# MacOS (High Sierra) 초기화 후 개발 환경 세팅

> 2018.03.10 회사에서 지급받은 맥북프로 초기화 진행 하면서 기록

## 초기화 및 재설치

- 맥북 재시동 후 `cmd` + `r` 누르고 있으면 관련 메뉴 진입 가능
- 디스크 유틸리티에서 하드 디스크 파티션 지운 후 재편성
  - 파일 시스템 결정 시 대소문자 구분 옵션과 구분하지 않음 옵션이 있는데, 구분하지 않음 옵션을 선택
  - 대소문자 구분 옵션 선택시 일부 Mac Application 에서 문제가 발생 할 수도 있음
- 디스크 유틸리티를 탈주 후 MacOS 다시 설치 선택. (인터넷 연결 필요)
- 설치까지 한 30분 가량 걸림

## 재설치 마무리

- 재설치 완료 후 국가 선택 - 대한민국
- 키보드 레이아웃 - 한국어 (두벌식)
- 인터넷 연결 - 우선 와이파이
- Apple 계정 연결 및 MacOS 사용자 계정 생성
- 시간대, 하드디스크 암호화, 시리 사용 설정 등 입맛대로 설정

## MacOS 환경 설정

### 한-영 전환 단축키 변경

- 시스템 환경 설정 - 키보드 - 단축키 - 입력 소스

### 키보드 키 반복 설정

- 시스템 환경 설정 - 키보드 - 키보드에서 `키 반복`, `반복 지연 시간` 조절

### F1, F2 키를 표준 기능 키로 사용

- 시스템 환경 설정 - 키보드 - 키보드에서 `F1, F2 등의 키를 표준 기능 키로 사용` 체크

## 개발 환경 설정

> 지극히 개인적인 개발 환경 설정 by Yowu

### Chrome

- 나는 이제 구글 크롬의 노예 
- https://chrome.com
- 설치 후 계정 연결

### iTerm2 

- Terminal 말고 iTerm2 를 쓰자
- https://www.iterm2.com
- 커스터마이징
  - iTerm2 Menu - Preferences - Profile
  - Colors - Color Preset 은 Tango Dark 추천
  - Text - Font 는 Powerline Mono 계열 추천
    - [Ubuntu Mono derivative Powerline](https://github.com/powerline/fonts/tree/master/UbuntuMono) 

### Homebrew

- MacOS 계의 apt
- https://brew.sh
```bash
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```


### git

```bash
brew install git
```

### zsh & oh my zsh

```bash
brew install zsh && chsh -s `which zsh`
```
- zsh 시 올바르지 않은 shell  에러 발생 시 `/etc/shells` 에 which zsh 의 결과 값 추가
- [zsh 설치와 유용한 플러그인](https://github.com/uyu423/TIL/blob/master/Terminal/zsh-%EC%84%A4%EC%B9%98-%ED%9B%84-%EC%9C%A0%EC%9A%A9%ED%95%9C-%ED%94%8C%EB%9F%AC%EA%B7%B8%EC%9D%B8.md) 참고

### Vim (with Plugins)

```bash
brew install vim && echo alias vi="/usr/local/bin/vim" >> ~/.zshrc && source ~/.zshrc
```
- 플러그인 쪽은 https://github.com/uyu423/vimrc-vundle-script 참고

### Visual Studio Code

- https://code.visualstudio.com
- `code` shell command 추가
  - `cmd` + `shift` + `p`
  - Shell Command: Install 'code' command in PATH
- [vscode 초기설정](https://github.com/uyu423/TIL/blob/master/VsCode/%EC%B4%88%EA%B8%B0%20%EC%84%B8%ED%8C%85.md) 문서와 [vscode 환경설정 json](https://github.com/uyu423/TIL/blob/master/VsCode/json%20%EC%84%A4%EC%A0%95.md) 문서 참고

### GitKraken

- https://www.gitkraken.com/download/mac
- Github Login 후 [GitKraken에서 Group의 Private Repository Clone하기](https://github.com/uyu423/TIL/blob/master/git%EA%B3%BC%20Github/GitKraken%EC%97%90%EC%84%9C%20Group%EC%9D%98%20Private%20Repository%20Clone%ED%95%98%EA%B8%B0.md) 참고  

### Node.js

- https://nodejs.org

### Paw

- https://paw.cloud

### Charles

- https://www.charlesproxy.com/
