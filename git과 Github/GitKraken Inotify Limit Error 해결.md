# GitKraken Inotify Limit Error 해결

- 리눅스 커널 기반 운영체제에서 `GitKraken` 을 사용하다보면 `Inotify Limit Erorr` 를 만나게될 확률이 굉장히 높다.
- `GitKraken` 은 파일 시스템의 변경 사항을 실시간으로 추적하는데 우부투 커널 내의 `Inotify` 서브 서비스를 사용한다.
- (아래 내용은 `Ubuntu 18.04` 기준이다)

## 현재 Inotify Limit 확인

```bash
cat /proc/sys/fs/inotify/max_user_watches
8192
```

## 일시적인 Inotify Limit 변경

- 아래 커맨드를 사용하여 일시적으로 Inotify Limit 을 변경할 수 있다. 현재 세션에서 유지됨

```bash
echo 99999 > /proc/sys/fs/inotify/max_user_watches
cat /proc/sys/fs/inotify/max_user_watches
99999
```

## 영구적인 Inotify Limit 변경

- 아래 커맨드를 사용하여 영구적으로 Inotify Limit 을 변경할 수 있다.

```bash
echo fs.inotify.max_user_watches=99999 | sudo tee -a /etc/sysctl.conf && sudo sysctl -p
cat /proc/sys/fs/inotify/max_user_watches
99999
```

## 참고

- [Wikipedia - Inotify](https://ko.wikipedia.org/wiki/Inotify)
- [Techsparx - Gitkraken Inotify](https://techsparx.com/blog/2018/02/gitkraken-inotify.html)