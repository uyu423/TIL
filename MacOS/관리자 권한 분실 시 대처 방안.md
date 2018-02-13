# MacOS 관리자 권한 분실 시 대처 방안

## Background
- 회사에서 지급 받은 맥북 프로의 사용자 이름을 변경하려고 함.
- 이름을 변경했더니 바뀌라는 이름은 안바뀌고 관리자 권한만 날아 감
- root 비밀번호를 설정해뒀으면 root 관리자 권한으로 어떻게든 했을 텐데, root 비번도 설정해두지 않았음.
- ...??!

## Do
- 맥북 재시동하고 부팅 화면에서 cmd + s 누르고 있으면 root 권한을 가진 터미널 창으로 진입함
- 다음 커맨드로 / 마운트 해제
    ```bash
    /sbin/mounrt -uw /
    ```
- `/etc/sudoers 에 sudo 권한을 줄 사용자 추가
  ```
  # root and users in group wheel can run anything on any machine as any user
  root		ALL = (ALL) ALL
  %admin		ALL = (ALL) ALL
  yowu		ALL = (ALL) ALL
  ```
- 재부팅
  ```bash
  reboot
  ```
- 맥북 로그인 후 터미널에서 루트 로그인 취득 후 root 비밀번호 변경
  ```bash
  yowu) sudo -i
  root) passwd
  ```
- 맥북 환경 설정 '사용자 및 그룹' 에서 이제 관리자 권한을 root 로 취득 가능
- 관리자 권한 줄 사용자에게 권한 주고 재시동
- 해결
