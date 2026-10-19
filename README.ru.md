<p align="center">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="docs/media/visor-logo-white.svg">
    <source media="(prefers-color-scheme: light)" srcset="docs/media/visor-logo-dark.svg">
    <img src="docs/media/visor-logo-dark.svg" width="112" alt="Логотип ASCII VISOR">
  </picture>
</p>

<h1 align="center">ASCII ⛶ VISOR · OBS Edition</h1>

<p align="center"><b>Превратите видео с веб-камеры в анимацию из символов — прямо в <a href="https://obsproject.com/">OBS Studio</a>.</b></p>

<p align="center">Разработано на основе ASCII ⛶ VISOR 5.0 · Автор — <a href="https://github.com/TRIPCHILLER">TRIPCHILLER</a></p>

<p align="center"><a href="README.md"><img src="docs/media/flags/us.svg" width="24" height="16" alt="US"> English</a> · <b><img src="docs/media/flags/ru.svg" width="24" height="16" alt="RU"> Русский</b> · <a href="README.es.md"><img src="docs/media/flags/es.svg" width="24" height="16" alt="ES"> Español</a> · <a href="README.pt-BR.md"><img src="docs/media/flags/br.svg" width="24" height="16" alt="BR"> Português (Brasil)</a> · <a href="README.de.md"><img src="docs/media/flags/de.svg" width="24" height="16" alt="DE"> Deutsch</a> · <a href="README.fr.md"><img src="docs/media/flags/fr.svg" width="24" height="16" alt="FR"> Français</a> · <a href="README.ja.md"><img src="docs/media/flags/jp.svg" width="24" height="16" alt="JP"> 日本語</a> · <a href="README.ko.md"><img src="docs/media/flags/kr.svg" width="24" height="16" alt="KR"> 한국어</a> · <a href="README.zh-CN.md"><img src="docs/media/flags/cn.svg" width="24" height="16" alt="CN"> 简体中文</a> · <a href="README.zh-TW.md"><img src="docs/media/flags/tw.svg" width="24" height="16" alt="TW"> 繁體中文</a></p>

<p align="center"><b>Windows · Linux · macOS · 0.3.1-rc1</b></p>

<p align="center"><a href="https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Windows-x64-Setup.exe"><img src="docs/media/download-0.svg" width="220" height="58" alt="Скачать · Windows x64"></a> &nbsp; <a href="https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.AppImage"><img src="docs/media/download-1.svg" width="220" height="58" alt="Скачать · Linux x86_64"></a> &nbsp; <a href="https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-macOS-universal-Setup.zip"><img src="docs/media/download-2.svg" width="220" height="58" alt="Скачать · macOS · Apple Silicon + Intel"></a></p>

<p align="center">0.3.1-rc1 — версия для проверки перед основным релизом. Эти ссылки заработают после публикации релиза. <a href="https://github.com/TRIPCHILLER/ascii-visor-obs/releases/tag/v0.2.8">0.2.8 · Windows</a></p>

![Камера с эффектом ASCII VISOR](docs/media/ascii_visor_preview.png)

