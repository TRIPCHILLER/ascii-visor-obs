<p align="center"><picture><source media="(prefers-color-scheme: dark)" srcset="docs/media/visor-logo-white.svg"><source media="(prefers-color-scheme: light)" srcset="docs/media/visor-logo-dark.svg"><img src="docs/media/visor-logo-dark.svg" width="112" alt="ASCII VISOR"></picture></p>

<h1 align="center">ASCII ⛶ VISOR · OBS Edition</h1>

<p align="center"><b>カメラや動画を、<a href="https://obsproject.com/">OBS Studio</a>でリアルタイムの文字アートに。</b></p>

<p align="center">ASCII ⛶ VISOR 5.0を基に開発 · 制作者： <a href="https://github.com/TRIPCHILLER">TRIPCHILLER</a></p>

<p align="center"><a href="README.md"><img src="docs/media/flags/us.svg" width="24" height="16" alt="US"> English</a> · <a href="README.ru.md"><img src="docs/media/flags/ru.svg" width="24" height="16" alt="RU"> Русский</a> · <a href="README.es.md"><img src="docs/media/flags/es.svg" width="24" height="16" alt="ES"> Español</a> · <a href="README.pt-BR.md"><img src="docs/media/flags/br.svg" width="24" height="16" alt="BR"> Português (Brasil)</a> · <a href="README.de.md"><img src="docs/media/flags/de.svg" width="24" height="16" alt="DE"> Deutsch</a> · <a href="README.fr.md"><img src="docs/media/flags/fr.svg" width="24" height="16" alt="FR"> Français</a> · <b><img src="docs/media/flags/jp.svg" width="24" height="16" alt="JP"> 日本語</b> · <a href="README.ko.md"><img src="docs/media/flags/kr.svg" width="24" height="16" alt="KR"> 한국어</a> · <a href="README.zh-CN.md"><img src="docs/media/flags/cn.svg" width="24" height="16" alt="CN"> 简体中文</a> · <a href="README.zh-TW.md"><img src="docs/media/flags/tw.svg" width="24" height="16" alt="TW"> 繁體中文</a></p>

<p align="center"><b>Windows x64 · <a href="https://obsproject.com/">OBS Studio</a> 32.2.2で検証済み · 通常版・Steam版 · 無料</b></p>

<p align="center"><a href="https://github.com/TRIPCHILLER/ascii-visor-obs/releases/latest/download/ASCII-VISOR-0.2.7-Setup.exe"><b>⬇ インストーラーをダウンロード</b></a> · <a href="#-クイックスタート">🚀 クイックスタート</a> · <a href="https://boosty.to/tripchiller">☕ 作者を支援</a></p>

![ASCII ⛶ VISOR](docs/media/ascii_visor_preview.png)

