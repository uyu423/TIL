# Zsh
```bash
sudo apt install zsh
chsh -s `which zsh`
```
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
### bulet-train
- 좀 더 유용한 zsh 테마
```bash
wget http://raw.github.com/caiogondim/bullet-train-oh-my-zsh-theme/master/bullet-train.zsh-theme
mkdir $ZSH_CUSTOM/themes
mv bullet-train.zsh-theme $ZSH_CUSTOM/themes/
# .zshrc ZSH_THEME="bullet-train"
```

# scm_breeze
- git 명령어들을 줄여서 간단하게 사용해 줄 수 있게 한다.
- https://github.com/scmbreeze/scm_breeze
```bash
$ git clone git://github.com/scmbreeze/scm_breeze.git ~/.scm_breeze
$ ~/.scm_breeze/install.sh
$ source ~/.bashrc
```
