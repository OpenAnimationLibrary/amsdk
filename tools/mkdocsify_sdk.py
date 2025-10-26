import os, re, subprocess, shutil, sys, json
from pathlib import Path

# --- CONFIG ---
SRC = Path(r"F:\SDK_clean")                 # source: your cleaned HTML set
REPO = Path(r"F:\am-sdk-docs")              # destination: mkdocs repo
DOCS = REPO / "docs"
ASSETS = DOCS / "assets"
TOOLS = REPO / "tools"
CHUNK_HUGE_PAGES = True                      # set False to disable chunking
CHUNK_SPLIT_AT_H2 = True                     # split at "## " headings
CHUNK_MAX_CHARS = 15000                      # soft cap per chunk

# --- UTIL ---
def run(cmd):
    p = subprocess.run(cmd, capture_output=True, text=True, shell=True)
    if p.returncode != 0:
        print("ERROR:", p.stderr.strip())
        raise SystemExit(p.returncode)
    return p.stdout

def ensure_clean_tree():
    REPO.mkdir(parents=True, exist_ok=True)
    TOOLS.mkdir(parents=True, exist_ok=True)
    DOCS.mkdir(parents=True, exist_ok=True)
    ASSETS.mkdir(parents=True, exist_ok=True)

def convert_html_to_md():
    # Find all .html/.htm in SRC and convert with pandoc
    htmls = [p for p in SRC.rglob("*") if p.suffix.lower() in (".html",".htm")]
    print(f"Converting {len(htmls)} HTML files → Markdown...")
    for html in htmls:
        rel = html.relative_to(SRC)
        out_md = (DOCS / rel).with_suffix(".md")
        out_md.parent.mkdir(parents=True, exist_ok=True)

        pandoc_cmd = (
            f'pandoc "{html}" -f html -t gfm '
            f'--extract-media="{ASSETS}" --wrap=none -o "{out_md}"'
        )
        run(pandoc_cmd)

def rewrite_links_in_md():
    # Convert internal links .../foo.html#abc -> .../foo.md#abc
    # Also fix plain foo.html to foo.md
    print("Rewriting internal links .html → .md ...")
    md_files = list(DOCS.rglob("*.md"))
    link_html = re.compile(r'(\]\()([^):]+?\.html)(#[^)]+)?(\))')  # markdown [text](link.html#hash)
    angle_html = re.compile(r'(<a\s+[^>]*href=["\'])([^"\']+?\.html)(#[^"\']+)?(["\'])', re.I)

    for md in md_files:
        txt = md.read_text(encoding="utf-8", errors="ignore")

        def md_sub(m):
            base = m.group(2)
            frag = m.group(3) or ""
            return f'{m.group(1)}{base[:-5]}.md{frag}{m.group(4)}'

        def a_sub(m):
            base = m.group(2)
            frag = m.group(3) or ""
            return f'{m.group(1)}{base[:-5]}.md{frag}{m.group(4)}'

        new = link_html.sub(md_sub, txt)
        new = angle_html.sub(a_sub, new)

        if new != txt:
            md.write_text(new, encoding="utf-8")

def chunk_large_md():
    if not CHUNK_HUGE_PAGES:
        return
    print("Chunking large Markdown files (with stubs for original targets)...")
    md_files = list(DOCS.rglob("*.md"))
    split_pat = re.compile(r'(?m)^(##\s+.+)$') if CHUNK_SPLIT_AT_H2 else re.compile(r'(?m)^(#\s+.+)$')

    for md in md_files:
        txt = md.read_text(encoding="utf-8", errors="ignore")
        if len(txt) <= CHUNK_MAX_CHARS:
            continue

        parts = split_pat.split(txt)
        if len(parts) == 1:
            blocks = [txt]
        else:
            blocks = [parts[0]] + [parts[i] + parts[i+1] for i in range(1, len(parts), 2)]

        # further split blocks by size if needed
        chunks = []
        for b in blocks:
            if len(b) <= CHUNK_MAX_CHARS:
                chunks.append(b)
            else:
                chunks.extend([b[i:i+CHUNK_MAX_CHARS] for i in range(0, len(b), CHUNK_MAX_CHARS)])

        base = md.with_suffix("")
        chunk_paths = []
        for i, c in enumerate(chunks):
            out = base.parent / f"{base.name}__{i:02d}.md"
            out.write_text(c, encoding="utf-8")
            chunk_paths.append(out.name)

        # Create a stub at the original filename that links to the chunks
        # This preserves targets like foo_8h.md used by other pages.
        stub_lines = []
        stub_lines.append(f"# {base.name}\n")
        stub_lines.append(f"> This page was split into smaller parts. Start here: [{chunk_paths[0]}]({chunk_paths[0]}).\n")
        stub_lines.append("## Parts\n")
        for cp in chunk_paths:
            stub_lines.append(f"- [{cp}]({cp})")
        md.write_text("\n".join(stub_lines) + "\n", encoding="utf-8")


