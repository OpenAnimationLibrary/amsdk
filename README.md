# Animation:Master SDK Docs (MkDocs)

Converted from Doxygen HTML to Markdown and published with MkDocs Material.

Animation:Master SDK Docs (online): https://openanimationlibrary.github.io/amsdk/

## Develop plugins without a local compiler

The Windows command-plugin build system uses GitHub-hosted Windows 2022,
Visual Studio 2022/MFC and the checksum-locked, complete A:M 19.5 SDK. Edit
sources in a branch, build remotely, verify the package and test the HXT in A:M.
The virtual machine is a disposable compiler environment, not a remote desktop
or an activated copy of A:M.

Start with the [plugin development guide](docs/plugin-development.md).
For scripted or AI-assisted work, read [AGENTS.md](AGENTS.md) and the
[plugin automation runbook](docs/plugin-automation.md).

| Reference | Purpose |
| --- | --- |
| [Development guide](docs/plugin-development.md) | Repository layout, new-plugin setup, object contexts and the end-to-end process |
| [Automation runbook](docs/plugin-automation.md) | Branch/PR handling, CLI and connector operations, exact run selection and handoff |
| [Build-system guide](tools/am-cloud/README.md) | Toolchain locks, audits, failure handling, packaging and local reproduction |
| [Host test and rollback](tools/am-cloud/HOST-TEST.md) | Verify, install with A:M closed, test, report and restore a known-good binary |
| [Validation record](docs/plugin-build-validation.md) | What has actually passed, exact identities and remaining limits |
| [Known-good host baseline](tools/am-cloud/validation/known-good.json) | Human-tested HXT hash, A:M version and context; never inferred from CI |

The complete SDK already exists at `tools/am-cloud/vendor/sdk195.zip` on the
build-development branch. There is no website fallback or private-repository
bootstrap. Do not mix it with the historical top-level `Include/` and `Lib/`.
The older API documentation remains useful reference material, but its v12/VS6
setup instructions are not the current Windows build recipe.

**Build success, package integrity and A:M runtime success are separate gates.**
The initial human-confirmed baseline is diagnostic v2 in A:M 19.5g, Group
context. The hardened run #10 passed Release and Debug CI, not a new host test.
See the dated validation record rather than treating this summary as live status.

During foundation review, use PR #3 / `build/am-plugins-sdk195`; do not merge
merely to start a build. After review/merge, new feature PRs should use the
then-current approved base. No automatic merge, deployment, or branch-rule
change is performed by the build system. Existing SDK/third-party rights and
notices remain unchanged.
