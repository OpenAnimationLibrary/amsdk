# Read-only integrity check. Does not load/install a DLL or change system settings.
[CmdletBinding()]
param()
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest
try {
    $root = [IO.Path]::GetFullPath($PSScriptRoot) + [IO.Path]::DirectorySeparatorChar
    $manifest = Join-Path $PSScriptRoot 'SHA256SUMS.txt'
    $seen = @{}
    foreach ($line in Get-Content -LiteralPath $manifest) {
        if ($line -notmatch '^([0-9a-f]{64})  ([A-Za-z0-9_./ -]+)$') {
            throw 'Invalid checksum manifest line.'
        }
        $expected = $Matches[1]
        $relative = $Matches[2]
        if ($relative -match '(^|/)\.\.?(/|$)' -or [IO.Path]::IsPathRooted($relative)) {
            throw 'Unsafe path in checksum manifest.'
        }
        $path = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot $relative))
        if (-not $path.StartsWith($root, [StringComparison]::OrdinalIgnoreCase) -or $seen.ContainsKey($path)) {
            throw 'Duplicate or escaping checksum path.'
        }
        $seen[$path] = $true
        $item = Get-Item -LiteralPath $path
        if ($item.PSIsContainer -or ($item.Attributes -band [IO.FileAttributes]::ReparsePoint)) {
            throw "Not a regular payload file: $relative"
        }
        $actual = (Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash.ToLowerInvariant()
        if ($actual -ne $expected) { throw "Checksum mismatch: $relative" }
    }
    foreach ($item in Get-ChildItem -LiteralPath $PSScriptRoot -Recurse -Force) {
        if ($item.Attributes -band [IO.FileAttributes]::ReparsePoint) { throw 'Reparse point in package.' }
        if (-not $item.PSIsContainer -and $item.FullName -ne $manifest -and -not $seen.ContainsKey($item.FullName)) {
            throw "Unlisted payload file: $($item.Name)"
        }
    }
    $receiptPath = Join-Path $PSScriptRoot 'build-receipt.json'
    if (-not $seen.ContainsKey($receiptPath)) { throw 'Receipt is not covered by the manifest.' }
    $receipt = Get-Content -LiteralPath $receiptPath -Raw | ConvertFrom-Json
    if ($receipt.status -ne 'passed' -or $receipt.architecture -ne 'x64') { throw 'Build/audit did not pass for x64.' }
    $plugin = Join-Path $PSScriptRoot $receipt.plugin.file
    if (-not $seen.ContainsKey($plugin)) { throw 'Plugin is not covered by the manifest.' }
    $extension = if ($receipt.configuration -eq 'Release') { '.hxt' } elseif ($receipt.configuration -eq 'Debug') { '.hxtd' } else { throw 'Unknown configuration.' }
    if ([IO.Path]::GetExtension($plugin) -ne $extension) { throw 'Plugin extension and configuration disagree.' }
    if ((Get-FileHash -LiteralPath $plugin -Algorithm SHA256).Hash.ToLowerInvariant() -ne $receipt.plugin.sha256) {
        throw 'Plugin and build receipt disagree.'
    }
    Write-Output "PASS: $($receipt.plugin.file); $($receipt.configuration) x64; all payload hashes match."
    Write-Output "Checkout: $($receipt.source.checkout_commit)"
    Write-Output 'Integrity is not a signature or an A:M compatibility test. Trust the source run separately.'
    if ($receipt.configuration -eq 'Debug') { Write-Warning 'DEBUG HOST ONLY: do not install in ordinary Release A:M.' }
    exit 0
} catch {
    Write-Error -Message $_ -ErrorAction Continue
    exit 1
}
