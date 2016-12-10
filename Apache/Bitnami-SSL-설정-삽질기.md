# Bitnami Apache2 SSL 설정 삽질기

## Trouble Shooting 부들부들..
- 회사 랜딩 페이지(공식 홈페이지)가 특정 기기(이라 쓰고 모바일이라 읽는다)에서만 SSL 인증 문제가 발생했다.(CA 인증 실패) 설정파일에서 Certificate파일과 Private Key파일, Chain 파일까지 모두 제대로 잡았다고 생각했는데, 적용이 안되는 상황. 원인부터 밝히자면 내가 SSL 설정을 잡았던 그 `conf` 파일이 사실은 `YOU JUST ACTIVATED MY TRAP CARD` 였던 상황
- 사실 이 TIL을 작성하게된 결정적인 계기는 EC2 AMI에 있는 `Bitnami` 라는 친구 덕분이다. [Bitnami](https://bitnami.com/aws) 는 서버 설정의 많은 것을 생략할 수 있게 해주는 좋은 친구지만 디테일한 설정을 하려면 약간의 러닝 커브가 생긴다.
- 심지어 Apache와 같은 패키지가 APT로 관리가 되지 않는 것 같다. 수 많은 개발자들이 거쳐간 EC2에는 온갖 잡다한 중복 설정이 존재했고, Apache가 두 개 설치되어 있었다.
  - `/usr/sbin/apache2` 그리고 `/opt/bitnami/apache2/bin/httpd`
  - 하나는 APT로 설치가 되고, 다른 하나는 bitnmai AMI를 사용하여 인스턴스를 찍어낼 때 자동으로 import 되는 것 같다.
  - 이 때 아파치 설정 파일이 포함된 디렉토리의 경로도 두개가 되므로 이를 처음 접한 서버 관리자는 혼비백산하게 된다.
    - `/etc/apache2/apachd2.conf` 그리고 `/opt/bitnami/apache2/conf/httpd.conf`
  - 두개의 아파치가 설치되어 있을 경우 `ps` 명령어를 사용하여 정확하게 어떤 친구가 프로세스로 돌아가고 있는지 확인해보아야한다.

  ```bash
  ps -ef | grep apache2
  ```

  - 더 열받는 것은 `bitnami`가 나름 유지보수를 위해 간지나는 구조로 가져갈 생각이었는지 `*.conf` 파일을 오만 곳에 다 분산시켜놨다는 것이다. 예를 들어 `apache2`의 전역 `httpd-vhost.conf`가 있고, `bitnami` APP 전역 설정에 사용되는 수 많은 `*.conf`가 있으며, bitnami APP으로 사용할 수 있는 `wordpress`나 `phpmyadmin`에도 각각 `*.conf`가 있다..! 와우!!!
- 여러군데 SSL 인증서 셋업을 해본 결과 정답은 `/opt/apache2/conf/bitnami/bitnami.conf`에 SSL 설정을 하니 잘 되었다. 이 결과를 얻기 까지 다음과 같은 삽질을 했다.
  - `/etc/apache2/apache2.conf`에 SSL 설정. 실패.
  - `/opt/bitnami/apache2/conf/extra/httpd-ssl.conf`에 SSL 설정. 실패.
  - `/opt/bitnami/apps/wordpress/conf/httpd-vhost.conf`에 SSL 설정. 될 때도 있고 안될 때도 있음. SSL Tool을 통과하지 못함. 실패

## 본론을 얘기해보자
- 드디어 SSL 설정 자체에 대한 삽질의 얘기다.

### Apache2의 mod_ssl 의 중요 변수
#### SSLEngine
- SSL 엔진을 쓰냐 마느냐를 결정한다. 당연히 `on`이 되어있어야 사용할 수 있다.

```bash
SSLEngine on
```

#### SSLCertificateKeyFile
- 이건 Private Key 파일의 경로를 찍어줘야한다. 일반적으로 `*.key` 확장자를 가진다.

```bash
SSLCertificateKeyFile "/etc/ssl/ssl.key/server.key"
```

#### SSLCertificateFile
- 이건 Certificate 파일(Public Key 맞나?)의 경로를 찍어준다. 일반적으로 `*.crt`의 확장자를 가진다.

```bash
SSLCertificateFile "/etc/ssl/ssl.crt/yourDomainName.crt"
```

#### SSLCertificateChainFile 그리고 SSLCACertificateFile
- 내 삽질의 원흉.
- 사실 `Certificate Chain`이란 브라우저나 앱에 CA List가 없을 경우 해당 CA의 유효성을 판단하기 위해 등록하기 여러개의 `*.crt`가 합쳐진(Bundling 된) 파일이다. 일반적인지는 모르겠지만 나는 `*.ca-bundle` 확장자를 사용했다.
  - Certificate Chain에 대한 원리는 여기를 참고하자
  - [인증서 체인이 작동하는 방법](http://www.ibm.com/support/knowledgecenter/ko/SSFKSJ_7.1.0/com.ibm.mq.doc/sy10600_.htm)
- Apache2에서는 이 두 친구가 같은 의미로 사용되는데 `2.4.8` 버전 이후로 `SSLCertificateChainFile`가 Deprecated 되고, `SSLCACertificateFile`가 사용된다고 한다.
- 현재 굴러가는 bitnami Apache2의 버전을 굳이 알아내려면 알 수 있었겠지만 그냥 다음과 같이 `ifVersion` 기능을 사용하여 `conf` 파일을 수정했다.

```bash
<IfVersion < 2.4.8>
  SSLCertificateChainFile "/etc/ssl/ssl.crt/yourDomainName.ca-bundle"
</IfVersion>
<IfVersion >= 2.4.8>
  SSLCACertificateFile "/etc/ssl/ssl.crt/yourDomainName.ca-bundle"
</IfVersion>
```

### 전체...! 전체를 보자..!!
- 아래는 `apache2`에서 `mod_ssl`이 include되어있고, vHost를 사용하여 SSL을 활성화 시키는 부분이다.

```bash
<IfModule !ssl_module>
  LoadModule ssl_module modules/mod_ssl.so
</IfModule>

Listen 443
SSLProtocol all -SSLv2 -SSLv3
SSLHonorCipherOrder on
SSLCipherSuite "EECDH+ECDSA+AESGCM EECDH+aRSA+AESGCM EECDH+ECDSA+SHA384 EECDH+ECDSA+SHA256 EECDH+aRSA+SHA384 EECDH+aRSA+SHA256 EECDH !aNULL !eNULL !LOW !3DES !MD5 !EXP !PSK !SRP !DSS !EDH !RC4"
SSLPassPhraseDialog  builtin
SSLSessionCache "shmcb:/opt/bitnami/apache2/logs/ssl_scache(512000)"
SSLSessionCacheTimeout  300

<VirtualHost *:443>
  DocumentRoot "/opt/bitnami/apache2/htdocs"
  SSLEngine on
  SSLCertificateFile "/etc/ssl/ssl.crt/server.crt"
  SSLCertificateKeyFile "/etc/ssl/ssl.crt/server.key"
  <IfVersion < 2.4.8 >
      SSLCertificateChainFile "/etc/ssl/ssl.crt/server.ca-bundle"
  </IfVersion>
  <IfVersion >= 2.4.8 >
      SSLCACertificateFile "/etc/ssl/ssl.crt/server.ca-bundle"
</IfVersion>
```

## 마무리
- bitnami 같은거 안 썼으면 좋겠다..
- 참고 링크
  - https://support.comodo.com/index.php?/Default/Knowledgebase/Article/View/637/37/certificate-installation-apache--mod_ssl
