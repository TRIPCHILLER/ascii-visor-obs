$ErrorActionPreference='Stop'
. (Join-Path $PSScriptRoot 'install-engine.ps1')
$testRoot=Join-Path $PSScriptRoot ('tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $testRoot | Out-Null
$payload=(Get-ChildItem -LiteralPath $PSScriptRoot -Directory -Filter 'payload-build-*' | Sort-Object LastWriteTime -Descending | Select-Object -First 1).FullName
function Assert([bool]$Condition,[string]$Name){if(!$Condition){throw "FAIL: $Name"};Write-Host "PASS: $Name"}
$base=Join-Path $testRoot 'standard'
$backup=Install-VisorPackage $payload $base $false
$dll=Join-Path $base 'plugins/ascii-visor/bin/64bit/ascii-visor.dll'
Assert (Test-Path -LiteralPath $dll) 'fresh standard installation creates folders'
Assert (@(Get-ChildItem -LiteralPath (Join-Path $base 'plugins/ascii-visor/data/locale') -Filter '*.ini').Count -eq 10) 'ten languages installed'
Set-Content -LiteralPath (Join-Path $base 'user-settings.txt') -Value 'preserve-me'
Set-Content -LiteralPath $dll -Value 'old-test-dll'
$oldHash=(Get-FileHash -LiteralPath $dll).Hash
$backup=Install-VisorPackage $payload $base $false
Assert ((Get-FileHash -LiteralPath (Join-Path $backup 'previous-0/bin/64bit/ascii-visor.dll')).Hash -eq $oldHash) 'previous plugin preserved'
Assert ((Get-Content -LiteralPath (Join-Path $base 'user-settings.txt')) -eq 'preserve-me') 'user settings untouched'
$currentHash=(Get-FileHash -LiteralPath $dll).Hash
$failed=$false
try{Install-VisorPackage $payload $base $false $true | Out-Null}catch{$failed=$true}
Assert ($failed -and (Get-FileHash -LiteralPath $dll).Hash -eq $currentHash) 'standard rollback restores previous version'
$portable=Join-Path $testRoot 'portable'
Install-VisorPackage $payload $portable $true | Out-Null
$portableDll=Join-Path $portable 'obs-plugins/64bit/ascii-visor.dll'
Assert (Test-Path -LiteralPath $portableDll) 'portable layout installed'
Assert (Test-Path -LiteralPath (Join-Path $portable 'data/obs-plugins/ascii-visor/visor.effect')) 'portable shader path'
Set-Content -LiteralPath $portableDll -Value 'previous-portable-dll'
$portableHash=(Get-FileHash -LiteralPath $portableDll).Hash
$failed=$false
try{Install-VisorPackage $payload $portable $true $true | Out-Null}catch{$failed=$true}
Assert ($failed -and (Get-FileHash -LiteralPath $portableDll).Hash -eq $portableHash) 'portable rollback restores previous version'
$corrupt=Join-Path $testRoot 'corrupt-payload'
Copy-Item -LiteralPath $payload -Destination $corrupt -Recurse
Set-Content -LiteralPath (Join-Path $corrupt 'ascii-visor/data/visor.effect') -Value 'tampered'
$failed=$false
try{Test-VisorPayload $corrupt}catch{$failed=$true}
Assert $failed 'damaged payload rejected'
$failed=$false
try{Assert-VisorTarget (Join-Path $testRoot 'outside') $base | Out-Null}catch{$failed=$true}
Assert $failed 'outside destination rejected'
Assert (Test-VisorOBS 'G:/STEAM/steamapps/common/OBS Studio/bin/64bit/obs64.exe') 'actual OBS 32.2.2 recognized'
Write-Host 'RESULT failures=0'
