[이미지]

회사의 production 인스턴스가 `AWS VPC` 내부에 있어서 인터넷 망으로는 접근이 되지 않는다. 회사가 OpenVPN 서비스를 사용 중이었으므로 OpenVPN을 써서 접속해야되는데, Windows나 Mac에서는 설치 파일하나로 잘만 되더니 Ubuntu Linux에서는 잘 안된다. OpenVPN 사이트에서 `openvpn` 명령어와 `*.ovpn` 파일을 사용해 VPN에 연결하는 방법이 안내되어 있지만 영 안된다.(Gnome의 Netwrok Manager 때문으로 추측한다. GUI Enviorment가 없으면 명령어로 될지도...) 이리저리 헤맨 끝에 접속 성공한 로그를 남긴다.

- 환경 : `Ubuntu Gnome 16.10`

# network-manager-openvpn-gnome 설치
[이미지]
```bash
sudo apt install network-manager-openvpn-gnome
```
