"""Assemble adjacent installer resources; executed only on a build runner."""
import hashlib
import json
import pathlib
import shutil
import sys

root = pathlib.Path(__file__).resolve().parents[2]
destination = pathlib.Path(sys.argv[1])
plugin = pathlib.Path(sys.argv[2])
destination.mkdir(parents=True, exist_ok=True)
shutil.copy2(root / "installer/locales.json", destination / "locales.json")
shutil.copy2(root / "installer/branding/installer-icon.png", destination / "installer-icon.png")
shutil.copytree(root / "installer/native/flags", destination / "flags")
payload = destination / "payload"
payload.mkdir()
shutil.copytree(plugin, payload / plugin.name)
manifest = []
for f in sorted(payload.rglob("*")):
    if f.is_symlink():
        raise RuntimeError(f"Unexpected symlink in plugin: {f}")
    if f.is_file():
        manifest.append({"path": f.relative_to(payload).as_posix(), "sha256": hashlib.sha256(f.read_bytes()).hexdigest()})
(payload / "manifest.json").write_text(json.dumps(manifest, indent=2), encoding="utf-8")
for name in ("LICENSE", "THIRD_PARTY.md"):
    shutil.copy2(root / name, destination / name)
