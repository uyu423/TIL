# Zsh
```bash
sudo apt install zsh
chsh -s `which zsh`
```
- `chsh` 로 기본 셸 변경 불가시 `which zsh` 의 값을 `/etc/shells` 에 추가

## Edit ~/.zshrc
```bash
ZSH_THEME="agnoster"
```
# Oh my zsh
```bash
curl -L https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh | sh
```
## Plugins
### zsh-autosuggestions
- 명령어 자동완성 추천
```bash
git clone git://github.com/zsh-users/zsh-autosuggestions $ZSH_CUSTOM/plugins/zsh-autosuggestions
# .zshrc plugins=(zsh-autosuggestions)
```
### zsh-syntax-highlighting
- 명령어 하이라이팅
```bash
git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
# .zshrc plugins=( [plugins...] zsh-syntax-highlighting)
```

### zsh-better-npm-completion
- npm run 스크립트 Auto Completion
```bash
git clone https://github.com/lukechilds/zsh-better-npm-completion ~/.oh-my-zsh/custom/plugins/zsh-better-npm-completion
# ./zshrc plugins=( [...plugins] zsh-better-npm-completion )
```

### bullet-train

- 좀 더 유용한 zsh 테마
```bash
wget http://raw.github.com/caiogondim/bullet-train-oh-my-zsh-theme/master/bullet-train.zsh-theme && mkdir $ZSH_CUSTOM/themes && mv bullet-train.zsh-theme $ZSH_CUSTOM/themes/
# .zshrc ZSH_THEME="bullet-train"
```
- `.zshrc` 에 아래 내용을 추가하면 `hostname` 을 제거할 수 있다.
```bash
prompt_context() {
  if [[ "$USER" != "$DEFAULT_USER" || -n "$SSH_CLIENT" ]]; then
    prompt_segment black default "%(!.%{%F{yellow}%}.)$USER"
  fi
}
```

# scm_breeze
- git 명령어들을 줄여서 간단하게 사용해 줄 수 있게 한다.
- https://github.com/scmbreeze/scm_breeze
```bash
$ git clone git://github.com/scmbreeze/scm_breeze.git ~/.scm_breeze
$ ~/.scm_breeze/install.sh
$ source ~/.bashrc
```
