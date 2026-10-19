#!/usr/bin/env bash
set -euo pipefail
# Exercise the distributed AppImage, not the unbundled development executable.
# Weston is a real headless Wayland compositor; X11 must not mask missing plugins.
image="$PWD/ascii-visor-linux-setup-preview.AppImage"
results="$PWD/test-results/appimage"
mkdir -p "$results"
runtime=$(mktemp -d)
chmod 700 "$runtime"
weston_pid=''
cleanup() {
    if [[ -n "$weston_pid" ]]; then
        kill "$weston_pid" 2>/dev/null || true
        wait "$weston_pid" 2>/dev/null || true
    fi
    rmdir "$runtime" 2>/dev/null || true
}
trap cleanup EXIT

# Both CLI diagnostics must run without any valid display or platform plugin.
env -u DISPLAY -u WAYLAND_DISPLAY QT_QPA_PLATFORM=nonexistent timeout 30s "$image" --version 2>&1 | tee "$results/version.log"
env -u DISPLAY -u WAYLAND_DISPLAY QT_QPA_PLATFORM=nonexistent timeout 60s "$image" --self-test 2>&1 | tee "$results/self-test.log"

env -u WAYLAND_DISPLAY QT_QPA_PLATFORM=xcb xvfb-run -a timeout 60s "$image" --preview "$results/x11" 2>&1 | tee "$results/x11.log"
grep -F 'Installer display platform: xcb' "$results/x11.log"

XDG_RUNTIME_DIR="$runtime" weston --backend=headless-backend.so --socket=visor-wayland --idle-time=0 --no-config --log="$results/weston.log" &
weston_pid=$!
for ((attempt=0; attempt<100; attempt++)); do
    [[ -S "$runtime/visor-wayland" ]] && break
    if ! kill -0 "$weston_pid" 2>/dev/null; then cat "$results/weston.log"; exit 1; fi
    sleep 0.1
done
test -S "$runtime/visor-wayland"
# Explicit override reproduces the tester's desktop; automatic selection covers
# ordinary Wayland desktops without QT_QPA_PLATFORM in their environment.
for selection in explicit automatic; do
    platform=(env -u QT_QPA_PLATFORM)
    if [[ "$selection" == explicit ]]; then platform=(env QT_QPA_PLATFORM=wayland); fi
    env -u DISPLAY XDG_RUNTIME_DIR="$runtime" WAYLAND_DISPLAY=visor-wayland XDG_SESSION_TYPE=wayland \
        "${platform[@]}" timeout 60s "$image" --preview "$results/wayland-$selection" 2>&1 | tee "$results/wayland-$selection.log"
    grep -F 'Installer display platform: wayland' "$results/wayland-$selection.log"
done
