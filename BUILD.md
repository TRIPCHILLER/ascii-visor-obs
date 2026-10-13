# Build


Windows x64 and OBS 32.2.2 are required for the verified build.

1. Run `prepare-dependencies.ps1` to download the pinned portable compiler and OBS headers into this project folder. No system installation is performed.
2. Run `build.ps1 -OBSPath 'C:/Program Files/obs-studio'`, or supply your Steam OBS installation folder.
3. Distribute `build/ascii-visor.dll` together with the entire `data` folder and licenses.

Check translations with `python tests/check-translations.py`. Changing the OBS installation path does not establish compatibility with a different OBS version.