**ASCII ⛶ VISOR** — плагин-видеофильтр для [OBS Studio](https://obsproject.com/), превращающий веб-камеру или другой видеоисточник в ASCII-изображение в реальном времени. Выбирайте символы, меняйте цвета и плотность, подстраивайте изображение под свою сцену — результат сразу виден в превью и попадает в запись или трансляцию.

Подходит для необычного оформления камеры, творческих трансляций, музыкальных выступлений и экспериментов с видео, а так же как альтернатива VTuber-подаче: сохраняйте живые движения и эмоции, показывая стилизованное изображение вместо обычной веб-камеры. 

_*Это даёт частичную визуальную приватность, но не гарантирует полную анонимность: голос, силуэт и детали кадра могут оставаться узнаваемыми._

## ✨ Возможности

| Возможность | Применение |
|---|---|
| **8 готовых наборов** | Изменить характер изображения: от классического ASCII до альтернативных символов и геометрических форм. |
| **Собственные символы** | Ввести свой набор и сделать изображение с индивидуальной фактурой. |
| **20 цветовых палитр** | Быстро выбрать готовый стиль или настроить собственные цвета. |
| **Сохранение цветовых стилей** | Сохранить до 20 своих цветовых пресетов для каждого фильтра. |
| **Прозрачный фон** | Сделать промежутки между символами прозрачными и разместить изображение поверх игры, видео или другой сцены. |
| **Настройка изображения** | Менять плотность, контраст, гамму, уровни чёрного и белого, масштаб и положение. |
| **Работа прямо в OBS** | Управлять эффектом из привычного окна фильтров и использовать его в записи и трансляции. |

Плотность регулируется от **30 до 150 символов по ширине**. Наборы символов и цветовые палитры выбираются независимо: их можно комбинировать.

### 🎨 Цветовые стили

Один источник — разные настроения. Переключайте готовые палитры или выбирайте цвета символов и фона самостоятельно.

https://github.com/user-attachments/assets/30c21fb0-9aad-4652-9b45-b2c97a04a234

### 🔤 Наборы и собственный ввод

Выбирайте из **8 готовых наборов**, сохраняя любимую палитру. У каждого свой характер: классические ASCII-символы, альтернативные алфавиты, цифры и геометрические формы дают совсем разную фактуру изображения.

https://github.com/user-attachments/assets/8ed8da50-d899-492f-a81a-4ccff01a9210

Хотите что-то своё? Выберите **собственный набор** и введите символы, из которых хотите собрать изображение. Экспериментируйте с сочетаниями и находите свой стиль.

https://github.com/user-attachments/assets/067aa13c-cada-4ff3-859d-4025b0b72c82

### 🎛️ Настройки в реальном времени

Подберите плотность и тон изображения под освещение и размер камеры в вашей сцене. Изменения сразу отображаются в превью.

https://github.com/user-attachments/assets/772cb41e-769f-432c-b734-f8f910bb3957

### 🫧 Прозрачность для вашей сцены

С прозрачным фоном между символами видны игра, видео или другие источники вашей сцены. Так ASCII-камеру можно вписать в оформление трансляции.

Это прозрачность промежутков между символами; она не отделяет человека от комнаты автоматически.

https://github.com/user-attachments/assets/7efa18ca-853b-4c0f-a8cb-d59d1732bf57

<a name="quick-start"></a>

## 🚀 Быстрый старт

Выберите свою систему выше. Закройте OBS, запустите установщик, затем откройте OBS → источник → Фильтры → Фильтры эффектов → + → ASCII ⛶ VISOR.

[Инструкция по установке](docs/INSTALL.ru.md) · [Releases](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/tag/v0.3.1-rc1)

<details>
<summary>Ручная установка и дополнительные архивы</summary>

- [ASCII-VISOR-0.3.1-rc1-Windows-x64-Plugin.zip](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Windows-x64-Plugin.zip)
- [ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Plugin.tar.gz](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Plugin.tar.gz)
- [ASCII-VISOR-0.3.1-rc1-macOS-universal-Plugin.zip](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-macOS-universal-Plugin.zip)
- [ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.tar.gz](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/ASCII-VISOR-0.3.1-rc1-Linux-x86_64-Setup.tar.gz)
- [SHA256SUMS.txt](https://github.com/TRIPCHILLER/ascii-visor-obs/releases/download/v0.3.1-rc1/SHA256SUMS.txt)
- Source code: GitHub ZIP / TAR.GZ

</details>

## 🌍 10 языков интерфейса

Плагин и установщик переведены на следующие языки. Язык плагина выбирается вместе с языком OBS; после его изменения перезапустите OBS. В установщике язык можно выбрать отдельно.

| | Язык | Локализация |
|---|---|---|
| <img src="docs/media/flags/ru.svg" width="24" height="16" alt="RU" style="width:24px;vertical-align:middle;border-radius:2px"> **RU** | Русский | `ru-RU` |
| <img src="docs/media/flags/us.svg" width="24" height="16" alt="US" style="width:24px;vertical-align:middle;border-radius:2px"> **US** | English — английский | `en-US` |
| <img src="docs/media/flags/es.svg" width="24" height="16" alt="ES" style="width:24px;vertical-align:middle;border-radius:2px"> **ES** | Español — испанский | `es-ES` |
| <img src="docs/media/flags/br.svg" width="24" height="16" alt="BR" style="width:24px;vertical-align:middle;border-radius:2px"> **BR** | Português (Brasil) — португальский, Бразилия | `pt-BR` |
| <img src="docs/media/flags/de.svg" width="24" height="16" alt="DE" style="width:24px;vertical-align:middle;border-radius:2px"> **DE** | Deutsch — немецкий | `de-DE` |
| <img src="docs/media/flags/fr.svg" width="24" height="16" alt="FR" style="width:24px;vertical-align:middle;border-radius:2px"> **FR** | Français — французский | `fr-FR` |
| <img src="docs/media/flags/jp.svg" width="24" height="16" alt="JP" style="width:24px;vertical-align:middle;border-radius:2px"> **JP** | 日本語 — японский | `ja-JP` |
| <img src="docs/media/flags/kr.svg" width="24" height="16" alt="KR" style="width:24px;vertical-align:middle;border-radius:2px"> **KR** | 한국어 — корейский | `ko-KR` |
| <img src="docs/media/flags/cn.svg" width="24" height="16" alt="CN" style="width:24px;vertical-align:middle;border-radius:2px"> **CN** | 简体中文 — упрощённый китайский | `zh-CN` |
| <img src="docs/media/flags/tw.svg" width="24" height="16" alt="TW" style="width:24px;vertical-align:middle;border-radius:2px"> **TW** | 繁體中文 — традиционный китайский | `zh-TW` |

Язык этой страницы можно переключить по ссылкам вверху.

## 💻 Совместимость

Windows x64; Linux x86_64 (Ubuntu 24.04 / glibc 2.39 или новее); macOS universal (Apple Silicon и Intel). OBS устанавливается отдельно. Сборки проверяются с OBS 32.2.2. У macOS локальная подпись: установщик не заверен Apple. Для Linux Flatpak нужна совместимая среда OBS. Требования и ограничения перечислены в инструкции.

[Инструкция по установке](docs/INSTALL.ru.md)

## ☕ Поддержать проект

ASCII ⛶ VISOR · OBS Edition — **бесплатный плагин с открытым исходным кодом**. Все возможности доступны без оплаты.

Понравился плагин? Вы можете [поддержать TRIPCHILLER на Boosty](https://boosty.to/tripchiller), помогая выпускать обновления и создавать новые творческие проекты.

## 🛠️ Для разработчиков

Инструкции по сборке и проверке переводов находятся в [BUILD.md](BUILD.md).

## 💬 Идеи и обратная связь

Придумали новую функцию или нашли ошибку? Напишите об этом в репозитории: выберите подходящую форму, расскажите, что хотите улучшить, или опишите проблему. Так мы сможем обсудить её в одном месте и сообщить, когда она будет решена.

**[💡 Предложить идею или сообщить об ошибке](https://github.com/TRIPCHILLER/ascii-visor-obs/issues/new/choose)**

Для отправки нужен аккаунт [GitHub](https://github.com/). Эту же страницу можно открыть кнопкой **«Идеи и ошибки»** в разделе **«О проекте»** внутри плагина.

## 📄 Лицензии

Плагин распространяется под **GPL-2.0-or-later**, шрифты — под **SIL Open Font License**. Подробнее: [LICENSE](LICENSE) и [THIRD_PARTY.md](THIRD_PARTY.md).

ASCII ⛶ VISOR · OBS Edition — независимый проект сообщества, созданный [TRIPCHILLER](https://github.com/TRIPCHILLER). Он не является официальным продуктом OBS Project.
