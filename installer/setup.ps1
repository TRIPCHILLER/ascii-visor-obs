param([string]$Bundle,[string]$PreviewPath)
$ErrorActionPreference='Stop'
. (Join-Path $PSScriptRoot 'install-engine.ps1')
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
[Windows.Forms.Application]::EnableVisualStyles()
$ru=[Globalization.CultureInfo]::CurrentUICulture.Name.StartsWith('ru')
function T([string]$Russian,[string]$English){if($ru){return $Russian}else{return $English}}
$work=Join-Path $PSScriptRoot ('extracted-'+[Guid]::NewGuid().ToString('N'))
try {Expand-Archive -LiteralPath $Bundle -DestinationPath $work; Test-VisorPayload $work} catch {
 [void][Windows.Forms.MessageBox]::Show($_.Exception.Message,'ASCII VISOR'); exit 1
}
$form=New-Object Windows.Forms.Form
$form.Text='ASCII VISOR · OBS Edition 0.2.6'
$form.ClientSize=New-Object Drawing.Size(600,410)
$form.StartPosition='CenterScreen';$form.FormBorderStyle='FixedDialog';$form.MaximizeBox=$false
$form.Font=New-Object Drawing.Font('Segoe UI',10)
$heading=New-Object Windows.Forms.Label
$heading.Text=T 'Установить ASCII VISOR' 'Install ASCII VISOR'
$heading.Font=New-Object Drawing.Font('Segoe UI',18,[Drawing.FontStyle]::Bold)
$heading.SetBounds(24,20,420,40);$form.Controls.Add($heading)
$intro=New-Object Windows.Forms.Label
$intro.Text=T 'Бесплатный ASCII-видеофильтр · Windows x64 · OBS 32.2.2' 'Free ASCII video filter · Windows x64 · OBS 32.2.2'
$intro.SetBounds(26,68,550,45);$form.Controls.Add($intro)
$standard=New-Object Windows.Forms.RadioButton
$standard.Text=T 'Обычная OBS / Steam — общая установка' 'Standard OBS / Steam — shared installation'
$standard.SetBounds(26,124,550,30);$standard.Checked=$true;$form.Controls.Add($standard)
$portable=New-Object Windows.Forms.RadioButton
$portable.Text=T 'Переносная OBS — выбрать папку' 'Portable OBS — choose folder'
$portable.SetBounds(26,158,550,30);$form.Controls.Add($portable)
$detail=New-Object Windows.Forms.Label
$detail.Text=T 'Папки будут созданы автоматически. Сцены, профили и настройки OBS сохраняются. Перед установкой закройте все окна OBS.' 'Folders are created automatically. OBS scenes, profiles and settings are preserved. Close all OBS windows before installation.'
$detail.SetBounds(26,204,545,80);$form.Controls.Add($detail)
$license=New-Object Windows.Forms.Label
$license.Text=T 'Плагин: GPL-2.0-or-later · Шрифты: SIL OFL. Исходники и лицензии доступны в репозитории проекта.' 'Plugin: GPL-2.0-or-later · Fonts: SIL OFL. Source and licenses are available in the project repository.'
$license.SetBounds(26,284,545,55);$form.Controls.Add($license)
$install=New-Object Windows.Forms.Button
$install.Text=T 'Установить' 'Install';$install.SetBounds(310,356,130,36);$form.Controls.Add($install)
$cancel=New-Object Windows.Forms.Button
$cancel.Text=T 'Отмена' 'Cancel';$cancel.SetBounds(450,356,125,36);$cancel.Add_Click({$form.Close()});$form.Controls.Add($cancel)
$language=New-Object Windows.Forms.ComboBox
$language.DropDownStyle='DropDownList';$language.SetBounds(450,28,125,30)
[void]$language.Items.Add('Русский');[void]$language.Items.Add('English')
$language.SelectedIndex=if($ru){0}else{1};$form.Controls.Add($language)
$language.Add_SelectedIndexChanged({
 $script:ru=$language.SelectedIndex -eq 0
 $heading.Text=T 'Установить ASCII VISOR' 'Install ASCII VISOR'
 $intro.Text=T 'Бесплатный ASCII-видеофильтр · Windows x64 · OBS 32.2.2' 'Free ASCII video filter · Windows x64 · OBS 32.2.2'
 $standard.Text=T 'Обычная OBS / Steam — общая установка' 'Standard OBS / Steam — shared installation'
 $portable.Text=T 'Переносная OBS — выбрать папку' 'Portable OBS — choose folder'
 $detail.Text=T 'Папки будут созданы автоматически. Сцены, профили и настройки OBS сохраняются. Перед установкой закройте все окна OBS.' 'Folders are created automatically. OBS scenes, profiles and settings are preserved. Close all OBS windows before installation.'
 $license.Text=T 'Плагин: GPL-2.0-or-later · Шрифты: SIL OFL. Исходники и лицензии доступны в репозитории проекта.' 'Plugin: GPL-2.0-or-later · Fonts: SIL OFL. Source and licenses are available in the project repository.'
 $install.Text=T 'Установить' 'Install';$cancel.Text=T 'Отмена' 'Cancel'
})
$install.Add_Click({
 try {
  if(Get-Process -Name obs64 -ErrorAction SilentlyContinue){throw (T 'Закройте все окна OBS и повторите установку.' 'Close all OBS windows and try again.')}
  $obsExe=$null
  if($standard.Checked){
   $candidates=@((Join-Path $env:ProgramFiles 'obs-studio/bin/64bit/obs64.exe'),(Join-Path $env:ProgramData 'obs-studio/bin/64bit/obs64.exe'))
   $steamKey=Get-ItemProperty -LiteralPath 'HKCU:\Software\Valve\Steam' -ErrorAction SilentlyContinue
   if($steamKey -and $steamKey.SteamPath){$candidates+=Join-Path $steamKey.SteamPath 'steamapps/common/OBS Studio/bin/64bit/obs64.exe'}
   foreach($candidate in $candidates){if(Test-VisorOBS $candidate){$obsExe=$candidate;break}}
  }
  if(!$obsExe){
   $select=New-Object Windows.Forms.OpenFileDialog
   $select.Title=T 'Выберите obs64.exe той OBS, которую используете' 'Select obs64.exe from the OBS installation you use'
   $select.Filter='OBS Studio (obs64.exe)|obs64.exe'
   if($select.ShowDialog() -ne 'OK'){return}
   $obsExe=$select.FileName
  }
  if(!(Test-VisorOBS $obsExe)){throw (T 'Эта сборка проверена только с OBS 32.2.2 x64. Выберите совместимую OBS.' 'This build is verified only with OBS 32.2.2 x64. Select a compatible OBS installation.')}
  $obsRoot=[IO.Directory]::GetParent([IO.Directory]::GetParent([IO.Path]::GetDirectoryName($obsExe)).FullName).FullName
  $isPortable=$portable.Checked
  if(!$isPortable -and ((Test-Path -LiteralPath (Join-Path $obsRoot 'portable_mode.txt')) -or (Test-Path -LiteralPath (Join-Path $obsRoot 'portable_mode')))) {
   throw (T 'Выбрана переносная OBS. Выберите вариант «Переносная OBS» в установщике.' 'Portable OBS detected. Select the Portable OBS option in the installer.')
  }
  if($isPortable){$base=$obsRoot}else{$base=Join-Path $env:ProgramData 'obs-studio'}
  $target=if($isPortable){$base}else{Join-Path $base 'plugins/ascii-visor'}
  $message=(T 'Установить VISOR в:' 'Install VISOR to:')+"`n"+$target+"`n`n"+(T 'Предыдущая версия, если есть, будет сохранена в резервной папке.' 'An existing version will be preserved in a backup folder.')
  if([Windows.Forms.MessageBox]::Show($message,'ASCII VISOR','OKCancel','Information') -ne 'OK'){return}
  $install.Enabled=$false
  $backup=Install-VisorPackage $work $base $isPortable
  $message=(T 'Готово! Откройте OBS обычным способом или через Steam. Камера → Фильтры → Фильтры эффектов → ASCII VISOR.' 'Done! Start OBS normally or through Steam. Camera → Filters → Effect Filters → ASCII VISOR.')+"`n`n"+(T 'Резервная папка: ' 'Backup folder: ')+$backup
  [void][Windows.Forms.MessageBox]::Show($message,'ASCII VISOR','OK','Information')
  $form.Close()
 } catch { $install.Enabled=$true;[void][Windows.Forms.MessageBox]::Show($_.Exception.Message,'ASCII VISOR','OK','Error') }
})
if($PreviewPath){
 $form.Show();$form.Refresh()
 $bitmap=New-Object Drawing.Bitmap($form.Width,$form.Height)
 $form.DrawToBitmap($bitmap,(New-Object Drawing.Rectangle(0,0,$form.Width,$form.Height)))
 $bitmap.Save($PreviewPath,[Drawing.Imaging.ImageFormat]::Png);$bitmap.Dispose();$form.Close()
}else{[void]$form.ShowDialog()}
