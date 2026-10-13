$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot
$downloads = @(
 @{Folder='tools';Name='llvm-mingw.zip';Url='https://github.com/mstorsjo/llvm-mingw/releases/download/20261006/llvm-mingw-20261006-ucrt-x86_64.zip';Hash='317492C456AA27EE607A5919F1D2D38DCDC1112516A24D0BF4B00D078F52D17A';Target='llvm-mingw-20261006-ucrt-x86_64'},
 @{Folder='vendor';Name='obs-studio-32.2.2.zip';Url='https://github.com/obsproject/obs-studio/archive/refs/tags/32.2.2.zip';Hash='F15F001F1FA526405318835F44F9910046502F496EBC3A30D5296A5018B831AA';Target='obs-studio-32.2.2'}
)
foreach ($download in $downloads) {
 $folder = Join-Path $root $download.Folder
 $target = Join-Path $folder $download.Target
 if (Test-Path -LiteralPath $target) { Write-Host "Already present: $target"; continue }
 New-Item -ItemType Directory -Force -Path $folder | Out-Null
 $archive = Join-Path $folder $download.Name
 if (!(Test-Path -LiteralPath $archive)) { Invoke-WebRequest $download.Url -OutFile $archive }
 if ((Get-FileHash -LiteralPath $archive).Hash -ne $download.Hash) { throw "Checksum mismatch: $archive. Nothing extracted." }
 Expand-Archive -LiteralPath $archive -DestinationPath $folder
}
Write-Host 'Local build dependencies ready. No system installation performed.'
