from pathlib import Path
import re, sys

DOCS = Path("docs")
PLUGIN = DOCS / "Plugin"

def titleize(name: str) -> str:
    name = re.sub(r'__\d{2}(?:_\d{2})?$', '', name)  # drop chunk suffixes
    name = name.replace('-', ' ').replace('_', ' ')
    name = re.sub(r'\s+', ' ', name).strip()
    return name[:1].upper() + name[1:] if name else name

def list_nav(root: Path):
    items = []
    folders = sorted([p for p in root.iterdir() if p.is_dir()], key=lambda p:p.name.lower())
    files = sorted([p for p in root.iterdir() if p.is_file() and p.suffix==".md"], key=lambda p:p.name.lower())

    for f in files:
        rel = f.relative_to(DOCS).as_posix()
        items.append({titleize(f.stem): rel})
    for d in folders:
        child = list_nav(d)
        if child:
            items.append({titleize(d.name): child})
    return items

def dump_yaml(items, indent=2):
    out = []
    sp = ' ' * indent
    for it in items:
        (k, v), = it.items()
        if isinstance(v, list):
            out.append(f"{sp}- {k}:")
            out.extend(dump_yaml(v, indent+2))
        else:
            out.append(f"{sp}- {k}: {v}")
    return out

if not PLUGIN.exists():
    print("docs/Plugin/ not found.", file=sys.stderr); sys.exit(1)

nav = [{"Home": "index.md"}, {"Plugin": list_nav(PLUGIN)}]
print("nav:")
print("\n".join(dump_yaml(nav, indent=0)))
