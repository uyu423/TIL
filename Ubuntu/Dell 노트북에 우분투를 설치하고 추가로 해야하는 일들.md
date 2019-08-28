# Dell 노트북에 우분투를 설치하고 추가로 해야하는 일들

![Ubuntu 18.04 in Dell XPS 13](https://user-images.githubusercontent.com/8033320/63880270-62f0ad00-ca08-11e9-8eef-688c4584d10a.png)

- 2016년 초에 무려 **4 BTC** 로 해외직구한 Dell XPS 13 9350 노트북에 Ubuntu 18.04 LTS 를 올려 사용 중이다.
- Dell XPS 는 Developer Edition 이라고 Ubuntu OEM 으로 운영체제 깔아서 팔기도 한다.
- 그렇다면 분명 Dell 에서 지원하는 Ubuntu 업데이트가 있을거라 생각했는데, 이번에 우연히 `Dell Archive apt Repository` 를 찾아서 적용했기에 기록한다.

## Dell apt Repository 추가

- Ubuntu 18.04 (bionic) 기준

```bash
$ sudo add-apt-repository 'deb http://dell.archive.canonical.com/updates bionic-dell public'
$ sudo add-apt-repository 'deb http://dell.archive.canonical.com/updates bionic-dell-service public'
$ sudo add-apt-repository 'deb http://dell.archive.canonical.com/updates bionic-oem public'
```

- 다른 버전을 사용하고 있다면 중간의 버전 코드 값을(bionic) 적절하게 변경한다.
- `bionic-dell`, `bionic-dell-service` 와 같은 값들은 조금씩 변경되었을 수도 있다. 만약 특정 uri 가 404 Not Found 발생한다면 해당 레포지터리의 [dist](http://dell.archive.canonical.com/updates/dists/) 에서 직접 찾아보자.

## Dell apt Repository 를 사용하기 위한 gpg 키 추가

- 위 레포지터리를 추가하고 `sudo apt update` 하면 공개키가 없어 에러가 발생한다.

```bash
W: GPG 오류: http://dell.archive.canonical.com/updates bionic-dell Release: 다음 서명들은 공개키가 없기 때문에 인증할 수 없습니다: NO_PUBKEY 1234567890ABCDEF
E: The repository 'http://dell.archive.canonical.com/updates bionic-dell Release' is not signed.
N: Updating from such a repository can't be done securely, and is therefore disabled by default.
N: See apt-secure(8) manpage for repository creation and user configuration details.
```

- NO_PUBKEY 다음의 서명으로 공개키 추가해준다.
- 위 예제에서는 `1234567890ABCDEF` 로 표시했지만 본인 터미널에 출력된 값을 사용한다.

```bash
$ sudo gpg --keyserver pool.sks-keyservers.net --recv-key 1234567890ABCDEF
gpg: WARNING: unsafe ownership on homedir '/home/yowu/.gnupg'

gpg: key 1234567890ABCDEF: public key "Canonical Archive Automatic Signing Key <ftpmaster@canonical.com>" imported
gpg: Total number processed: 1
gpg:               imported: 1
```

```bash
$ gpg -a --export F9FDA6BED73CDC22 | sudo apt-key add -
OK
```

## 마무리

- 이제 `sudo apt update` 하면 정상적으로 dell archive repository 를 사용할 수 있다.
- 나는 다음 2개 업데이트가 설치되었는데 뭔지는 모르겠다.

```bash
$ apt list --upgradable
리스팅... 완료
fwupd/알 수 없음 1.2.5-1~somerville1 amd64 [upgradable from: 1.0.9-0ubuntu2]
libfwupd2/알 수 없음 1.2.5-1~somerville1 amd64 [upgradable from: 1.0.9-0ubuntu2]
```

끝. ~~아.. 저 때 구매 실패해서 까먹고 4 BTC 를 묵혀두기만 했으면...~~
