# Vim에 Node.js 환경 구축하기
- 말이 Node.js지 사실 vim에서의 Javascript 개발 환경 구축이라고 봐도 무방하다..

## 하이라이팅이 날 미치게 해...!
![image](https://cloud.githubusercontent.com/assets/8033320/21022047/83293fc8-bdbe-11e6-80c4-588744f8ced3.png)
- 얼마전에 vim 플러그인들을 한번 정리했는데, 그 때 js 관련 플러그인 몇 개가 같이 갈려들어간 듯 하다.
- 그리고 \`String\`나 `${}` 같은 것들을 사용하기 시작했는데, 하이라이팅이 완전 똥망이다.
- 이대로는 안된다..! 이번 기회에 vim을 렙업 좀 시키고 vim의 javascript 스탯에 투자를 해야겠다.

## 일단 Vim Plugin Manager `Vundle`을 설치해보자
- Vundle이 설치되어 있지 않는 분들을 위한 문단.. 난 이미 설치 되어있다..
- 나는 Vim Plugin Manager로 이미 [Vundle](https://github.com/VundleVim/Vundle.vim)을 사용한다.
- 간단한 Vundle 설치법
```bash
git clone https://github.com/gmarik/Vundle.vim.git ~/.vim/bundle/Vundle.vim
```
- Vundle 설치와 설정에 대해 참고할 만한 URL
  - [VundleVim/Vundle](https://github.com/VundleVim/Vundle.vim)
  - [uyu423/vimrc-vundle-script](https://github.com/uyu423/vimrc-vundle-script)
  - [내맘대로 쓰는 vim 플러그인과 .vimrc 설정](http://luckyyowu.tistory.com/308)

## Javascript 관련 플러그인들
- 나는 주로 `Javascript`를 `Node.js`와 가끔씩 쓸 일이 생기는 `React.js`를 사용해 개발하고 있으며, 최근에 `ECMA2015 (ES6)` 문법을 적용하여 열심히 사용 중이다.
- 그래서 이와 관련된 플러그인들을 설치할 것이다.
- Vundle을 사용하여 Plugin을 설치하는 방법을 일반적으로 테크를 타면 된다.
  1. 설정하려는 플러그인을 찾자 일반적으로 [구글링](http://google.com), [vim.org](http://vim.org), [vimawesome](http://vimawesome.com/) 등을 뒤적거리면 찾을 수 있다. 나는 vimawesome을 추천한다.
  2. `~/.vimrc` 설정 파일 내부의 `call vundle#begin()` 구문과 `call vundle#end()` 구문 사이에 Plugin을 추가해주면 된다. 일반적으로 `Plugin 'pluginName'` 혹은 `Plugin 'maker/pluginName'`이다.
  3. `vim`에 실행하고 `:VundleInstall`을 입력하거나 터미널에서 `vim +VundleInstall +q` 명령어를 입력하면 된다.

### `pangloss/vim-javascript`
- [`vim-javascript`](https://github.com/pangloss/vim-javascript) 플러그인은 vim의 js 기본 Syntax Highlighting과 Indentation을 향상시켜준다.
```viml
Plugin 'pangloss/vim-javascript'
```
- es6 문법도 어느정도 지원해 주는 것 같다.

### `mxw/vim-jsx`
- `React.js`를 사용하다보면 필연적으로 jsx 문법을 사용하게 된다. 당연히 vim의 기본 하이라이팅과 인덴트는 지원을 해주지 않아서 vim으로 react 개발할 때 고통을 받는다.
- [`vim-jsx`](https://github.com/mxw/vim-jsx)는 jsx 문법의 하이라이팅과 인덴트를 지원해주는 플러그인이다.
- 직접 확인한 것은 아니지만 바로 위의 `vim-javascript` 플러그인과 의존성이 있는 것 같다.
```viml
Plugin 'pangloss/vim-javascript'
Plugin 'mxw/vim-jsx''
```
- 여담으로 생각보다 많은 사람들이 react 개발할 때 jsx 문법을 사용하더라도 파일의 확장자를 `*.jsx`로 하지 않고 `*.js`로 하는 경우가 많다. 이 플러그인을 `*.js` 확장자에도 적용하고 싶으면 `.vimrc`에 다음 설정 구문을 추가해주자. (`call vundle#(begin|end)()` 구문 외부에 추가해야한다.)
```viml
let g:jsx_ext_required = 0
```
- 사실 무슨 차이 나는지 잘 모르겠다.

### `isRuslan/vim-es6`
- Write JavaScript ES6 easily with vim. (vim에서 javascript es6를 쉽게 작성하세요.)
 - 라고 [`isRuslan/vim-es6`](https://github.com/isruslan/vim-es6) README에 적혀 있다.
- 사용하기 위해서는 `SirVer/ultisnips` 혹은 `'garbas/vim-snipmate`플러그인이 필요하다고 한다. 플러그인 자체에 스니펫 기능이 있어서 그런 듯. 나는 설치가 덜 귀찮아 보이는 `ultisnips`를 설치했다.
```
Plugin 'SirVer/ultisnips'
Plugin 'isRuslan/vim-es6'
```
- 그런데 테스트를 해봤는데, 솔직히 큰 차이가 없는 것 같다. 혹시 `vim-javascript`와 충돌이 나나..?
  - `vim-javascript`에서 es6 문법을 어느정도 지원해주는 것 같다. (ex. Arrow Function)
- 그냥 한번 추가해보고, 별로 바뀌는게 없다 싶으면 없애버려도 될 듯 하다. 참고로 플러그인 삭제는 `.vimrc`에서 플러그인 구문을 제거하고 vim에서 `:VundleClean`

## 마무리
- 적용 전
![image](https://cloud.githubusercontent.com/assets/8033320/21022047/83293fc8-bdbe-11e6-80c4-588744f8ced3.png)
- 적용 후
![image](https://cloud.githubusercontent.com/assets/8033320/21023587/7be32520-bdc4-11e6-96f7-1ada91775d6a.png)
- 마음이 깨끗해지지고 정신이 맑아지는 기분이다.
- 정리하고 보니 `vim-javascript`가 짱인 것 같다.
- 뭔가 도움이 될 것 같은 URL
  - [Vim Syntastic Plugin에 eslint-es6-airbnb 설정하기](http://luckyyowu.tistory.com/353)

### 다음 TIL 예고 : 좀 더 심화된 기능
- 다음 TIL에서는 `youcompleteme`를 사용하여 javascript 분석 도구인 `tern`을 `vim`에 붙이는 것을 해 볼 것이다.
![image](https://cloud.githubusercontent.com/assets/8033320/21023953/20c188d8-bdc6-11e6-9ae7-7425d013e3b3.png)
