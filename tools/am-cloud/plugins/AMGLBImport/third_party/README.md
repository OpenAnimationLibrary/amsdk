# Pinned cgltf

The unmodified header and MIT license are identified by repository, commit and
SHA-256 in `provenance.json`. Local `.gitattributes` disables text conversion for
those two files, preserving upstream bytes on Windows checkouts.

The MSVC wrapper in `GLBReader.cpp` scopes warning settings to this vendor header.
In particular, native build run 34196549235 exposed C4996 errors under `/sdl` for
portable C99 `fopen`, `strcpy` and `strncpy` calls. These Microsoft CRT deprecation
diagnostics request Microsoft-specific `_s` alternatives; they are not reports of
observed buffer overruns. The native tests now also compile with `/sdl`.

The reported sites in this exact header were inspected: default file opening at
1048; path combination at 1289-1294; legacy extras-copy helper at 1824/1829; bounded,
terminated token-number copies at 2771-2792; and preallocated JSON string copies
at 2871 and 3029-3062. Path/file helpers are not called by this importer: it parses
in-memory bytes and rejects all external geometry buffers before loading data.
Token/string copies use destination sizing based on the bounded input spans.

C4996 is disabled only between the vendor warning push/pop. `/sdl`, stack checks,
owned-source diagnostics, SDK warning audit, parser bounds/memory limits and the
malformed-input regression tests remain enabled. No SDK or vendor bytes were
patched, and no project-wide `_CRT_SECURE_NO_WARNINGS` definition is introduced.
The legacy extras-copy helper is also unused; its caller-buffer contract is not
certified by this review.
This review does not certify arbitrary future cgltf versions or glTF extensions.
