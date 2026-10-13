# Build


Windows x64 and OBS 32.2.2 are required for the verified build.

1. Run `prepare-dependencies.ps1` to download the pinned portable compiler and OBS headers into this project folder. No system installation is performed.
2. Run `build.ps1 -OBSPath 'C:/Program Files/obs-studio'`, or supply your Steam OBS installation folder.
3. Distribute `build/ascii-visor.dll` together with the entire `data` folder and licenses.

Check translations with `python tests/check-translations.py`. Changing the OBS installation path does not establish compatibility with a different OBS version.


## Scene transparency regression

After building, add your OBS `bin/64bit` folder to `PATH` and run `build/scene-transparency.exe <plugin-root> <output-prefix> <OBS-root>`. Use this repository as the plugin root, supply your OBS installation directory, and choose a private output directory for the generated PPM files. The test uses synthetic sources and verifies actual compositing over a colored background, including fresh and cached frames. It does not access a webcam or change OBS scenes.
