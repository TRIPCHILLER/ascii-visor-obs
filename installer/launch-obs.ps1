function Start-VisorOBS([string]$Executable,[bool]$ThroughSteam) {
 # Ask the existing desktop Explorer to launch, instead of inheriting the installer's administrator token.
 $shell=New-Object -ComObject Shell.Application
 $windowHandle=0
 $desktop=$shell.Windows().FindWindowSW(0,0,8,[ref]$windowHandle,1)
 if(!$desktop){throw 'Desktop Explorer is unavailable.'}
 if($ThroughSteam) {
  $desktop.Document.Application.ShellExecute('steam://run/1905180','','','open',1)
 } else {
  if(!(Test-VisorOBS $Executable)){throw 'Compatible OBS executable is unavailable.'}
  $desktop.Document.Application.ShellExecute($Executable,'',[IO.Path]::GetDirectoryName($Executable),'open',1)
 }
}
