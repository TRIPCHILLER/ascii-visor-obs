# Installation / Установка

Verified target: Windows x64, OBS Studio 32.2.2. Close OBS before copying or updating plugin files.

## Installer (recommended)

Run ASCII-VISOR-0.2.7-Setup.exe, confirm Windows administrator permission, and select Standard OBS / Steam. The installer detects compatible OBS in common locations and creates the plugin folder automatically. If detection fails, select your OBS bin/64bit/obs64.exe. Choose Portable OBS to install into a selected portable copy instead.

The installer UI is available in the same ten languages as the plugin, with native language names and flag icons. Existing plugin files are backed up, and OBS profiles and scenes are preserved. The executable is unsigned; the previous build passed user upgrade and clean-install tests in ordinary and Steam OBS. The author also verified the localized installer and its optional launch action in both editions.

## Ordinary OBS and Steam OBS

Extract the windows-x64 archive. Copy its `ascii-visor` folder to:

`C:\ProgramData\obs-studio\plugins\ascii-visor`

Result:

```text
ascii-visor/
  bin/64bit/ascii-visor.dll
  data/visor.effect
  data/locale/*.ini
  data/fonts/*
```

Launch OBS normally, or through Steam if you want Steam to register it as running. Add ASCII VISOR as an Effect Filter to your video source. Do not launch the development OPEN_VISOR command: it opens a separate portable test OBS.

The shared folder may make the plugin visible to multiple installed OBS versions. Only 32.2.2 has been verified. Do not use this package in other OBS versions until compatibility is confirmed.

## Portable OBS 32.2.2

Extract the portable archive into your OBS root directory, merging `obs-plugins` and `data`. The root is the directory containing `bin/64bit/obs64.exe`.

Do not install both layouts into the same OBS instance: duplicate copies can prevent reliable updates.

## Updates

Close OBS, preserve a backup of the plugin's existing DLL and data, then replace them with the matching files from the new release. Leave OBS profiles, collections and user settings untouched. New locale files are included in the same download. There is no built-in automatic updater.

## Removal

Close OBS. For the shared installation remove only C:\ProgramData\obs-studio\plugins\ascii-visor. For the portable layout remove only obs-plugins/64bit/ascii-visor.dll and data/obs-plugins/ascii-visor inside that portable OBS. Do not remove OBS itself, its other plugins, profiles or scene collections. The installer does not currently register an uninstaller.

## Quick checks

1. Add your camera and confirm ordinary video works.
2. Add the ASCII VISOR filter; start with density 100.
3. Test a character set, palette, contrast and gamma.
4. Close and reopen the settings; the filter should stay active.
5. Disable and enable it with the eye icon.
6. Restart OBS and check that your settings persist.
7. Make a short recording at your intended output size and inspect it at 100% scale.

## Кратко по-русски

Для обычной и Steam-версии OBS 32.2.2: закрыть OBS, распаковать windows-x64 и скопировать папку ascii-visor в C:\ProgramData\obs-studio\plugins. Затем открыть свою OBS обычным способом, выбрать камеру → Фильтры → Фильтры эффектов → ASCII VISOR.

Для переносной OBS: использовать архив portable, распаковав его в корневую папку своей OBS. Язык плагина следует за языком OBS после перезапуска.
