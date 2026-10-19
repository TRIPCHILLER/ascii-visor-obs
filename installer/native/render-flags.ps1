$ErrorActionPreference='Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -Path (Join-Path $PSScriptRoot '../flags.cs') -ReferencedAssemblies System.Drawing.dll,System.dll
$destination=Join-Path $PSScriptRoot 'flags'
New-Item -ItemType Directory -Path $destination -Force | Out-Null
foreach($code in @('ru-RU','en-US','es-ES','pt-BR','de-DE','fr-FR','ja-JP','ko-KR','zh-CN','zh-TW')){
 $bitmap=[VisorFlags]::Create($code)
 $bitmap.Save((Join-Path $destination ($code+'.png')),[Drawing.Imaging.ImageFormat]::Png)
 $bitmap.Dispose()
}
