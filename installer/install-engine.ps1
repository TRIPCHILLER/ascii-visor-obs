Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Assert-VisorTarget([string]$Target,[string]$Base) {
 $resolved=[IO.Path]::GetFullPath($Target).TrimEnd('\')
 $parent=[IO.Path]::GetFullPath($Base).TrimEnd('\')
 if (!$resolved.StartsWith($parent+'\',[StringComparison]::OrdinalIgnoreCase)) {throw 'Destination outside the selected installation folder.'}
 if ($resolved -eq $parent) {throw 'Invalid destination.'}
 return $resolved
}

function Test-VisorPayload([string]$Payload) {
 $manifest=Get-Content -LiteralPath (Join-Path $Payload 'manifest.json') -Raw -Encoding UTF8 | ConvertFrom-Json
 if ($manifest.version -ne '0.2.6') {throw 'Unexpected package version.'}
 foreach($file in $manifest.files) {
  $path=Assert-VisorTarget (Join-Path $Payload $file.path) $Payload
  if (!(Test-Path -LiteralPath $path -PathType Leaf)) {throw "Missing package file: $($file.path)"}
  if ((Get-FileHash -LiteralPath $path -Algorithm SHA256).Hash -ne $file.sha256) {throw "Damaged package file: $($file.path)"}
 }
 $actual=@(Get-ChildItem -LiteralPath (Join-Path $Payload 'ascii-visor') -File -Recurse)
 if($actual.Count -ne @($manifest.files).Count){throw 'Unexpected package files.'}
}

function Install-VisorPackage([string]$Payload,[string]$Base,[bool]$Portable,[bool]$SimulateFailure=$false) {
 Test-VisorPayload $Payload
 $Base=[IO.Path]::GetFullPath($Base).TrimEnd('\')
 $backupRoot=Assert-VisorTarget (Join-Path $Base ('visor-install-backups\'+[Guid]::NewGuid().ToString('N'))) $Base
 New-Item -ItemType Directory -Path $backupRoot -Force | Out-Null
 if($Portable) {
  $entries=@(
   @{Source=(Join-Path $Payload 'ascii-visor/bin/64bit/ascii-visor.dll');Relative='obs-plugins/64bit/ascii-visor.dll'},
   @{Source=(Join-Path $Payload 'ascii-visor/data');Relative='data/obs-plugins/ascii-visor'}
  )
 } else {
  $entries=@(@{Source=(Join-Path $Payload 'ascii-visor');Relative='plugins/ascii-visor'})
 }
 $completed=New-Object System.Collections.ArrayList
 try {
  for($i=0;$i -lt $entries.Count;$i++) {
   $entry=$entries[$i]
   $target=Assert-VisorTarget (Join-Path $Base $entry.Relative) $Base
   # Refuse junctions/symlinks at the destination or along its parent path.
   $ancestor=$target
   while($ancestor -and $ancestor.Length -ge $Base.Length) {
    if(Test-Path -LiteralPath $ancestor) {
     if((Get-Item -LiteralPath $ancestor).Attributes -band [IO.FileAttributes]::ReparsePoint){throw 'Installation through a junction or symbolic link is not supported.'}
    }
    $ancestor=[IO.Path]::GetDirectoryName($ancestor)
   }
   $saved=Join-Path $backupRoot ('previous-'+$i)
   $staged=Join-Path $backupRoot ('staged-'+$i)
   Copy-Item -LiteralPath $entry.Source -Destination $staged -Recurse
   New-Item -ItemType Directory -Path ([IO.Path]::GetDirectoryName($target)) -Force | Out-Null
   $record=@{Target=$target;Saved=$saved;HadOld=(Test-Path -LiteralPath $target);Installed=$false}
   [void]$completed.Add($record)
   if($record.HadOld){Move-Item -LiteralPath $target -Destination $saved}
   Move-Item -LiteralPath $staged -Destination $target
   $record.Installed=$true
   if($SimulateFailure){throw 'Simulated failure for rollback test.'}
  }
 } catch {
  $failure=$_
  for($i=$completed.Count-1;$i -ge 0;$i--) {
   $record=$completed[$i]
   $checked=Assert-VisorTarget $record.Target $Base
   if($record.Installed -and (Test-Path -LiteralPath $checked)) {
    Move-Item -LiteralPath $checked -Destination (Join-Path $backupRoot ('failed-'+$i))
   }
   if($record.HadOld -and (Test-Path -LiteralPath $record.Saved)) {Move-Item -LiteralPath $record.Saved -Destination $checked}
  }
  throw $failure
 }
 return $backupRoot
}

function Test-VisorOBS([string]$Executable) {
 if(!(Test-Path -LiteralPath $Executable -PathType Leaf)){return $false}
 if([IO.Path]::GetFileName($Executable) -ne 'obs64.exe'){return $false}
 $version=(Get-Item -LiteralPath $Executable).VersionInfo.FileVersion
 return $version -match '^32\.2\.2(?:\D|$)'
}
