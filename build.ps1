param([string]$OBSPath='G:/STEAM/steamapps/common/OBS Studio', [string]$DependencyRoot='')
$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot
if (!$DependencyRoot) {
 $DependencyRoot = if (Test-Path "$root/tools/llvm-mingw-20261006-ucrt-x86_64") { $root } else { Join-Path $root '../..' }
}
$compiler = Join-Path $DependencyRoot 'tools/llvm-mingw-20261006-ucrt-x86_64/bin'
$sdk = Join-Path $DependencyRoot 'vendor/obs-studio-32.2.2/libobs'
$obsBin = Join-Path $OBSPath 'bin/64bit'
if (!(Test-Path "$compiler/clang.exe") -or !(Test-Path "$sdk/obs-module.h")) { throw 'Run prepare-dependencies.ps1 first, or pass DependencyRoot.' }
$build = Join-Path $root 'build'
New-Item -ItemType Directory -Force -Path $build | Out-Null
# Derive the import library from this computer's actual OBS exports.
$exports = & "$compiler/llvm-readobj.exe" --coff-exports "$obsBin/obs.dll"
if ($LASTEXITCODE) { throw 'Cannot inspect OBS exports' }
$names = $exports | ForEach-Object { if ($_ -match '^\s+Name: (.+)$') { $Matches[1] } }
@('LIBRARY obs.dll','EXPORTS') + $names | Set-Content "$build/obs.def" -Encoding ascii
& "$compiler/llvm-dlltool.exe" -m i386:x86-64 -d "$build/obs.def" -l "$build/libobs.a"
if ($LASTEXITCODE) { throw 'Import library generation failed' }
& "$compiler/clang.exe" -std=c11 -O2 -Wall -Wextra -shared '-D_WIN32_WINNT=0x0601' "-I$sdk" "-I$root/sdk-config" "$root/src/visor.c" "$build/libobs.a" -lgdi32 -luser32 -lshell32 -o "$build/ascii-visor.dll"
if ($LASTEXITCODE) { throw 'Plugin compilation failed' }
if (Test-Path "$root/tests/obs-smoke.c") {
 & "$compiler/clang.exe" -std=c11 -O2 -Wall -Wextra "-I$sdk" "-I$root/sdk-config" "$root/tests/obs-smoke.c" "$build/libobs.a" -lole32 -o "$build/obs-smoke.exe"
 if ($LASTEXITCODE) { throw 'Test compilation failed' }
}
Write-Host 'Build successful: build/ascii-visor.dll'
if (Test-Path "$root/tests/locale-smoke.c") {
 & "$compiler/clang.exe" -std=c11 -O2 -Wall -Wextra "-I$sdk" "-I$root/sdk-config" "$root/tests/locale-smoke.c" "$build/libobs.a" -o "$build/locale-smoke.exe"
 if ($LASTEXITCODE) { throw 'Localization test compilation failed' }
}

if (Test-Path "$root/tests/scene-transparency.c") {
 & "$compiler/clang.exe" -std=c11 -O2 -Wall -Wextra "-I$sdk" "-I$root/sdk-config" "$root/tests/scene-transparency.c" "$build/libobs.a" -lole32 -o "$build/scene-transparency.exe"
 if ($LASTEXITCODE) { throw 'Scene transparency test compilation failed' }
}
