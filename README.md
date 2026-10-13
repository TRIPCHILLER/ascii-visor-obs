# ASCII ⛶ VISOR — OBS Edition

A native, real-time ASCII video filter for OBS Studio by **TRIPCHILLER**, based on ASCII VISOR 5.0.

Turn your webcam or another video source into live ASCII artwork. Control character sets, density, contrast, gamma, levels, palettes, transparency, mirroring and framing through the standard OBS Filters panel. The effect stays active when you close its settings.

## Status and downloads

Version **0.2.7** is being prepared for its first public release. Windows x64, **OBS Studio 32.2.2**. Other OBS versions and operating systems are not yet verified. Downloadable release assets will be published in [Releases](https://github.com/TRIPCHILLER/ascii-visor-obs/releases).

The author tested live Iriun Webcam, ordinary/Steam installation and restart persistence. In 0.2.7 the author confirmed that the new stable-character option resolves the distracting flicker in their setup. Moving test footage and controlled GPU tests also pass. All ten locale files pass completeness and module-loading checks. New translations still need native-speaker proofreading and visual layout review.

## Features

- Ten built-in character sets plus custom characters.
- Density from 30 to 150 characters across; default 100.
- Twenty VISOR color palettes and up to twenty saved custom color styles per filter.
- Contrast, gamma, black/white levels, inversion and horizontal mirroring.
- Stable characters enabled by default: suppresses small brightness-driven glyph changes; can be disabled for comparison.
- Character and background colors; optional transparent background between characters.
- Image scale, position and refresh rate controls.
- Russian, English, Spanish, Brazilian Portuguese, German, French, Japanese, Korean, Simplified Chinese and Traditional Chinese. Language follows OBS; English is the fallback.

Transparent background does not automatically remove the room or isolate a person: it makes the spaces between rendered characters transparent.

## Installation and use

See [INSTALL.md](INSTALL.md). The ordinary and Steam editions use the same plugin package; a separate archive layout is provided for portable OBS. This plugin does not include OBS itself and does not require launching the development demo.

Select a video source → **Filters** → add **ASCII ⛶ VISOR** under Effect Filters. Change the settings while watching the preview. Toggle the filter's eye icon to return to ordinary video.

## Build

Windows x64 and OBS 32.2.2 are required for the verified build.

1. Run `prepare-dependencies.ps1` to download the pinned portable compiler and OBS headers into this project folder. No system installation is performed.
2. Run `build.ps1 -OBSPath 'C:/Program Files/obs-studio'`, or supply your Steam OBS installation folder.
3. Distribute `build/ascii-visor.dll` together with the entire `data` folder and licenses.

Check translations with `python tests/check-translations.py`. Changing the OBS installation path does not establish compatibility with a different OBS version.

## Support the author

The plugin is free and open source. If you enjoy it, you can [support TRIPCHILLER on Boosty](https://boosty.to/tripchiller). Support is optional and does not unlock features.

## License

GPL-2.0-or-later. Bundled fonts use SIL Open Font License; see [THIRD_PARTY.md](THIRD_PARTY.md) and `data/fonts`. This is a community plugin and is not an official OBS Project product.


https://github.com/user-attachments/assets/067aa13c-cada-4ff3-859d-4025b0b72c82



https://github.com/user-attachments/assets/8ed8da50-d899-492f-a81a-4ccff01a9210



https://github.com/user-attachments/assets/30c21fb0-9aad-4652-9b45-b2c97a04a234



https://github.com/user-attachments/assets/772cb41e-769f-432c-b734-f8f910bb3957



https://github.com/user-attachments/assets/6e653001-9286-4655-aad6-fa029b3f2180

