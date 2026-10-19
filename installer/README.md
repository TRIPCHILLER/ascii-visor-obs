# ASCII VISOR installer 0.2.6

Double-click ASCII-VISOR-0.2.6-Setup.exe. Windows requests administrator permission to write the shared plugin directory. Choose one of ten languages in the top-right selector. Native language names and bitmap flag icons help identify each language.

Close all OBS windows, select Standard OBS / Steam and click Install. OBS 32.2.2 is detected in common installation locations; if it is not found, select your obs64.exe. Confirm the destination. Directories are created automatically.

For portable OBS select Portable OBS, then choose that copy's bin/64bit/obs64.exe. The installer places the plugin DLL and data in that application's directories.

The installer validates the package before use, refuses incompatible OBS versions, leaves profiles and scene collections untouched, preserves old plugin files in visor-install-backups and rolls back file replacements on failure. Backup folders are retained deliberately. A uniquely named temporary extraction folder is retained for diagnostics.

This installer is not digitally signed. Windows will show an unknown publisher. Download it only from the project's GitHub release. The finish screen can optionally launch the selected OBS or launch through Steam when available. Launch requests are delegated to the existing desktop Explorer to avoid inheriting the installer administrator token (https://devblogs.microsoft.com/oldnewthing/20131118-00/?p=2643). A small launch probe confirmed ordinary user permissions. If desktop Explorer is unavailable, the installer asks the user to open OBS manually. The implementation does not provide automatic updates or an uninstaller; manual removal paths are documented in the [current installation guide](../docs/INSTALL.en.md).

## Build from the repository

Build the plugin first as described in the main README. Then run:

```powershell
./installer/build-setup.ps1
```

Pass -CompilerRoot if the portable compiler is in another location. The builder creates a payload from the built DLL, effect, ten locales, licensed fonts and GPL license, calculates a hash manifest, and embeds the ZIP and installation scripts as resources in the native executable.

## Verification

The installation engine was tested in new isolated directories: fresh standard and portable layouts, backup preservation, user-settings preservation, rollback, corrupted-package rejection, path containment and OBS version recognition. The Windows PowerShell 5.1 interface was rendered and inspected. The author confirmed both upgrade and clean installation with the previous two-language build in ordinary and Steam OBS 32.2.2. R3 adds ten languages, flags, translated credits and an optional launch choice on the finish screen. Its native window launch, language completeness, initial/finish layouts and installation engine have been checked; a user run of R3 and its optional OBS/Steam launch remain to be confirmed.


## Branding (R4)

The installer executable and window use TRIPCHILLER's supplied vector logo. A derived icon adds a dark rounded tile and inset spacing so the white mark remains visible on light backgrounds. The ICO contains 16, 20, 24, 32, 40, 48, 64, 128 and 256 pixel sizes. Original-logo.svg is an unchanged copy; installer-icon.svg contains the derived backing tile. The prebuilt ICO is included, so compiling the installer does not require a graphics application.

R3 upgrade, clean installation and optional ordinary/Steam launch were confirmed by the author. R4 changes the installer icon and window branding; its native window and embedded icon have been verified.
