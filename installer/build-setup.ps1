param([string]$CompilerRoot='',[string]$PluginRoot='')
$ErrorActionPreference='Stop'
if(!$PluginRoot){$PluginRoot=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..'))}
if(!$CompilerRoot){$CompilerRoot=Join-Path $PluginRoot 'tools/llvm-mingw-20261006-ucrt-x86_64/bin'}
if(!(Test-Path -LiteralPath (Join-Path $PluginRoot 'build/ascii-visor.dll'))){throw 'Build the plugin first or pass PluginRoot.'}
$payload=Join-Path $PSScriptRoot ('payload-build-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path (Join-Path $payload 'ascii-visor/bin/64bit'),(Join-Path $payload 'ascii-visor/data/fonts') -Force | Out-Null
Copy-Item -LiteralPath (Join-Path $PluginRoot 'build/ascii-visor.dll') -Destination (Join-Path $payload 'ascii-visor/bin/64bit')
Copy-Item -LiteralPath (Join-Path $PluginRoot 'data/visor.effect') -Destination (Join-Path $payload 'ascii-visor/data')
Copy-Item -LiteralPath (Join-Path $PluginRoot 'data/locale') -Destination (Join-Path $payload 'ascii-visor/data') -Recurse
foreach($font in @('BetterVCR.ttf','BetterVCR-OFL.txt','NotoSansMonoCJKjp-Regular.otf','Noto-OFL.txt')){
 Copy-Item -LiteralPath (Join-Path $PluginRoot ('data/fonts/'+$font)) -Destination (Join-Path $payload 'ascii-visor/data/fonts')
}
Copy-Item -LiteralPath (Join-Path $PluginRoot 'LICENSE') -Destination (Join-Path $payload 'ascii-visor')
$files=Get-ChildItem -LiteralPath (Join-Path $payload 'ascii-visor') -Recurse -File | ForEach-Object {
 [pscustomobject]@{path=$_.FullName.Substring($payload.Length+1).Replace('\','/');sha256=(Get-FileHash -LiteralPath $_.FullName).Hash}
}
[pscustomobject]@{version='0.2.6';files=@($files)} | ConvertTo-Json -Depth 5 | Set-Content -LiteralPath (Join-Path $payload 'manifest.json') -Encoding UTF8
Compress-Archive -Path (Join-Path $payload '*') -DestinationPath (Join-Path $PSScriptRoot 'payload.zip') -Force
Push-Location $PSScriptRoot
try {
 foreach($file in @('setup.ps1','install-engine.ps1','launch-obs.ps1')){
  $path=Join-Path $PSScriptRoot $file
  [IO.File]::WriteAllText($path,[IO.File]::ReadAllText($path),[Text.UTF8Encoding]::new($true))
 }
 & "$CompilerRoot/windres.exe" -i setup.rc -o setup-res.o
 if($LASTEXITCODE){throw 'Resource compilation failed'}
 & "$CompilerRoot/clang.exe" -O2 -Wall -Wextra -municode -mwindows bootstrap.c setup-res.o -luser32 -o ASCII-VISOR-0.2.6-Setup.exe
 if($LASTEXITCODE){throw 'Installer compilation failed'}
 Write-Host 'Built ASCII-VISOR-0.2.6-Setup.exe'
} finally{Pop-Location}
