# Permanent platform downloads

README buttons point to `https://tripchiller.github.io/ascii-visor-obs/download/?platform=windows`, `linux` or `macos`. GitHub Pages serves the public `docs/` folder from main; it contains no credentials or private information.

The page reads the public GitHub Releases API on every visit, sorts published releases by `published_at`, ignores drafts and selects the newest release containing an uploaded installer for the requested platform. Pre-releases are included and visibly labelled. A release that omits one platform does not hide the preceding published installer for that platform.

Keep these installer filename endings when publishing future releases:

- `Windows-x64-Setup.exe`
- `Linux-x86_64-Setup.AppImage`
- `macOS-universal-Setup.zip`

The normal versioned prefix is `ASCII-VISOR-<version>-`. Legacy `ASCII-VISOR-0.2.8-Setup.exe` Windows assets remain recognized. Manual plugin archives and Linux setup TAR files do not qualify as primary installers.

The page never uses a token. It validates download URLs against this repository's GitHub release URLs and displays version names with `textContent`. If the API is unavailable/rate-limited, it presents a link to Releases instead of silently offering a possibly outdated cached version. It does not start a download without a user click.

Supported text languages are English and Russian, selected by `lang=en` / `lang=ru` or the browser language. Installation links jump to the chosen platform's section. `node tests/download-selector.cjs` checks selection, drafts, pre-releases, partial platform releases, legacy names and URL validation; the documentation workflow runs these checks automatically.
