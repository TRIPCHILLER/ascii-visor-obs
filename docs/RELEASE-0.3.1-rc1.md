# ASCII VISOR 0.3.1-rc1 — Windows, Linux & macOS

Turn your camera and video into live character art inside OBS Studio. This release candidate brings the approved PIXEL, DOTS and Katakana improvements to all three platforms, with graphical installers and ten interface languages.

## Download

| Your system | Recommended download |
|---|---|
| Windows x64 | [Windows installer](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Windows-x64-Setup.exe) |
| Linux x86_64 | [Linux AppImage installer](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.AppImage) |
| macOS · Apple Silicon + Intel | [Universal macOS installer ZIP](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-macOS-universal-Setup.zip) |

Close OBS before installing. On macOS unzip and open **ASCII VISOR Setup.app**; on Linux allow execution of the AppImage. Then open OBS → source → **Filters → Effect Filters → + → ASCII ⛶ VISOR**.

[Installation guide](https://github.com/TRIPCHILLER/ascii-visor-obs/blob/feature/cross-platform-obs/docs/INSTALL.en.md) · [Инструкция на русском](https://github.com/TRIPCHILLER/ascii-visor-obs/blob/feature/cross-platform-obs/docs/INSTALL.ru.md)

## What changed

- **DOTS:** consistent pixel circles with five filled sizes plus blank background.
- **PIXEL:** sharp squares with five filled sizes plus blank background.
- **Katakana:** clearer, denser Japanese pixel glyphs using PixelMplus12 Bold.
- Removed obsolete DOTS/PIXEL variants and duplicate names; saved legacy selections migrate to the supported sets.
- Renamed **Custom input** and clarified its prompt in all ten languages: up to 128 unique characters.
- Linux installer includes X11 and Wayland components. macOS packages are universal, with the same localized wizard tested in the preceding preview.

CLASSIC, NUMBERS, LATIN, CYRILLIC, BLOCKS and custom rendering keep their original font and behavior. Experimental size and randomization variants are not included.

## Compatibility

- Windows x64: tested with OBS 32.2.2, standard/Steam/portable installation.
- Linux x86_64: Ubuntu 24.04 / glibc 2.39 baseline, OBS 32.2+. Flatpak needs a compatible OBS runtime; older distributions may require a rebuild.
- macOS: universal arm64 + x86_64; plugin target macOS 12+ and OBS 31.1+, subject to the higher requirements of OBS and bundled Qt. Packages have ad-hoc signatures, without Apple notarization. Use a per-app security exception if required; do not disable Gatekeeper globally.

This is a **pre-release** for wider testing. Please report your OS, CPU, OBS version and installation type with any issue.

<details>
<summary>Manual installation, alternative packages and checksums</summary>

- `ASCII-VISOR-0.3.1-rc1-Windows-x64-Plugin.zip` — manual Windows installation.
- `ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Plugin.tar.gz` — manual Linux installation.
- `ASCII-VISOR-0.3.1-rc1-macOS-universal-Plugin.zip` — manual macOS plugin bundle.
- `ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.tar.gz` — Linux wizard without bundled Qt; requires compatible host Qt 6 Widgets.
- `SHA256SUMS.txt` — checksums for the seven downloadable packages.
- GitHub **Source code** archives — for developers; not installers.

</details>

<details>
<summary>Что нового — на русском</summary>

Новые PIXEL и DOTS с пятью размерами фигур и пустым фоном, более читаемая пиксельная катакана, единые названия без старых дублей и обновлённые подписи собственного ввода на десяти языках. Остальные наборы сохраняют прежний шрифт и логику.

Сверху выберите установщик для своей системы. Для Mac нужен один universal-архив — он подходит и Apple Silicon, и Intel. Для Linux основной вариант — AppImage с поддержкой X11 и Wayland. В разделе Assets находятся также архивы ручной установки и контрольные суммы. Эта версия предназначена для проверки перед основным релизом.

</details>
