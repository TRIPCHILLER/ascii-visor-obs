import json
from pathlib import Path
keys = 'Heading Intro Standard Portable Detail License Install Cancel CloseOBS SelectOBS Incompatible PortableDetected Destination BackupNotice DoneHeading DoneInfo Backup Finish Launch DirectOBS SteamOBS LaunchError InstallerError'.split()
texts = {
'en-US': '''Install ASCII VISOR
Free ASCII video filter · Windows x64 · OBS 32.2.2
Standard OBS / Steam — shared installation
Portable OBS — choose folder
Folders are created automatically. OBS scenes, profiles and settings are preserved. Close all OBS windows before installation.
Plugin: GPL-2.0-or-later · Fonts: SIL OFL. Source and licenses are available in the project repository.
Install
Cancel
Close all OBS windows and try again.
Select obs64.exe from the OBS installation you use
This build is verified only with OBS 32.2.2 x64. Select a compatible installation.
Portable OBS detected. Select the Portable OBS option.
Install VISOR to:
An existing version will be preserved in a backup folder.
Installation complete
Open your camera source → Filters → Effect Filters → ASCII VISOR.
Backup folder:
Finish
Launch OBS when I finish
Selected OBS installation
Launch through Steam
Could not launch OBS with ordinary user permissions. Open it using your usual shortcut.
Installation could not be completed.''',
'ru-RU': '''Установить ASCII VISOR
Бесплатный ASCII-видеофильтр · Windows x64 · OBS 32.2.2
Обычная OBS / Steam — общая установка
Переносная OBS — выбрать папку
Папки будут созданы автоматически. Сцены, профили и настройки OBS сохраняются. Перед установкой закройте все окна OBS.
Плагин: GPL-2.0-or-later · Шрифты: SIL OFL. Исходники и лицензии доступны в репозитории проекта.
Установить
Отмена
Закройте все окна OBS и повторите установку.
Выберите obs64.exe той OBS, которую используете
Эта сборка проверена только с OBS 32.2.2 x64. Выберите совместимую версию.
Выбрана переносная OBS. Выберите вариант «Переносная OBS».
Установить VISOR в:
Предыдущая версия, если есть, будет сохранена в резервной папке.
Установка завершена
Выберите камеру → Фильтры → Фильтры эффектов → ASCII VISOR.
Резервная папка:
Завершить
Запустить OBS после завершения
Выбранная версия OBS
Запустить через Steam
Не удалось запустить OBS с обычными правами пользователя. Откройте её привычным ярлыком.
Не удалось завершить установку.''',
'es-ES': '''Instalar ASCII VISOR
Filtro de vídeo ASCII gratuito · Windows x64 · OBS 32.2.2
OBS estándar / Steam — instalación compartida
OBS portátil — elegir carpeta
Las carpetas se crean automáticamente. Se conservan las escenas, los perfiles y los ajustes de OBS. Cierra todas las ventanas de OBS antes de instalar.
Plugin: GPL-2.0-or-later · Fuentes: SIL OFL. El código fuente y las licencias están en el repositorio del proyecto.
Instalar
Cancelar
Cierra todas las ventanas de OBS e inténtalo de nuevo.
Selecciona obs64.exe de la instalación de OBS que utilizas
Esta versión solo se ha verificado con OBS 32.2.2 x64. Selecciona una instalación compatible.
Se ha detectado OBS portátil. Selecciona la opción OBS portátil.
Instalar VISOR en:
La versión anterior, si existe, se guardará en una carpeta de respaldo.
Instalación completada
Selecciona la cámara → Filtros → Filtros de efecto → ASCII VISOR.
Carpeta de respaldo:
Finalizar
Iniciar OBS al finalizar
Instalación de OBS seleccionada
Iniciar a través de Steam
No se pudo iniciar OBS con permisos de usuario normales. Ábrelo con tu acceso directo habitual.
No se pudo completar la instalación.''',
'pt-BR': '''Instalar ASCII VISOR
Filtro de vídeo ASCII gratuito · Windows x64 · OBS 32.2.2
OBS padrão / Steam — instalação compartilhada
OBS portátil — escolher pasta
As pastas são criadas automaticamente. Cenas, perfis e configurações do OBS são preservados. Feche todas as janelas do OBS antes de instalar.
Plugin: GPL-2.0-or-later · Fontes: SIL OFL. O código-fonte e as licenças estão no repositório do projeto.
Instalar
Cancelar
Feche todas as janelas do OBS e tente novamente.
Selecione obs64.exe da instalação do OBS que você usa
Esta versão foi verificada apenas com OBS 32.2.2 x64. Selecione uma instalação compatível.
OBS portátil detectado. Selecione a opção OBS portátil.
Instalar o VISOR em:
A versão anterior, se houver, será preservada em uma pasta de backup.
Instalação concluída
Selecione a câmera → Filtros → Filtros de efeito → ASCII VISOR.
Pasta de backup:
Concluir
Iniciar o OBS ao concluir
Instalação do OBS selecionada
Iniciar pelo Steam
Não foi possível iniciar o OBS com permissões normais de usuário. Abra-o pelo atalho habitual.
Não foi possível concluir a instalação.''',
'de-DE': '''ASCII VISOR installieren
Kostenloser ASCII-Videofilter · Windows x64 · OBS 32.2.2
Standard-OBS / Steam — gemeinsame Installation
Portable OBS — Ordner auswählen
Ordner werden automatisch erstellt. OBS-Szenen, Profile und Einstellungen bleiben erhalten. Schließe vor der Installation alle OBS-Fenster.
Plugin: GPL-2.0-or-later · Schriftarten: SIL OFL. Quellcode und Lizenzen findest du im Projekt-Repository.
Installieren
Abbrechen
Schließe alle OBS-Fenster und versuche es erneut.
Wähle obs64.exe deiner OBS-Installation
Diese Version wurde nur mit OBS 32.2.2 x64 geprüft. Wähle eine kompatible Installation.
Portable OBS erkannt. Wähle die Option Portable OBS.
VISOR installieren in:
Eine vorhandene Version wird in einem Sicherungsordner aufbewahrt.
Installation abgeschlossen
Wähle deine Kamera → Filter → Effektfilter → ASCII VISOR.
Sicherungsordner:
Fertigstellen
OBS nach Abschluss starten
Ausgewählte OBS-Installation
Über Steam starten
OBS konnte nicht mit normalen Benutzerrechten gestartet werden. Öffne es über deine gewohnte Verknüpfung.
Die Installation konnte nicht abgeschlossen werden.''',
'fr-FR': '''Installer ASCII VISOR
Filtre vidéo ASCII gratuit · Windows x64 · OBS 32.2.2
OBS standard / Steam — installation commune
OBS portable — choisir un dossier
Les dossiers sont créés automatiquement. Les scènes, profils et réglages OBS sont conservés. Fermez toutes les fenêtres OBS avant l’installation.
Plugin : GPL-2.0-or-later · Polices : SIL OFL. Le code source et les licences sont disponibles dans le dépôt du projet.
Installer
Annuler
Fermez toutes les fenêtres OBS et réessayez.
Sélectionnez obs64.exe dans votre installation d’OBS
Cette version a été vérifiée uniquement avec OBS 32.2.2 x64. Choisissez une installation compatible.
OBS portable détecté. Sélectionnez l’option OBS portable.
Installer VISOR dans :
La version précédente, si elle existe, sera conservée dans un dossier de sauvegarde.
Installation terminée
Sélectionnez la caméra → Filtres → Filtres d’effets → ASCII VISOR.
Dossier de sauvegarde :
Terminer
Lancer OBS à la fin
Installation OBS sélectionnée
Lancer via Steam
Impossible de lancer OBS avec les droits utilisateur habituels. Ouvrez-le avec votre raccourci habituel.
L’installation n’a pas pu être terminée.''',
'ja-JP': '''ASCII VISORをインストール
無料ASCII映像フィルター · Windows x64 · OBS 32.2.2
通常のOBS / Steam — 共通インストール
ポータブルOBS — フォルダーを選択
必要なフォルダーは自動作成されます。OBSのシーン、プロファイル、設定は保持されます。インストール前にすべてのOBSウィンドウを閉じてください。
プラグイン：GPL-2.0-or-later · フォント：SIL OFL。ソースコードとライセンスはプロジェクトのリポジトリで公開しています。
インストール
キャンセル
すべてのOBSウィンドウを閉じて、もう一度お試しください。
使用するOBSのobs64.exeを選択してください
このビルドはOBS 32.2.2 x64でのみ検証済みです。対応するOBSを選択してください。
ポータブルOBSを検出しました。「ポータブルOBS」を選択してください。
VISORのインストール先：
既存のバージョンはバックアップフォルダーに保存されます。
インストール完了
カメラを選択 → フィルタ → エフェクトフィルタ → ASCII VISOR。
バックアップフォルダー：
完了
完了後にOBSを起動する
選択したOBS
Steamから起動
通常のユーザー権限でOBSを起動できませんでした。いつものショートカットから開いてください。
インストールを完了できませんでした。''',
'ko-KR': '''ASCII VISOR 설치
무료 ASCII 영상 필터 · Windows x64 · OBS 32.2.2
일반 OBS / Steam — 공통 설치
포터블 OBS — 폴더 선택
폴더가 자동으로 생성됩니다. OBS 장면, 프로필 및 설정은 유지됩니다. 설치 전에 모든 OBS 창을 닫아 주세요.
플러그인: GPL-2.0-or-later · 글꼴: SIL OFL. 소스 코드와 라이선스는 프로젝트 저장소에서 확인할 수 있습니다.
설치
취소
모든 OBS 창을 닫고 다시 시도해 주세요.
사용하는 OBS의 obs64.exe를 선택하세요
이 빌드는 OBS 32.2.2 x64에서만 검증되었습니다. 호환되는 설치를 선택하세요.
포터블 OBS가 감지되었습니다. 포터블 OBS 옵션을 선택하세요.
VISOR 설치 위치:
기존 버전이 있으면 백업 폴더에 보관됩니다.
설치 완료
카메라 선택 → 필터 → 효과 필터 → ASCII VISOR.
백업 폴더:
마침
완료 후 OBS 실행
선택한 OBS 설치
Steam으로 실행
일반 사용자 권한으로 OBS를 실행하지 못했습니다. 평소 사용하는 바로 가기로 열어 주세요.
설치를 완료하지 못했습니다.''',
'zh-CN': '''安装 ASCII VISOR
免费 ASCII 视频滤镜 · Windows x64 · OBS 32.2.2
普通 OBS / Steam — 共用安装
便携版 OBS — 选择文件夹
文件夹将自动创建。OBS 场景、配置文件和设置会保留。安装前请关闭所有 OBS 窗口。
插件：GPL-2.0-or-later · 字体：SIL OFL。源代码和许可证可在项目仓库中查看。
安装
取消
请关闭所有 OBS 窗口后重试。
请选择您使用的 OBS 安装中的 obs64.exe
此版本仅在 OBS 32.2.2 x64 上验证过。请选择兼容版本。
检测到便携版 OBS。请选择便携版 OBS 选项。
将 VISOR 安装到：
已有版本将保存在备份文件夹中。
安装完成
选择摄像头 → 滤镜 → 效果滤镜 → ASCII VISOR。
备份文件夹：
完成
完成后启动 OBS
选中的 OBS 安装
通过 Steam 启动
无法以普通用户权限启动 OBS。请使用平时的快捷方式打开。
无法完成安装。''',
'zh-TW': '''安裝 ASCII VISOR
免費 ASCII 影片濾鏡 · Windows x64 · OBS 32.2.2
一般 OBS / Steam — 共用安裝
可攜版 OBS — 選擇資料夾
資料夾將自動建立。OBS 場景、設定檔及設定會保留。安裝前請關閉所有 OBS 視窗。
外掛程式：GPL-2.0-or-later · 字型：SIL OFL。原始碼及授權條款可在專案儲存庫中查看。
安裝
取消
請關閉所有 OBS 視窗後再試一次。
請選擇您使用的 OBS 安裝中的 obs64.exe
此版本僅在 OBS 32.2.2 x64 上驗證過。請選擇相容版本。
偵測到可攜版 OBS。請選擇可攜版 OBS 選項。
將 VISOR 安裝至：
既有版本將保存在備份資料夾中。
安裝完成
選擇攝影機 → 濾鏡 → 效果濾鏡 → ASCII VISOR。
備份資料夾：
完成
完成後啟動 OBS
選取的 OBS 安裝
透過 Steam 啟動
無法以一般使用者權限啟動 OBS。請使用平常的捷徑開啟。
無法完成安裝。'''
}
names = {'ru-RU':'Русский','en-US':'English','es-ES':'Español','pt-BR':'Português (Brasil)','de-DE':'Deutsch','fr-FR':'Français','ja-JP':'日本語','ko-KR':'한국어','zh-CN':'简体中文','zh-TW':'繁體中文'}
locales={}
credits={
'ru-RU':'Разработано на основе ASCII ⛶ VISOR 5.0 · Автор — TRIPCHILLER',
'en-US':'Based on ASCII ⛶ VISOR 5.0 · Made by TRIPCHILLER',
'es-ES':'Basado en ASCII ⛶ VISOR 5.0 · Creado por TRIPCHILLER',
'pt-BR':'Baseado em ASCII ⛶ VISOR 5.0 · Criado por TRIPCHILLER',
'de-DE':'Basierend auf ASCII ⛶ VISOR 5.0 · Von TRIPCHILLER',
'fr-FR':'Basé sur ASCII ⛶ VISOR 5.0 · Créé par TRIPCHILLER',
'ja-JP':'ASCII ⛶ VISOR 5.0を基に開発 · 作者：TRIPCHILLER',
'ko-KR':'ASCII ⛶ VISOR 5.0 기반 · 제작: TRIPCHILLER',
'zh-CN':'基于 ASCII ⛶ VISOR 5.0 · 作者：TRIPCHILLER',
'zh-TW':'基於 ASCII ⛶ VISOR 5.0 · 作者：TRIPCHILLER'
}
for locale,name in names.items():
    values=texts[locale].splitlines()
    assert len(values)==len(keys),(locale,len(values))
    locales[locale]={'Name':name,**dict(zip(keys,values)),'Credits':credits[locale]}
Path(__file__).with_name('locales.json').write_text(json.dumps(locales,ensure_ascii=False,indent=2),encoding='utf-8')
print(f'{len(locales)} languages, {len(keys)+1} UI keys per language')
