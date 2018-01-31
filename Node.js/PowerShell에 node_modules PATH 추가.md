# PowerShell에 `./node_modules/.bin` PATH 추가

- cmd는 잘 모르겠고, 언젠가부터 Atom 패키지 `platformio-ide-terminal`의 윈도우 기본 터미널이 PowerShell이 되었다.
- pm2나 typescript, eslint 등 바이너리 패키지를 devDependecies로 사용하는데 평소 윈도우 개발시 cmd에 PATH 추가가 잘 안되어서 열 받았었다.
- PowerShell에서는 명령어 한 줄로 현재 프로젝트의 `./node_modules/.bin` 을 PATH 추가 할 수 있다.
```
$env:PATH += ';.\node_modules\.bin'
```
- 출처: https://stackoverflow.com/questions/45280752/can-i-include-a-folder-relative-to-the-current-directory-in-path-in-powershell
