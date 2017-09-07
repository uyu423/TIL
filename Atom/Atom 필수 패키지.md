# Atom Editor 초보자의 필수 패키지 정리
- 전제 조건
  - 나는 Node.js 개발 환경을 목표로 패키지를 설치했다.
  - 나는 Atom 완전 초심자다
  - 나는 원래 vim을 모든 개발에 사용했다.
- 나는 한큐에간다
  ```bash
  apm install vim-mode-plus vim-mode-plus-ex-mode platformio-ide-terminal atom-beautify code-peek highlight-selected linter linter-csslint linter-eslint linter-ui-default busy-signal intentions minimap pigments seti-ui file-type-icons nord-atom-syntax nord-atom-ui
  ```

## vim-mode-plus
- 내가 바로 이 구역의 vim 충이야..!!

## vim-mode-plus-ex-mode
- `vim-mode-plus`에 커맨드 모드까지 사용할 수 있다. 그런데 `w`, `wq`와 같은 기본적인 것들만 지원됨. 좀 불만족 ㅜㅜ

## platformio-ide-terminal
- Atom 내에서 터미널을 사용할 수 있다. 별로 이쁘지는 않다.

## atom-beautify
- 코드를 이쁘게 정렬해준다.

## code-peek
- `Ctrl` + `Left Click` 으로 해당 함수의 선언으로 이동할 수 있다.

## highlight-selected
- 특정 텍스트 블록 선택시 같은 내용의 텍스트를 하이라이팅해준다.

## linter
- 아톰 하단에 메시지 라인을 추가해준다. 다른 추가 패키지와 함께 사용한다.
- `linter v2`의 경우 추가로 필요한 패키지 : `linter-ui-default`, `busy-signal`, `intentions`

## linter-csslint
- linter를 사용하여 css 문법 에러를 찾아준다.

## linter-eslint
- linter를 사용하여 자바스크립트 문법 체크 도구인 eslint를 사용할 수 있다.

## minimap
- 화면 오른쪽에 전체 코드를 나타내는 미니맵을 띄워준다.

## pigments
- CSS에서 사용하는 색상을 확인할 수 있게 해준다.

## seti-ui
- 테마로 설치할 수 있다. 파일 타입별 아이콘을 만들어주고, 영 심심한 Atom 이 좀 더 화려해진다.

## file-type-icons
- 네비게이터의 아이콘을 확장자에 따라 다르게 표현해준다.

## nord-atom-syntax nord-atom-ui
- [nord](https://github.com/arcticicestudio/nord) 테마의 Color Scheme을 따르는 Atom Syntax와 UI Theme다.
