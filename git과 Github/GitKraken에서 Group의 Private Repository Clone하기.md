# GitKraken에서 Group의 Private Repository Clone하기

- GitKraken을 만든 axosoft에서 GitHub Enterprise 활성화(유료)를 팔아먹기 위해서인지 GitKraken에서 생성하고 자동으로 등록되는 SSH Key로는 절대 Group의 Private Repository를 가져올 수 없다.
- 아무리 생각해도 안되는게 이상해서 몇 가지 테스트 해보니 방법을 찾아냈다.
- 우선 `ssh-keygen` 명령어(윈도우의 경우 Bash on Windows를 활용)로 private key와 public key를 생성해주자.
```bash
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
```
- 생성된 `id_rsa`와 `id_rsa.pub` 파일을 잘 가지고 있자. `id_rsa`는 개인키 `id_rsa.pub`는 공개키다.
  - 생성된 파일을 윈도우로 옮기려면 `/mnt` 디렉토리를 확인해보자. 본인의 드라이브들을 확인할 수 있다.
- Github의 Profile Setting - SSH and GPG keys 메뉴에서 생성된 공개키를 New SSH Key 버튼을 눌러 등록해주자.
- 이제 GitKraken의 Preferences 메뉴에서 Authentication에서 General 탭과 Github.com 탭에서 생성된 id_rsa와 id_rsa.pub를 등록해주자.
- 이제 `git@github.com:*/*.git` 형태의 SSH git 주소를 Clone 시도해보자.
