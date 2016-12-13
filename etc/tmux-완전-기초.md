# tmux 완전 기초
![image](https://cloud.githubusercontent.com/assets/8033320/21155711/89a95990-c1b6-11e6-9cc1-4e7dd58a0160.png)
- 이젠 tmux도 적절하게 써야할 때..! 모니터가 한 4대 정도 되면 안써도 될 것 같다.

## 설치
- Ubuntu
```bash
sudo apt install tmux
```
- MacOS
```bash
brew install tmux
```

## 실행
```bash
tmux
```

## 기본 사용법
- 사실 그냥 지금 당장 나한테 필요한 기능만..
- `Ctrl` + `b`, `%` : 종으로 화면 분할
- `Ctrl` + `b`, `"` : 횡으로 화면 분할
- `Ctrl` + `b`, `방향키` : 화면 이동
- `Ctrl` + `b`, `:`
  - `resize-pane -U 10` : 현재 윈도우 위로 10 Row 크기 조절
  - `resize-pane -D 10` : 현재 윈도우 아래로 10 Row 크기 조절
  - `resize-pane -L 10` : 현재 윈도우 왼쪽으로 10 Row 크기 조절
  - `resize-pane -R 10` : 현재 윈도우 오른쪽으로 10 Row 크기 조절

## tmux에서 Vim Color Scheme이 제대로 나타나지 않을 때
- `~/.tmux.conf`에 다음 내용 추가
```
set -g default-terminal "screen-256color"
```