**ASCII ⛶ VISOR**は、Webカメラや他の映像ソースをリアルタイムでASCIIアートに変換する[OBS Studio](https://obsproject.com/)用映像フィルタープラグインです。文字、色、密度を選び、シーンに合う見た目に調整できます。変更はすぐにプレビューに反映され、録画や配信にも適用されます。

個性的なカメラ演出、クリエイティブな配信、音楽ライブ、映像実験に。

## ✨ 機能

| 機能 | 使い方 |
|---|---|
| **10種類の文字セット** | クラシックASCII、さまざまな文字、幾何学模様で質感を変更。 |
| **カスタム文字** | 自分の文字セットを入力して独自のスタイルを作成。 |
| **20種類のカラーパレット** | 用意されたスタイルや好きな色を選択。 |
| **カラースタイルの保存** | フィルターごとに最大20種類の色プリセットを保存。 |
| **透明背景** | 文字の隙間を透明にしてゲームや動画に重ねる。 |
| **映像調整** | 密度、コントラスト、ガンマ、黒・白レベル、拡大率、位置を調整。 |
| **OBS内で操作** | 通常のフィルター画面から操作し、録画や配信に使用。 |

密度は**横幅30〜150文字**。文字セットとパレットは自由に組み合わせられます。

### 🎨 カラースタイル

同じ映像でも印象を変えられます。パレットを切り替えたり、文字と背景の色を自分で選んだりできます。

https://github.com/user-attachments/assets/30c21fb0-9aad-4652-9b45-b2c97a04a234

### 🔤 文字セットとカスタム入力

お気に入りのパレットを保ったまま、**10種類のセット**から選べます。クラシックASCII、別の文字体系、数字、幾何学模様が、それぞれ異なる質感を作ります。

https://github.com/user-attachments/assets/8ed8da50-d899-492f-a81a-4ccff01a9210

自分だけの見た目にしたいなら、**カスタム**を選んで使いたい文字を入力。組み合わせを試して、自分のスタイルを見つけましょう。

https://github.com/user-attachments/assets/067aa13c-cada-4ff3-859d-4025b0b72c82

### 🎛️ リアルタイム調整

照明やシーン内のカメラの大きさに合わせて密度と階調を調整します。変更はプレビューにすぐ反映されます。

https://github.com/user-attachments/assets/772cb41e-769f-432c-b734-f8f910bb3957

### 🫧 シーンに合わせた透明背景

透明背景では、文字の隙間からゲーム、動画、他のソースが見えます。ASCIIカメラを配信のレイアウトに重ねられます。

透明になるのは文字の隙間です。人物と部屋を自動的に切り分ける機能ではありません。重ね合わせのデモは後日追加します。

<a name="quick-start"></a>

## 🚀 クイックスタート

1. 上のリンク、またはリリースページの**Assets**から**ASCII-VISOR-0.2.7-Setup.exe**をダウンロードします。
2. OBSのウィンドウをすべて閉じ、インストーラーを実行します。
3. **通常版OBS / Steam — 共通インストール**を選びます。ポータブル版では専用の項目とフォルダーを選択します。
4. OBSを開き、カメラや他の映像ソースを選択します。
5. ソースを右クリック → **フィルタ → エフェクトフィルタ → + → ASCII ⛶ VISOR**。
6. フィルター一覧でプラグイン名をクリックして設定を開きます。文字、色、密度を自由に調整して、楽しみながら試してみてください！

https://github.com/user-attachments/assets/6e653001-9286-4655-aad6-fa029b3f2180

目のアイコンで元の映像と比較できます。設定画面を閉じても効果は有効で、OBSを再起動しても設定は保存されます。

### 📦 ダウンロードするファイル

| ファイル | 用途 |
|---|---|
| **[ASCII-VISOR-0.2.7-Setup.exe](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.2.7/ASCII-VISOR-0.2.7-Setup.exe)** | 推奨。通常版・Steam版・ポータブル版に対応し、必要なフォルダーを自動作成。 |
| **[ascii-visor-0.2.7-windows-x64.zip](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.2.7/ascii-visor-0.2.7-windows-x64.zip)** | 通常版・Steam版の手動インストール用。 |
| **[ascii-visor-0.2.7-portable.zip](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.2.7/ascii-visor-0.2.7-portable.zip)** | ポータブル版の手動インストール用。 |
| **[ascii-visor-0.2.7-source.zip](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.2.7/ascii-visor-0.2.7-source.zip)** | 開発者向けソースコード。利用には不要。 |

手動インストール、更新、削除：[INSTALL.md](INSTALL.md)。

## 🌍 インターフェースの10言語

プラグインとインストーラーは次の言語に対応しています。プラグインの言語はOBSに従います。変更後はOBSを再起動してください。インストーラーの言語は別途選べます。

| | 言語 | ロケール |
|---|---|---|
| <img src="docs/media/flags/us.svg" width="24" height="16" alt="US"> **US** | English | `en-US` |
| <img src="docs/media/flags/ru.svg" width="24" height="16" alt="RU"> **RU** | Русский | `ru-RU` |
| <img src="docs/media/flags/es.svg" width="24" height="16" alt="ES"> **ES** | Español | `es-ES` |
| <img src="docs/media/flags/br.svg" width="24" height="16" alt="BR"> **BR** | Português (Brasil) | `pt-BR` |
| <img src="docs/media/flags/de.svg" width="24" height="16" alt="DE"> **DE** | Deutsch | `de-DE` |
| <img src="docs/media/flags/fr.svg" width="24" height="16" alt="FR"> **FR** | Français | `fr-FR` |
| <img src="docs/media/flags/jp.svg" width="24" height="16" alt="JP"> **JP** | 日本語 | `ja-JP` |
| <img src="docs/media/flags/kr.svg" width="24" height="16" alt="KR"> **KR** | 한국어 | `ko-KR` |
| <img src="docs/media/flags/cn.svg" width="24" height="16" alt="CN"> **CN** | 简体中文 | `zh-CN` |
| <img src="docs/media/flags/tw.svg" width="24" height="16" alt="TW"> **TW** | 繁體中文 | `zh-TW` |

このページの言語は上部のリンクから切り替えられます。

## 💻 動作環境

**Windows x64・[OBS Studio](https://obsproject.com/) 32.2.2**の通常版、Steam版、ポータブル版で検証済みです。OBSは別途インストールしてください。

作者は通常版とSteam版で上書き・新規インストール、起動、設定の保存、支援リンクを確認しました。他のOBSバージョン、macOS、Linuxは未検証です。

## ☕ プロジェクトを支援

ASCII ⛶ VISOR · OBS Editionは**無料のオープンソースプラグイン**です。すべての機能を無料で利用できます。

気に入ったら、[BoostyでTRIPCHILLERを支援](https://boosty.to/tripchiller)して更新や新しい創作プロジェクトを応援できます。

## 🛠️ 開発者向け

ビルド手順と翻訳チェック：[BUILD.md](BUILD.md)。

## 💬 アイデア・フィードバック

アイデアや不具合がありましたか？フォームを選び、改善案や問題を教えてください。同じ場所で相談し、解決したらお知らせできます。

**[💡 アイデアの提案・不具合の報告](https://github.com/TRIPCHILLER/ascii-visor-obs/issues/new/choose)**

送信には[GitHub](https://github.com/)アカウントが必要です。プラグインの**プロジェクトについて**にある**アイデア・不具合報告**ボタンからも同じページを開けます。

## 📄 ライセンス

プラグイン：**GPL-2.0-or-later**。フォント：**SIL Open Font License**。[LICENSE](LICENSE)、[THIRD_PARTY.md](THIRD_PARTY.md)を参照してください。

ASCII ⛶ VISOR · OBS Editionは[TRIPCHILLER](https://github.com/TRIPCHILLER)による独立したコミュニティプロジェクトであり、OBS Projectの公式製品ではありません。
