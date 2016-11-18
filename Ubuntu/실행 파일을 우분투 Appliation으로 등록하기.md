# 실행 파일을 우분투 Application으로 등록하기

## 도대체 무슨 말이냐?
- 이렇게 생겨먹은 ELF 파일을
![image](https://cloud.githubusercontent.com/assets/8033320/20421866/18f3a680-adaa-11e6-93fc-b2fa5534e662.png)
- 이렇게 우분투 Application으로 등록해서 검색으로 사용하고, 사이드바에서도 사용하고, 메뉴 바에서도 사용하겠다는 말이다.
![image](https://cloud.githubusercontent.com/assets/8033320/20421934/89f79fb2-adaa-11e6-8fc6-91ea11016455.png)

## `*.desktop` 파일 작성
- 우분투에서 Application 목록 관리는 `/usr/share/applicatons` 내에서 `*.desktop` 파일로 관리된다.
- 그렇다고 `/usr/share/applications`에 가서 desktop 파일을 작성할 필요는 없다. 우리에겐 `desktop-file-install`이라는 좋은 명령어가 있다.
- 텔레그램 ELF 실행파일을 케이스로 `telegram.desktop`을 만들어보자.
  ```bash
  echo '[Desktop Entry]
  Name=Telegram
  Type=Application
  Exec=env UBUNTU_MENUPROXY=0 telegram
  Terminal=false
  Icon=telegram
  Comment=Telegram Ubuntu Application
  NoDisplay=false
  Name[en]=Telegram' > telegram.desktop
  ```
  - 원래 `Categories`라는 변수가 있었는데, 뭔가 적용이 잘 되지 않아서 제거했다.
  - `Icon`은 현재 활성화된 아이콘 테마를 참고한다. 아이콘 테마는 `/usr/share/icons` 내의 테마명으로 된 디렉토리 안에서 확인할 수 있다. 나의 경우 현재 `Numix-Circle` 테마를 사용 중이고 내부에 `telegram.svg` 파일이 존재한다.

## `telegram.desktop`을 등록하자
- 위에서 언급한 것 처럼 `desktop-file-install` 명령어를 사용하면 쉽게 `*.desktop` 파일을 등록시킬 수 있다.
```bash
sudo desktop-file-install telegram.desktop
```

## 실행파일을 `$PATH`경로에 넣어주자.
- 이제 우분투 Application으로 나타는 나지만 실제로 `PATH` 경로에는 파일이 없기 때문에 실행되지 않는다. 나는 `/home/uyu423/.telegram/` 내에 `Telegram`이라는 실행파일이 있엇고, 이를 `/usr/local/bin`에 `telegram`으로 심볼릭 링크를 생성했다.
```bash
sudo ln -s /home/uyu423/.telegram/Telegram /usr/local/bin/telegram
```
- **이제 잘 될 것이다..!!**

## 기타 사항
- 내가 위에서 적용한 `telegram.desktop` 파일은 최소화 버전이다. 예를 들어 `chromium-browser.desktop`의 경우 아래와 같이 되게 복잡하다.

```
[Desktop Entry]
Version=1.0
Name=Google Chrome
# Only KDE 4 seems to use GenericName, so we reuse the KDE strings.
# From Ubuntu's language-pack-kde-XX-base packages, version 9.04-20090413.
GenericName=Web Browser
GenericName[ar]=متصفح الشبكة
GenericName[bg]=Уеб браузър
GenericName[ca]=Navegador web
GenericName[cs]=WWW prohlížeč
GenericName[da]=Browser
GenericName[de]=Web-Browser
GenericName[el]=Περιηγητής ιστού
GenericName[en_GB]=Web Browser
GenericName[es]=Navegador web
GenericName[et]=Veebibrauser
GenericName[fi]=WWW-selain
GenericName[fr]=Navigateur Web
GenericName[gu]=વેબ બ્રાઉઝર
GenericName[he]=דפדפן אינטרנט
GenericName[hi]=वेब ब्राउज़र
GenericName[hu]=Webböngésző
GenericName[it]=Browser Web
GenericName[ja]=ウェブブラウザ
GenericName[kn]=ಜಾಲ ವೀಕ್ಷಕ
GenericName[ko]=웹 브라우저
# 생략...
# Gnome and KDE 3 uses Comment.
Comment=Access the Internet
Comment[ar]=الدخول إلى الإنترنت
Comment[bg]=Достъп до интернет
Comment[bn]=ইন্টারনেটটি অ্যাক্সেস করুন
Comment[ca]=Accedeix a Internet
Comment[cs]=Přístup k internetu
Comment[da]=Få adgang til internettet
Comment[de]=Internetzugriff
Comment[el]=Πρόσβαση στο Διαδίκτυο
Comment[en_GB]=Access the Internet
Comment[es]=Accede a Internet.
Comment[et]=Pääs Internetti
Comment[fi]=Käytä internetiä
Comment[fil]=I-access ang Internet
Comment[fr]=Accéder à Internet
Comment[gu]=ઇંટરનેટ ઍક્સેસ કરો
Comment[he]=גישה אל האינטרנט
Comment[hi]=इंटरनेट तक पहुंच स्थापित करें
Comment[hr]=Pristup Internetu
Comment[hu]=Internetelérés
Comment[id]=Akses Internet
Comment[it]=Accesso a Internet
Comment[ja]=インターネットにアクセス
Comment[kn]=ಇಂಟರ್ನೆಟ್ ಅನ್ನು ಪ್ರವೇಶಿಸಿ
Comment[ko]=인터넷 연결
# 생략...
Exec=/usr/bin/google-chrome-stable %U
Terminal=false
Icon=google-chrome
Type=Application
Categories=Network;WebBrowser;
MimeType=text/html;text/xml;application/xhtml_xml;image/webp;x-scheme-handler/http;x-scheme-handler/https;x-scheme-handler/ftp;
X-Ayatana-Desktop-Shortcuts=NewWindow;NewIncognito

[NewWindow Shortcut Group]
Name=New Window
Name[am]=አዲስ መስኮት
Name[ar]=نافذة جديدة
Name[bg]=Нов прозорец
Name[bn]=নতুন উইন্ডো
Name[ca]=Finestra nova
Name[cs]=Nové okno
Name[da]=Nyt vindue
Name[de]=Neues Fenster
Name[el]=Νέο Παράθυρο
Name[en_GB]=New Window
Name[es]=Nueva ventana
Name[et]=Uus aken
Name[fa]=پنجره جدید
Name[fi]=Uusi ikkuna
Name[fil]=New Window
Name[fr]=Nouvelle fenêtre
Name[gu]=નવી વિંડો
Name[hi]=नई विंडो
Name[hr]=Novi prozor
Name[hu]=Új ablak
Name[id]=Jendela Baru
Name[it]=Nuova finestra
Name[iw]=חלון חדש
Name[ja]=新規ウインドウ
Name[kn]=ಹೊಸ ವಿಂಡೊ
Name[ko]=새 창
# 생략...
Exec=/usr/bin/google-chrome-stable
TargetEnvironment=Unity

[NewIncognito Shortcut Group]
Name=New Incognito Window
Name[ar]=نافذة جديدة للتصفح المتخفي
Name[bg]=Нов прозорец „инкогнито“
Name[bn]=নতুন ছদ্মবেশী উইন্ডো
Name[ca]=Finestra d'incògnit nova
Name[cs]=Nové anonymní okno
Name[da]=Nyt inkognitovindue
Name[de]=Neues Inkognito-Fenster
Name[el]=Νέο παράθυρο για ανώνυμη περιήγηση
Name[en_GB]=New Incognito window
Name[es]=Nueva ventana de incógnito
Name[et]=Uus inkognito aken
Name[fa]=پنجره جدید حالت ناشناس
Name[fi]=Uusi incognito-ikkuna
Name[fil]=Bagong Incognito window
Name[fr]=Nouvelle fenêtre de navigation privée
Name[gu]=નવી છુપી વિંડો
Name[hi]=नई गुप्त विंडो
Name[hr]=Novi anoniman prozor
Name[hu]=Új Inkognitóablak
Name[id]=Jendela Penyamaran baru
Name[it]=Nuova finestra di navigazione in incognito
Name[iw]=חלון חדש לגלישה בסתר
Name[ja]=新しいシークレット ウィンドウ
Name[kn]=ಹೊಸ ಅಜ್ಞಾತ ವಿಂಡೋ
Name[ko]=새 시크릿 창
# 생략...
Exec=/usr/bin/google-chrome-stable --incognito
TargetEnvironment=Unity
```
