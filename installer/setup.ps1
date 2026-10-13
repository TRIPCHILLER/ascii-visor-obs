param([string]$Bundle,[string]$PreviewPath,[switch]$SelfTest,[string]$LanguageCode,[switch]$PreviewFinish)
$ErrorActionPreference='Stop'
$env:PSModulePath=Join-Path $PSHOME 'Modules'
Start-Transcript -LiteralPath (Join-Path $PSScriptRoot 'startup.log') -Force | Out-Null
. (Join-Path $PSScriptRoot 'install-engine.ps1')
. (Join-Path $PSScriptRoot 'launch-obs.ps1')
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
Add-Type -Path (Join-Path $PSScriptRoot 'flags.cs') -ReferencedAssemblies 'System.Drawing.dll','System.dll'
[Windows.Forms.Application]::EnableVisualStyles()
$translations=Get-Content -LiteralPath (Join-Path $PSScriptRoot 'locales.json') -Raw -Encoding UTF8 | ConvertFrom-Json
$codes=@('ru-RU','en-US','es-ES','pt-BR','de-DE','fr-FR','ja-JP','ko-KR','zh-CN','zh-TW')
if(!$LanguageCode){
 $culture=[Globalization.CultureInfo]::CurrentUICulture.Name
 if($culture -in $codes){$LanguageCode=$culture}
 elseif($culture -match '^zh-(TW|HK|MO|Hant)'){$LanguageCode='zh-TW'}
 elseif($culture -match '^zh'){$LanguageCode='zh-CN'}
 else{$LanguageCode=$codes | Where-Object {$_.Substring(0,2) -eq $culture.Substring(0,2)} | Select-Object -First 1}
}
if($LanguageCode -notin $codes){$LanguageCode='en-US'}
function L([string]$Key){return $translations.PSObject.Properties[$script:LanguageCode].Value.PSObject.Properties[$Key].Value}
$work=Join-Path $PSScriptRoot ('extracted-'+[Guid]::NewGuid().ToString('N'))
try{Add-Type -AssemblyName System.IO.Compression.FileSystem;[IO.Compression.ZipFile]::ExtractToDirectory($Bundle,$work);Test-VisorPayload $work}
catch{[void][Windows.Forms.MessageBox]::Show((L 'InstallerError')+"`n"+$_.Exception.Message,'ASCII VISOR');exit 1}
$form=New-Object Windows.Forms.Form
$form.Text='ASCII VISOR · OBS Edition 0.2.8 · Setup'
$form.Icon=New-Object Drawing.Icon((Join-Path $PSScriptRoot 'installer.ico'))
$form.ClientSize=New-Object Drawing.Size(720,470)
$form.StartPosition='CenterScreen';$form.FormBorderStyle='FixedDialog';$form.MaximizeBox=$false
$form.Font=New-Object Drawing.Font('Segoe UI',10)
function Label([int]$X,[int]$Y,[int]$W,[int]$H){$control=New-Object Windows.Forms.Label;$control.SetBounds($X,$Y,$W,$H);$form.Controls.Add($control);return $control}
$heading=Label 24 20 435 64
$heading.Font=New-Object Drawing.Font('Segoe UI',17,[Drawing.FontStyle]::Bold)
$intro=Label 26 90 665 40
$standard=New-Object Windows.Forms.RadioButton;$standard.SetBounds(26,142,660,32);$standard.Checked=$true;$form.Controls.Add($standard)
$portable=New-Object Windows.Forms.RadioButton;$portable.SetBounds(26,180,660,32);$form.Controls.Add($portable)
$detail=Label 26 230 665 86
$license=Label 26 325 665 62
$install=New-Object Windows.Forms.Button;$install.SetBounds(402,414,144,36);$form.Controls.Add($install)
$cancel=New-Object Windows.Forms.Button;$cancel.SetBounds(558,414,136,36);$form.Controls.Add($cancel)
$credits=Label 26 408 360 48
$credits.ForeColor=[Drawing.Color]::DimGray
$credits.Font=New-Object Drawing.Font('Segoe UI',9)
$language=New-Object Windows.Forms.ComboBox;$language.DropDownStyle='DropDownList'
$language.DrawMode='OwnerDrawFixed';$language.ItemHeight=25;$language.SetBounds(474,28,220,32)
$flagImages=@{}
foreach($code in $codes){[void]$language.Items.Add($code);$flagImages[$code]=[VisorFlags]::Create($code)}
$language.SelectedIndex=[Array]::IndexOf($codes,$LanguageCode);$form.Controls.Add($language)
$language.Add_DrawItem({
 param($sender,$e)
 if($e.Index -lt 0){return}
 $e.DrawBackground();$code=$codes[$e.Index]
 $e.Graphics.DrawImage($flagImages[$code],$e.Bounds.X+5,$e.Bounds.Y+4,24,16)
 $name=$translations.PSObject.Properties[$code].Value.Name
 $brush=New-Object Drawing.SolidBrush($e.ForeColor)
 $e.Graphics.DrawString($name,$e.Font,$brush,[single]($e.Bounds.X+37),[single]($e.Bounds.Y+3));$brush.Dispose();$e.DrawFocusRectangle()
})
$launch=New-Object Windows.Forms.CheckBox;$launch.SetBounds(26,260,660,30);$launch.Visible=$false;$launch.Checked=$false;$form.Controls.Add($launch)
$launchMode=New-Object Windows.Forms.ComboBox;$launchMode.DropDownStyle='DropDownList';$launchMode.SetBounds(48,300,520,32);$launchMode.Visible=$false;$form.Controls.Add($launchMode)
$script:complete=$false;$script:selectedOBS=$null;$script:backup=$null;$script:portableInstall=$false
$script:steamAvailable=Test-Path -LiteralPath 'Registry::HKEY_CLASSES_ROOT\steam\shell\open\command'
function Update-Text {
 $heading.Text=if($script:complete){L 'DoneHeading'}else{L 'Heading'}
 $intro.Text=L 'Intro';$standard.Text=L 'Standard';$portable.Text=L 'Portable'
 $credits.Text=L 'Credits'
 $detail.Text=if($script:complete){L 'DoneInfo'}else{L 'Detail'}
 $license.Text=if($script:complete){(L 'Backup')+"`n"+$script:backup}else{L 'License'}
 $install.Text=L 'Install';$cancel.Text=if($script:complete){L 'Finish'}else{L 'Cancel'}
 $launch.Text=L 'Launch'
 $index=$launchMode.SelectedIndex;$launchMode.Items.Clear();[void]$launchMode.Items.Add((L 'DirectOBS'))
 if(!$portable.Checked -and $script:steamAvailable){[void]$launchMode.Items.Add((L 'SteamOBS'))}
 $launchMode.SelectedIndex=if($index -ge 0 -and $index -lt $launchMode.Items.Count){$index}else{0}
}
function Show-Finish {
 $script:complete=$true;$standard.Visible=$false;$portable.Visible=$false;$install.Visible=$false
 $detail.SetBounds(26,150,665,75);$license.SetBounds(26,350,665,56)
 $launch.Visible=$true;$launchMode.Visible=$true;Update-Text
}
$language.Add_SelectedIndexChanged({$script:LanguageCode=$codes[$language.SelectedIndex];Update-Text})
$launchMode.Enabled=$false;$launch.Add_CheckedChanged({$launchMode.Enabled=$launch.Checked})
$cancel.Add_Click({
 if($script:complete -and $launch.Checked){
  try{Start-VisorOBS $script:selectedOBS ($launchMode.SelectedIndex -eq 1) $script:portableInstall}
  catch{[void][Windows.Forms.MessageBox]::Show((L 'LaunchError'),'ASCII VISOR','OK','Information');return}
 }
 $form.Close()
})
$install.Add_Click({
 try{
  if(Get-Process -Name obs64 -ErrorAction SilentlyContinue){throw (L 'CloseOBS')}
  $obsExe=$null
  if($standard.Checked){
   $candidates=@((Join-Path $env:ProgramFiles 'obs-studio/bin/64bit/obs64.exe'),(Join-Path $env:ProgramData 'obs-studio/bin/64bit/obs64.exe'))
   $steamKey=Get-ItemProperty -LiteralPath 'HKCU:\Software\Valve\Steam' -ErrorAction SilentlyContinue
   if($steamKey -and $steamKey.PSObject.Properties['SteamPath']){$candidates+=Join-Path $steamKey.SteamPath 'steamapps/common/OBS Studio/bin/64bit/obs64.exe'}
   foreach($candidate in $candidates){if(Test-VisorOBS $candidate){$obsExe=$candidate;break}}
  }
  if(!$obsExe){$select=New-Object Windows.Forms.OpenFileDialog;$select.Title=L 'SelectOBS';$select.Filter='OBS Studio (obs64.exe)|obs64.exe';if($select.ShowDialog() -ne 'OK'){return};$obsExe=$select.FileName}
  if(!(Test-VisorOBS $obsExe)){throw (L 'Incompatible')}
  $obsRoot=[IO.Directory]::GetParent([IO.Directory]::GetParent([IO.Path]::GetDirectoryName($obsExe)).FullName).FullName
  $isPortable=$portable.Checked
  if(!$isPortable -and ((Test-Path -LiteralPath (Join-Path $obsRoot 'portable_mode.txt')) -or (Test-Path -LiteralPath (Join-Path $obsRoot 'portable_mode')))){throw (L 'PortableDetected')}
  $base=if($isPortable){$obsRoot}else{Join-Path $env:ProgramData 'obs-studio'}
  $target=if($isPortable){$base}else{Join-Path $base 'plugins/ascii-visor'}
  $message=(L 'Destination')+"`n"+$target+"`n`n"+(L 'BackupNotice')
  if([Windows.Forms.MessageBox]::Show($message,'ASCII VISOR','OKCancel','Information') -ne 'OK'){return}
  $install.Enabled=$false
  $script:backup=Install-VisorPackage $work $base $isPortable
  $script:selectedOBS=$obsExe
  $script:portableInstall=$isPortable
  Show-Finish
 }catch{$install.Enabled=$true;[void][Windows.Forms.MessageBox]::Show((L 'InstallerError')+"`n"+$_.Exception.Message,'ASCII VISOR','OK','Error')}
})
Update-Text
if($PreviewFinish){$script:backup='C:\ProgramData\obs-studio\visor-install-backups\example';Show-Finish}
if($SelfTest){
 Add-Type -TypeDefinition 'using System; using System.Runtime.InteropServices; public static class VisorWindowTest { [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr hWnd); }'
 $timer=New-Object Windows.Forms.Timer;$timer.Interval=1500
 $timer.Add_Tick({$timer.Stop();[pscustomobject]@{visible=[VisorWindowTest]::IsWindowVisible($form.Handle);title=$form.Text;languages=$language.Items.Count;locale=$script:LanguageCode} | ConvertTo-Json | Set-Content -LiteralPath (Join-Path $PSScriptRoot 'startup-test.json') -Encoding UTF8;$form.Close()})
 $form.Add_Shown({$timer.Start()});[void]$form.ShowDialog()
}elseif($PreviewPath){
 $form.Show();$form.Refresh();$bitmap=New-Object Drawing.Bitmap($form.Width,$form.Height)
 $layout=@()
 foreach($control in @($heading,$intro,$standard,$portable,$detail,$license,$install,$cancel,$launch,$credits)){
  if($control.Visible){
   $size=[Windows.Forms.TextRenderer]::MeasureText($control.Text,$control.Font,(New-Object Drawing.Size(($control.Width-12),10000)),[Windows.Forms.TextFormatFlags]::WordBreak)
   $layout+=[pscustomobject]@{text=$control.Text;fits=($size.Height -le $control.Height);height=$size.Height;available=$control.Height}
  }
 }
 $layout | ConvertTo-Json | Set-Content -LiteralPath ($PreviewPath+'.json') -Encoding UTF8
 $form.DrawToBitmap($bitmap,(New-Object Drawing.Rectangle(0,0,$form.Width,$form.Height)));$bitmap.Save($PreviewPath,[Drawing.Imaging.ImageFormat]::Png);$bitmap.Dispose();$form.Close()
}else{[void]$form.ShowDialog()}
foreach($flag in $flagImages.Values){$flag.Dispose()}
Stop-Transcript | Out-Null