def write_mkdocs_yml():
    print("Writing mkdocs.yml...")
    # Auto-generate a simple nav from top-level directories under docs/
    # (sorted folders first, then files)
    def collect_nav(root: Path):
        items = []
        folders = sorted([p for p in root.iterdir() if p.is_dir() and p.name != "assets"], key=lambda p:p.name.lower())
        files = sorted([p for p in root.iterdir() if p.is_file() and p.suffix==".md"], key=lambda p:p.name.lower())

        for f in files:
            items.append({readable_title(f.stem): str(f.relative_to(DOCS)).replace("\\","/")})
        for d in folders:
            child = collect_nav(d)
            if child:
                items.append({readable_title(d.name): child})
        return items

    def readable_title(name: str) -> str:
        # nicer titles from filenames
        name = re.sub(r'__\d{2}(_\d{2})?$', '', name)  # strip chunk suffixes
        name = name.replace('-', ' ').replace('_',' ')
        name = re.sub(r'\s+', ' ', name).strip()
        return name[:1].upper() + name[1:]

    nav = collect_nav(DOCS)
    yml = f"""site_name: Animation:Master SDK
site_url: https://example.github.io/am-sdk-docs
repo_url: https://github.com/USER/am-sdk-docs
theme:
  name: material
  features:
    - navigation.instant
    - navigation.tracking
    - content.code.copy
    - search.suggest
    - search.highlight
markdown_extensions:
  - toc:
      permalink: true
  - admonition
  - tables
  - attr_list
  - def_list
  - footnotes
nav:
"""

    def dump_nav(items, indent=2):
        out_lines = []
        sp = ' ' * indent
        for it in items:
            (k, v), = it.items()
            if isinstance(v, list):
                out_lines.append(f"{sp}- {k}:")
                out_lines.extend(dump_nav(v, indent+2))
            else:
                out_lines.append(f"{sp}- {k}: {v}")
        return out_lines

    yml_lines = [yml] + dump_nav(nav, 2)
    (REPO/"mkdocs.yml").write_text("\n".join(yml_lines) + "\n", encoding="utf-8")

def write_readme_gitignore():
    (REPO/"README.md").write_text(
        "# Animation:Master SDK Docs (MkDocs)\n\n"
        "Converted from Doxygen HTML to Markdown and published with MkDocs Material.\n", encoding="utf-8"
    )
    (REPO/".gitignore").write_text(
        "site/\n__pycache__/\n*.pyc\n.DS_Store\n", encoding="utf-8"
    )

def main():
    ensure_clean_tree()
    convert_html_to_md()
    rewrite_links_in_md()
    chunk_large_md()
    write_mkdocs_yml()
    write_readme_gitignore()
    print("\nDone. Next steps:")
    print("  1) cd F:\\am-sdk-docs")
    print("  2) mkdocs serve  (then open http://127.0.0.1:8000)")
    print("  3) git init && git add . && git commit -m \"Initial MkDocs\"")
    print("  4) Create GitHub repo & push")
    print("  5) mkdocs gh-deploy  (to publish to GitHub Pages)")

if __name__ == "__main__":
    main()
