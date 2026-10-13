# ASCII VISOR installer 0.2.6

Double-click ASCII-VISOR-0.2.6-Setup.exe. Windows requests administrator permission to write the shared plugin directory. Choose Russian or English in the top-right selector.

Close all OBS windows, select Standard OBS / Steam and click Install. OBS 32.2.2 is detected in common installation locations; if it is not found, select your obs64.exe. Confirm the destination. Directories are created automatically.

For portable OBS select Portable OBS, then choose that copy's bin/64bit/obs64.exe. The installer places the plugin DLL and data in that application's directories.

The installer validates the package before use, refuses incompatible OBS versions, leaves profiles and scene collections untouched, preserves old plugin files in visor-install-backups and rolls back file replacements on failure. Backup folders are retained deliberately. A uniquely named temporary extraction folder is retained for diagnostics.

This installer is not digitally signed. Windows will show an unknown publisher. Download it only from the project's GitHub release. The implementation does not provide automatic updates or an uninstaller; manual removal paths are documented in INSTALL.md.

## Build from the repository

Build the plugin first as described in the main README. Then run:

```powershell
./installer/build-setup.ps1
```

Pass -CompilerRoot if the portable compiler is in another location. The builder creates a payload from the built DLL, effect, ten locales, licensed fonts and GPL license, calculates a hash manifest, and embeds the ZIP and installation scripts as resources in the native executable.

## Verification

The installation engine was tested in new isolated directories: fresh standard and portable layouts, backup preservation, user-settings preservation, rollback, corrupted-package rejection, path containment and OBS version recognition. The Windows PowerShell 5.1 interface was rendered and inspected. An actual user run of the compiled executable with administrator confirmation remains necessary before publication.
