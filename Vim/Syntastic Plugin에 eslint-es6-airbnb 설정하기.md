# Syntastic Plugin에 eslint-es6-airbnb 설정하기

## npm 패키지 설치
- 우분투 전역(sudo) 설치 기준
```bash
export PKG=eslint-config-airbnb;
npm info "$PKG" peerDependencies --json | command sed 's/[\{\},]//g ; s/: /@/g' | xargs sudo npm install --global "$PKG"
```
- Mac OS
  - 내가 맥을 안써봐서 잘 모르겠다..

## .eslintrc 설정
- 전역 설정
  - `~/.eslintrc` 를 생성하고 다음 내용을 입력
  ```json
  {
    "extends": "airbnb",
    "globals": {
      "_": true,
      "$": true,
    }
  }
  ```
    - _ 와 $ 를 globals로 따로 처리하는 것은 lodash 혹은 underscore와 jQuery에서 에러를 뿜지 않기 위해서..
- 로컬 설정
  - 해당 프로젝트 루트에 `~/.eslintrc`를 생성

## Syntastic plugin 설정
- `Vundle`과 `Syntastic` Plugin 설치
  - 다음 URL들을 참고
    - [내맘대로 쓰는 vim 플러그인과 .vimrc 설정](http://luckyyowu.tistory.com/308)
    - [Syntastic - Vim Awesome](http://vimawesome.com/plugin/syntastic)
- `.vimrc`에 `Syntastic` 설정 추가
  ```viml
  let g:syntastic_javascript_checkers = ['eslint']
  ```
- `Syntastic` + `eslint` + es6,airbnb 컨벤션 적용된 모습
![image](https://cloud.githubusercontent.com/assets/8033320/20301304/1937b5b4-ab66-11e6-9fbd-e2ad25db341b.png)

- 만약 뭔가 잘 안된다면 vim 내에서 `:SyntasticInfo` 명령어로 `eslint`가 잘 잡혀있는지 확인해 볼 수 있다.
![image](https://cloud.githubusercontent.com/assets/8033320/20301638/775dacc4-ab67-11e6-9eb9-d6e2f826f381.png)
