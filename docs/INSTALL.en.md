# Install ASCII ⛶ VISOR

Choose your system: **[Windows](#windows) · [Linux](#linux) · [macOS](#macos)**.

The plugin is free. Install [OBS Studio](https://obsproject.com/) first and completely close it before installing or updating VISOR.

The buttons below find the newest published installer for your platform. The download page displays its version and labels pre-releases clearly. GitHub **Source code** archives are not installers.

---

<a name="windows"></a>

# 🪟 Windows

**Windows x64 · standard, Steam and portable OBS**

### 1. Download the installer

Open the link below and select **Download installer**. Use **Windows-x64-Setup.exe**; older versions may simply end with **Setup.exe**.

**[↓ Download the latest installer](https://tripchiller.github.io/ascii-visor-obs/download/?platform=windows&lang=en)**

### 2. Open the downloaded file

Close OBS, run the `.exe` and choose your installer language.

### 3. Choose your OBS installation

For standard or Steam OBS, choose the **shared standard/Steam installation**. For portable OBS, choose **portable installation** and select your OBS folder. The wizard creates the folders.

### 4. Install and open OBS

Select **Install**, wait for completion, then reopen OBS and [enable the filter](#enable). The previous plugin is kept for rollback; profiles and scenes are not replaced.

<details>
<summary>Requirements, manual installation and alternatives</summary>

Use `ASCII-VISOR-0.3.1-rc1-Windows-x64-Setup.exe`. Choose the shared installation for standard or Steam OBS, or select your portable OBS folder. The wizard creates the folders, preserves a previous plugin for rollback, and does not replace your OBS profiles or scenes. Tested with OBS 32.2.2.

For manual installation, extract the `Windows-x64-Plugin.zip` package into a temporary folder. Its `ascii-visor` folder contains `bin/64bit/ascii-visor.dll` and `data/`. Copy the complete `ascii-visor` folder into `%ProgramData%/obs-studio/plugins/` for standard/Steam OBS. For portable OBS, copy the DLL into `<OBS>/obs-plugins/64bit/` and the contents of `ascii-visor/data/` into `<OBS>/data/obs-plugins/ascii-visor/`. Keep licenses with the plugin. Do not copy a whole parent archive folder as the plugin.

</details>

---

<a name="linux"></a>

# 🐧 Linux

**Linux x86_64 · OBS 32.2+ · Ubuntu 24.04 / glibc 2.39 or newer**

### 1. Download the AppImage

Open the link below and select **Download installer**. Use **Setup.AppImage**, which includes the graphical wizard’s libraries.

**[↓ Download the latest installer](https://tripchiller.github.io/ascii-visor-obs/download/?platform=linux&lang=en)**

### 2. Allow it to run

Right-click the file → **Properties → Permissions** → allow execution as a program. The wording depends on your desktop environment.

### 3. Open the wizard and choose OBS

Close OBS and open the AppImage. Select **Native / Steam** for standard or Steam OBS, or **Flatpak** for Flatpak OBS. Select your OBS executable if needed and check the displayed destination.

### 4. Install and enable the effect

Select **Install**, reopen OBS as usual, then [enable the filter](#enable). The AppImage includes both X11 and Wayland support.

<details>
<summary>Requirements, manual installation and alternatives</summary>

Use `ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.AppImage`. Make it executable in file properties, then launch it. Select native/Steam OBS or Flatpak as appropriate. The current build uses Ubuntu 24.04 (glibc 2.39) as its baseline and requires OBS 32.2 or newer. Older distributions need a compatible rebuild. ARM Linux is not included.

The AppImage includes Qt's X11 and Wayland backends. If FUSE is unavailable, run `./ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.AppImage --appimage-extract-and-run`. The alternative `Linux-x86_64-Setup.tar.gz` contains the same wizard without bundled Qt; it requires matching Qt 6 Widgets libraries on the host. Do not install arbitrary host Qt plugins into the AppImage.

For manual installation, extract `Linux-x86_64-Plugin.tar.gz` and copy its complete `ascii-visor` folder into `$XDG_CONFIG_HOME/obs-studio/plugins/`, or `~/.config/obs-studio/plugins/` when XDG_CONFIG_HOME is unset. For Flatpak use `~/.var/app/com.obsproject.Studio/config/obs-studio/plugins/`. The plugin and Flatpak OBS runtime must have compatible OBS and system libraries; selecting Flatpak does not guarantee ABI compatibility with every runtime.

</details>

---

<a name="macos"></a>

# 🍎 macOS

**One universal package for Apple Silicon and Intel**

### 1. Download the ZIP

Open the link below and select **Download installer**. Use **macOS-universal-Setup.zip**. Separate Apple Silicon and Intel downloads are unnecessary.

**[↓ Download the latest installer](https://tripchiller.github.io/ascii-visor-obs/download/?platform=macos&lang=en)**

### 2. Unzip and open the app

Close OBS. Double-click the ZIP, then open **ASCII VISOR Setup.app**. Keep the application bundle intact.

### 3. Select OBS and install

Choose your **OBS.app**, usually in **Applications**. Check the displayed location and select **Install**. The wizard installs and locally signs the plugin.

### 4. Open OBS

Start OBS and [enable the filter](#enable). If macOS blocks a trusted download, use its per-app **System Settings → Privacy & Security → Open Anyway** option. Do not disable Gatekeeper globally. This candidate is ad-hoc signed without Apple notarization.

<details>
<summary>Requirements, manual installation and alternatives</summary>

Use `ASCII-VISOR-0.3.1-rc1-macOS-universal-Setup.zip`. Unzip it, close OBS and open **ASCII VISOR Setup.app**. Select your **OBS.app**, usually `/Applications/OBS.app`. Keep the wizard and its resources together. Both the plugin and wizard contain arm64 and x86_64 code; separate Apple Silicon and Intel downloads are unnecessary.

The plugin targets macOS 12 or newer and OBS 31.1 or newer; the actual minimum can be higher because of your OBS or bundled Qt version. Native rendering checks use OBS 32.2.2 on both CPUs. The installer has an ad-hoc signature, without Developer ID signing or Apple notarization. If macOS blocks an otherwise trusted download, use its per-app **Privacy & Security → Open Anyway** option. Do not disable Gatekeeper globally. The wizard applies a local signature to the installed plugin.

For manual installation, unzip `macOS-universal-Plugin.zip` and place `ascii-visor.plugin` in `~/Library/Application Support/obs-studio/plugins/`. The `.plugin` is a complete bundle; do not move only its inner executable. The wizard is recommended because it also handles installation checks and local signing.

</details>

---

<a name="enable"></a>

# ✨ Enable VISOR in OBS — all platforms

1. Select your camera or another video source in **Sources**.
2. Open its **Filters**.
3. Under **Effect Filters**, select **+ → ASCII ⛶ VISOR**.
4. Choose a character set and palette. Adjust density, contrast and gamma to suit your image.

The effect appears in the preview and in recordings or streams. Use the eye icon to compare with the original video. Closing the filter window keeps the effect active, and settings are saved.

# Updates and help

Open OBS → select a video source → **Filters → Effect Filters → + → ASCII ⛶ VISOR**. The filter follows the OBS language. Restart OBS after changing language or installing the plugin. The installer language is selected separately.

For updates, close OBS and rerun the installer for the same destination. If needed, use the wizard's previous-version restore option. For manual removal, close OBS and remove only the plugin folder/bundle described above (both files/directories for portable Windows), without deleting OBS settings or other plugins.

Verify downloads against `SHA256SUMS.txt`. GitHub's **Source code** ZIP and TAR.GZ contain source files, not ready-to-run installers. If the filter does not appear, include your OS, CPU, OBS version, installation type and OBS log when reporting the problem; do not include private keys or unrelated personal data.
