#!/usr/bin/env bash
set -euo pipefail
# Bundle the wizard and Qt. Add the OBS payload after dependency deployment so
# the host OBS libraries are never copied into the installer runtime.
export ARCH=x86_64
export APPIMAGE_EXTRACT_AND_RUN=1
export QMAKE=/usr/bin/qmake6
# Widgets do not link QtWayland directly, so automatic dependency discovery
# otherwise includes xcb only. Bundle the client backends and their integrations.
export EXTRA_PLATFORM_PLUGINS='libqwayland-egl.so;libqwayland-generic.so'
export EXTRA_QT_MODULES=waylandcompositor
mkdir -p appimage-tools AppDir/usr/bin
curl -fL --retry 3 https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage -o appimage-tools/linuxdeploy
curl -fL --retry 3 https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage -o appimage-tools/linuxdeploy-plugin-qt
curl -fL --retry 3 https://github.com/AppImage/appimagetool/releases/download/continuous/appimagetool-x86_64.AppImage -o appimage-tools/appimagetool
chmod +x appimage-tools/*
export PATH="$PWD/appimage-tools:$PATH"
cp 'build_x86_64/installer/native/ASCII VISOR Setup' AppDir/usr/bin/ascii-visor-setup
cp installer/branding/installer-icon.png AppDir/ascii-visor.png
cat > AppDir/ascii-visor-setup.desktop <<'EOF'
[Desktop Entry]
Type=Application
Name=ASCII VISOR Setup
Exec=ascii-visor-setup
Icon=ascii-visor
Categories=AudioVideo;
Terminal=false
EOF
linuxdeploy --appdir AppDir --executable AppDir/usr/bin/ascii-visor-setup --desktop-file AppDir/ascii-visor-setup.desktop --icon-file AppDir/ascii-visor.png --plugin qt
for plugin in platforms/libqxcb.so platforms/libqwayland-egl.so platforms/libqwayland-generic.so wayland-shell-integration/libxdg-shell.so; do
    test -f "AppDir/usr/plugins/$plugin"
done
python3 installer/native/package.py AppDir/usr/bin preview/ascii-visor
appimagetool AppDir ascii-visor-linux-setup-preview.AppImage
chmod +x ascii-visor-linux-setup-preview.AppImage
bash installer/native/test-linux-displays.sh
