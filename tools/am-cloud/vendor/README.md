# Complete A:M 19.5 SDK upload location

Upload the original **sdk195.zip** into this directory on branch
**build/am-plugins-sdk195**, not `main` or the old development branch.
Leave the archive zipped. The required repository path is:

```text
tools/am-cloud/vendor/sdk195.zip
```

Expected size: **6,529,791 bytes**.
Expected SHA-256 (unchanged from `../sdk.lock.json`):

```text
0e917a67d9ac386ea3ad512ce97518f764cddc032957682717c862e64c112977
```

The repository owner has authorized adding this Library copy to this public
repository. This README is only a placeholder; it does not contain the SDK.
The existing workflow automatically uses an archive at this path and verifies
its checksum. Keep the setup PR in draft until compilation, binary auditing
and a local A:M runtime check are complete.

Do not upload an A:M installation, activation/license files or personal settings.
Existing SDK notices and licenses remain unchanged; no relicensing is implied.
