- 우분투 17.04 부터는 스왑 메모리를 스왑 파티션을 사용하지 않고 스왑 파일로 사용함.
- 이전 처럼 `gparted`와 같은 파티션 도구로 스왑을 조절 할 수 가 없다.
- 스왑 파일의 기본 위치는 `/swapfile`

## 스왑 파일 마운트 해제
```bash
sudo swapoff /swapfile
```

## 스왑 파일 생성
```bash
sudo fallocate -l 16g /swapfile # 16g에 원하는 스왑 파일 크기 설정
sudo chmod 600 /swapfile
sudo mkswap /swapfile
```

## 스왑 파일 마운트
```bash
sudo swapon /swapfile
```
