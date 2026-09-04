# Approved complete A:M 19.5 SDK

`sdk195.zip` is already committed here with the repository owner's approval.
It is the complete Library copy supplied on August 24, 2026: 6,529,791 bytes,
SHA-256 `0e917a67d9ac386ea3ad512ce97518f764cddc032957682717c862e64c112977`.
No further upload or private-repository bootstrap is required.

The build verifies this archive against `../sdk.lock.json` before extraction.
It never substitutes the older top-level SDK or downloads an alternative.
`Include/SDK` and `Include/3rdParty/Imath` must be present alongside the selected
Release/Debug x64 libraries. Existing SDK/third-party rights and notices remain
unchanged. Do not place A:M application, activation or personal files here.

To update the SDK, review the actual archive, its provenance and header/library
pairing, then update this archive and the lock together in a PR. Run both native
builds and repeat the intended A:M host test before adopting it as known-good.
