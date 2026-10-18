# ASCII VISOR: cross-platform preview

This branch prepares 0.3.0. The published Windows release remains 0.2.8.
Do not describe these previews as a fully tested stable release.

## Packages

* Windows x64: existing GDI renderer and Windows setup remain supported. The
  Windows build script remains available; the experimental CMake route does not
  replace the published Windows installer.
* Linux x86_64: Ubuntu 24.04 build, native OBS and optional Flatpak destination.
  `ascii-visor-linux-setup-preview.AppImage` contains the graphical setup wizard
  and its Qt runtime. Make it executable and launch it. Systems without FUSE can
  use `--appimage-extract-and-run`. The fallback setup tarball needs Qt 6 Widgets.
* macOS: universal arm64 + x86_64 `.plugin` and a graphical setup `.app` distributed
  as ZIP. The setup app includes Qt. The bundle targets macOS 12+, subject to the
  requirements of the installed OBS version and the bundled Qt libraries.

The setup wizard reuses the existing logo, flags, and ten translations. It
supports choosing an OBS application/executable, automatic per-user plugin
destination, a custom plugins directory, upgrading with a backup, and optional
OBS launch. Linux additionally offers Flatpak and Steam launch when available.
The Flatpak destination is an experimental compatibility option: selecting a
folder does not prove runtime/ABI compatibility with every Flatpak release.
macOS does not offer a Windows portable/Steam layout.

## Installation behaviour

Close OBS before installing. The setup checks the selected OBS version against the actual SDK API (Linux 32.2+, macOS 31.1+ for
these previews), validates every payload file against its SHA-256 manifest, stages
files in the destination filesystem, and renames the previous plugin to a
unique `.visor-backup-*` directory. A failed final rename restores the old
plugin. Scenes, profiles, presets, and other OBS plugins are not edited.
Backups are intentionally retained; remove an old backup only after testing.

Default plugin roots:

* Linux: `$XDG_CONFIG_HOME/obs-studio/plugins` or `~/.config/obs-studio/plugins`.
* Flatpak: `~/.var/app/com.obsproject.Studio/config/obs-studio/plugins`.
* macOS: `~/Library/Application Support/obs-studio/plugins`.

The Linux plugin tarball contains `ascii-visor/bin/64bit/ascii-visor.so` and
`ascii-visor/data`. The Mac plugin bundle contains its own `Contents/Resources`.
Manual installation follows the official OBS plugins guide:
https://obsproject.com/kb/plugins-guide

## macOS distribution limits

Preview packages have ad-hoc signatures, not Developer ID signatures or Apple
notarization. Gatekeeper may require explicit approval in Privacy & Security.
Do not disable Gatekeeper globally. The wizard signs the installed plugin
locally with `/usr/bin/codesign --force --sign -`.
For a normal public release with fewer security prompts, configure Developer ID
Application signing and notarization; the official OBS template documents this:
https://github.com/obsproject/obs-plugintemplate/wiki/Codesigning-On-macOS

## Rendering changes

Windows retains private GDI fonts. Linux/macOS use statically linked FreeType
2.13.3 and the same bundled Better VCR and Noto fonts. Fonts are never installed
system-wide. Unicode parsing accepts scalar values, deduplicates characters,
rejects invalid UTF-8, and preserves stable density sorting. Missing glyphs are
reported in the OBS log. Different rasterizers can produce small visual
differences; exact pixel equality with GDI is not promised.
PIXEL2/DOTS2 shapes and the GPU shaders, filter identifier, palettes, settings,
stability hysteresis, and alpha-compositing logic remain shared.

## Building

The CMake infrastructure is adapted from the official OBS plugin template at
commit `3e7d7ac3b5342cd7d9b88890b9c70b472d1520fc`, under GPL-2.0-or-later.
The matching macdeployqt deployment tool is built from three checksum-verified Qt 6.8.3 source files; it is not included in user packages.
Its pinned macOS SDK configuration uses OBS 31.1.1 and obs-deps 2025-07-11,
including published dependency checksums. Runtime regression testing uses OBS
32.2.2. The Linux job uses the official OBS PPA and records the installed version
in its log; it is not a bit-for-bit reproducible package source.

On Linux install OBS development headers (provided by the OBS PPA package),
Ninja, libsimde-dev, libgles2-mesa-dev, libx11-dev and qt6-base-dev. Do not mix
Ubuntu's old libobs-dev package with the PPA's OBS package: they conflict.

```
cmake --preset ubuntu-x86_64 -DENABLE_QT=ON -DCMAKE_COMPILE_WARNING_AS_ERROR=OFF
cmake --build --preset ubuntu-x86_64 --parallel 4
ctest --test-dir build_x86_64 --output-on-failure
```

On macOS use Xcode 16+ and CMake 3.28+; the preset downloads checked OBS SDK
dependencies and builds both architectures:

```
cmake --preset macos -DENABLE_QT=ON -DCMAKE_COMPILE_WARNING_AS_ERROR=OFF
cmake --build --preset macos --parallel 4
ctest --test-dir build_macos -C RelWithDebInfo --output-on-failure
```

Set `ENABLE_QT=OFF` for plugin-only builds. See
`.github/workflows/cross-platform.yml` for packaging and actual rendering tests.
The workflow has read-only repository permissions and publishes artifacts only;
it does not create or replace public releases.

FreeType is fetched from its upstream `VER-2-13-3` tag and statically linked with
optional compression/shaping libraries disabled. Font rasterization is performed
only when the atlas changes, not for every video frame. Source:
https://github.com/freetype/freetype/tree/VER-2-13-3

Qt is dynamically linked in the graphical installer, not in the filter. Mac Qt
comes from the OBS template's checked Qt dependency; Linux Qt comes from Ubuntu
and is bundled into the AppImage. Qt source and rebuild instructions:
https://code.qt.io/cgit/qt/qtbase.git/ and https://doc.qt.io/qt-6/build-sources.html
The installer includes LGPLv3/GPLv3 license texts and supports replacing its
dynamically linked Qt libraries. Qt source must remain available under its
license when distributing binaries. AppImage deployment tools are downloaded
from upstream continuous releases; pin their binaries/checksums before a stable
release. FreeType's FTL notice is included with installer resources.

## Release checklist

1. Confirm Linux native OBS load, all 11 character sets, custom Cyrillic/CJK,
   transparency over another source, stability, FPS caching, palette save/delete.
2. Repeat on both a real Apple Silicon Mac and an Intel Mac. A universal binary
   architecture check alone does not establish rendering on both CPUs.
3. Test Linux Wayland, Flatpak runtime matching and at least one additional
   distribution. The Ubuntu/Xvfb test does not cover all Linux GPU drivers.
4. Review all ten installer language screenshots and test fresh install,
   upgrade, backup restore and optional launching in interactive OBS sessions.
5. Sign/notarize Mac release packages, pin deployment tools, include license
   notices, and only then update the public platform badges/release notes.

No camera, personal media, real OBS profile, or production installation is used
by the synthetic rendering and installer filesystem tests.
