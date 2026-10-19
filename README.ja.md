<p align="center"><picture><source media="(prefers-color-scheme: dark)" srcset="docs/media/visor-logo-white.svg"><source media="(prefers-color-scheme: light)" srcset="docs/media/visor-logo-dark.svg"><img src="docs/media/visor-logo-dark.svg" width="112" alt="ASCII VISOR"></picture></p>

<h1 align="center">ASCII ⛶ VISOR · OBS Edition</h1>

<p align="center"><b>カメラや動画を、<a href="https://obsproject.com/">OBS Studio</a>でリアルタイムの文字アートに。</b></p>

<p align="center">ASCII ⛶ VISOR 5.0を基に開発 · 制作者： <a href="https://github.com/TRIPCHILLER">TRIPCHILLER</a></p>

<p align="center"><a href="README.md"><img src="docs/media/flags/us.svg" width="24" height="16" alt="US"> English</a> · <a href="README.ru.md"><img src="docs/media/flags/ru.svg" width="24" height="16" alt="RU"> Русский</a> · <a href="README.es.md"><img src="docs/media/flags/es.svg" width="24" height="16" alt="ES"> Español</a> · <a href="README.pt-BR.md"><img src="docs/media/flags/br.svg" width="24" height="16" alt="BR"> Português (Brasil)</a> · <a href="README.de.md"><img src="docs/media/flags/de.svg" width="24" height="16" alt="DE"> Deutsch</a> · <a href="README.fr.md"><img src="docs/media/flags/fr.svg" width="24" height="16" alt="FR"> Français</a> · <b><img src="docs/media/flags/jp.svg" width="24" height="16" alt="JP"> 日本語</b> · <a href="README.ko.md"><img src="docs/media/flags/kr.svg" width="24" height="16" alt="KR"> 한국어</a> · <a href="README.zh-CN.md"><img src="docs/media/flags/cn.svg" width="24" height="16" alt="CN"> 简体中文</a> · <a href="README.zh-TW.md"><img src="docs/media/flags/tw.svg" width="24" height="16" alt="TW"> 繁體中文</a></p>

<p align="center"><b>Windows · Linux · macOS</b></p>

<p align="center"><a href="https://tripchiller.github.io/ascii-visor-obs/download/?platform=windows&amp;lang=en"><img src="docs/media/download-0.svg" width="220" height="58" alt="ダウンロード · Windows x64"></a> &nbsp; <a href="https://tripchiller.github.io/ascii-visor-obs/download/?platform=linux&amp;lang=en"><img src="docs/media/download-1.svg" width="220" height="58" alt="ダウンロード · Linux x86_64"></a> &nbsp; <a href="https://tripchiller.github.io/ascii-visor-obs/download/?platform=macos&amp;lang=en"><img src="docs/media/download-2.svg" width="220" height="58" alt="ダウンロード · macOS · Apple Silicon + Intel"></a></p>

<p align="center"><a href="docs/INSTALL.en.md">インストール</a> · <a href="#examples">使用例</a> · <a href="https://github.com/TRIPCHILLER/ascii-visor-obs/issues/new/choose">不具合を報告</a> · <a href="https://github.com/TRIPCHILLER/ascii-visor-obs/releases">リリース</a></p>

![ASCII ⛶ VISOR](docs/media/ascii_visor_preview.png)

