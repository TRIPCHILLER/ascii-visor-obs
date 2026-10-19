# Install ASCII VISOR 0.3.1-rc1

This is a release candidate. Download packages from the candidate's **Assets** on [Releases](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/tag/v0.3.1-rc1) once published. Before publication, packages are available to testers through the draft PR's Actions artifacts. OBS must be installed separately; close OBS before installing or updating the plugin.

## Windows x64

Use `ASCII-VISOR-0.3.1-rc1-Windows-x64-Setup.exe`. Choose the shared installation for standard or Steam OBS, or select your portable OBS folder. The wizard creates the folders, preserves a previous plugin for rollback, and does not replace your OBS profiles or scenes. Tested with OBS 32.2.2.

For manual installation, extract the `Windows-x64-Plugin.zip` package into a temporary folder. Its `ascii-visor` folder contains `bin/64bit/ascii-visor.dll` and `data/`. Copy the complete `ascii-visor` folder into `%ProgramData%/obs-studio/plugins/` for standard/Steam OBS. For portable OBS, copy the DLL into `<OBS>/obs-plugins/64bit/` and the contents of `ascii-visor/data/` into `<OBS>/data/obs-plugins/ascii-visor/`. Keep licenses with the plugin. Do not copy a whole parent archive folder as the plugin.

## Linux x86_64

Use `ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.AppImage`. Make it executable in file properties, then launch it. Select native/Steam OBS or Flatpak as appropriate. The current build uses Ubuntu 24.04 (glibc 2.39) as its baseline and requires OBS 32.2 or newer. Older distributions need a compatible rebuild. ARM Linux is not included.

The AppImage includes Qt's X11 and Wayland backends. If FUSE is unavailable, run `./ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.AppImage --appimage-extract-and-run`. The alternative `Linux-x86_64-Setup.tar.gz` contains the same wizard without bundled Qt; it requires matching Qt 6 Widgets libraries on the host. Do not install arbitrary host Qt plugins into the AppImage.

For manual installation, extract `Linux-x86_64-Plugin.tar.gz` and copy its complete `ascii-visor` folder into `$XDG_CONFIG_HOME/obs-studio/plugins/`, or `~/.config/obs-studio/plugins/` when XDG_CONFIG_HOME is unset. For Flatpak use `~/.var/app/com.obsproject.Studio/config/obs-studio/plugins/`. The plugin and Flatpak OBS runtime must have compatible OBS and system libraries; selecting Flatpak does not guarantee ABI compatibility with every runtime.

## macOS · Apple Silicon and Intel

Use `ASCII-VISOR-0.3.1-rc1-macOS-universal-Setup.zip`. Unzip it, close OBS and open **ASCII VISOR Setup.app**. Select your **OBS.app**, usually `/Applications/OBS.app`. Keep the wizard and its resources together. Both the plugin and wizard contain arm64 and x86_64 code; separate Apple Silicon and Intel downloads are unnecessary.

The plugin targets macOS 12 or newer and OBS 31.1 or newer; the actual minimum can be higher because of your OBS or bundled Qt version. Native rendering checks use OBS 32.2.2 on both CPUs. The installer has an ad-hoc signature, without Developer ID signing or Apple notarization. If macOS blocks an otherwise trusted download, use its per-app **Privacy & Security → Open Anyway** option. Do not disable Gatekeeper globally. The wizard applies a local signature to the installed plugin.

For manual installation, unzip `macOS-universal-Plugin.zip` and place `ascii-visor.plugin` in `~/Library/Application Support/obs-studio/plugins/`. The `.plugin` is a complete bundle; do not move only its inner executable. The wizard is recommended because it also handles installation checks and local signing.

## Enable, update or remove

Open OBS → select a video source → **Filters → Effect Filters → + → ASCII ⛶ VISOR**. The filter follows the OBS language. Restart OBS after changing language or installing the plugin. The installer language is selected separately.

For updates, close OBS and rerun the installer for the same destination. If needed, use the wizard's previous-version restore option. For manual removal, close OBS and remove only the plugin folder/bundle described above (both files/directories for portable Windows), without deleting OBS settings or other plugins.

Verify downloads against `SHA256SUMS.txt`. GitHub's **Source code** ZIP and TAR.GZ contain source files, not ready-to-run installers. If the filter does not appear, include your OS, CPU, OBS version, installation type and OBS log when reporting the problem; do not include private keys or unrelated personal data.