**ASCII ⛶ VISOR**は、Webカメラや他の映像ソースをリアルタイムでASCIIアートに変換する[OBS Studio](https://obsproject.com/)用映像フィルタープラグインです。文字、色、密度を選び、シーンに合う見た目に調整できます。変更はすぐにプレビューに反映され、録画や配信にも適用されます。

個性的なカメラ演出、クリエイティブな配信、音楽ライブ、映像実験に。

ASCIIアバターは、VTuber風の配信表現の選択肢にもなります。通常のカメラ映像の代わりに様式化した姿を表示しながら、動きやリアクションをリアルタイムで伝えられます。見た目のプライバシーをある程度保てますが、匿名性を保証するものではありません。声、シルエット、画面内の細部から本人が分かる場合があります。

## ✨ 機能

| 機能 | 使い方 |
|---|---|
| **8種類の文字セット** | クラシックASCII、さまざまな文字、幾何学模様で質感を変更。 |
| **カスタム文字** | 自分の文字セットを入力して独自のスタイルを作成。 |
| **20種類のカラーパレット** | 用意されたスタイルや好きな色を選択。 |
| **カラースタイルの保存** | フィルターごとに最大20種類の色プリセットを保存。 |
| **透明背景** | 文字の隙間を透明にしてゲームや動画に重ねる。 |
| **映像調整** | 密度、コントラスト、ガンマ、黒・白レベル、拡大率、位置を調整。 |
| **OBS内で操作** | 通常のフィルター画面から操作し、録画や配信に使用。 |

密度は**横幅30〜150文字**。文字セットとパレットは自由に組み合わせられます。

<a name="examples"></a>

### 🎨 カラースタイル

同じ映像でも印象を変えられます。パレットを切り替えたり、文字と背景の色を自分で選んだりできます。

https://github.com/user-attachments/assets/30c21fb0-9aad-4652-9b45-b2c97a04a234

### 🔤 文字セットとカスタム入力

お気に入りのパレットを保ったまま、**8種類のセット**から選べます。クラシックASCII、別の文字体系、数字、幾何学模様が、それぞれ異なる質感を作ります。

https://github.com/user-attachments/assets/8ed8da50-d899-492f-a81a-4ccff01a9210

自分だけの見た目にしたいなら、**独自入力**を選んで使いたい文字を入力。組み合わせを試して、自分のスタイルを見つけましょう。

https://github.com/user-attachments/assets/067aa13c-cada-4ff3-859d-4025b0b72c82

### 🎛️ リアルタイム調整

照明やシーン内のカメラの大きさに合わせて密度と階調を調整します。変更はプレビューにすぐ反映されます。

https://github.com/user-attachments/assets/772cb41e-769f-432c-b734-f8f910bb3957

### 🫧 シーンに合わせた透明背景

透明背景では、文字の隙間からゲーム、動画、他のソースが見えます。ASCIIカメラを配信のレイアウトに重ねられます。

透明になるのは文字の間の部分です。人物と部屋の背景を自動で分離する機能ではありません。

https://github.com/user-attachments/assets/7efa18ca-853b-4c0f-a8cb-d59d1732bf57

<a name="quick-start"></a>

## 🚀 クイックスタート

上でOSを選び、OBSを終了してインストーラーを実行します。その後OBSを起動し、映像ソースを選択して次の順に操作します：**プレビュー内の選択したソースの映像を右クリック →「フィルタ」→ +（プラスのアイコン）→ ASCII ⛶ VISOR**。

[インストールガイド](docs/INSTALL.en.md) · [Releases](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/tag/v0.3.1-rc1)

https://github.com/user-attachments/assets/6e653001-9286-4655-aad6-fa029b3f2180

<details>
<summary>手動インストールと追加パッケージ</summary>

- [ASCII-VISOR-0.3.1-rc1-Windows-x64-Plugin.zip](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Windows-x64-Plugin.zip)
- [ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Plugin.tar.gz](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Plugin.tar.gz)
- [ASCII-VISOR-0.3.1-rc1-macOS-universal-Plugin.zip](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-macOS-universal-Plugin.zip)
- [ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.tar.gz](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.tar.gz)
- [SHA256SUMS.txt](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/SHA256SUMS.txt)
- Source code: GitHub ZIP / TAR.GZ

</details>

<a name="help"></a>

## ヘルプ

<details>
<summary>フィルターが表示されない場合</summary>

OBSを完全に再起動し、映像ソースを選択してください。次の順に操作します：**プレビュー内の選択したソースの映像を右クリック →「フィルタ」→ +（プラスのアイコン）→ ASCII ⛶ VISOR**。 一覧にASCII VISORがない場合は、OSとOBSのバージョンを添えて[問題を報告](https://github.com/TRIPCHILLER/ascii-visor-obs/issues/new/choose)してください。

</details>

<details>
<summary>プラグインの更新</summary>

OBSを終了し、お使いのOSのボタンから最新のインストーラーをダウンロードして、以前と同じ場所を選びます。**旧バージョンのアンインストールは不要です。**新しいバージョンがプラグインのファイルを上書きして更新します。OBSのシーンとプロファイルは保持されます。

</details>

<details>
<summary>プラグインを削除するには</summary>

OBSを終了し、[お使いのOSのインストールガイド](docs/INSTALL.en.md)の削除手順に従ってください。削除されるのはプラグインのみで、OBS本体と設定は保持されます。

</details>

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

Windows x64、Linux x86_64（Ubuntu 24.04 / glibc 2.39以降）、macOS universal（Apple Silicon・Intel）。OBSは別途必要です。OBS 32.2.2でテスト。macOS版はアドホック署名で、公証はされていません。Linux Flatpakでは互換性のあるOBS環境が必要です。詳細はガイドをご覧ください。

[インストールガイド](docs/INSTALL.en.md)

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

プラグイン：**GPL-2.0-or-later**。フォント：**SIL Open Font License / M+**。[LICENSE](LICENSE)、[THIRD_PARTY.md](THIRD_PARTY.md)を参照してください。

ASCII ⛶ VISOR · OBS Editionは[TRIPCHILLER](https://github.com/TRIPCHILLER)による独立したコミュニティプロジェクトであり、OBS Projectの公式製品ではありません。
