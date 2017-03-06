이번에 회사 SSL 계정이 만료됨에 따라 새로운 SSL 인증서를 발급하는 작업을 했다. 그리고 때 맞춰 회사의 랜딩 페이지가 새로 만들어졌기에 nginx에 SSL을 붙이는 작업도 병행했다.

## 1. openssl 로 개인키(Private Key) 생성
```bash
openssl req -new -newkey rsa:2048 -nodes -keyout example.key -out example.csr
```
- `exmaple.key` 는 RSA 2048 bit 방식을 사용하는 개인키다.
`example.csr` 은 Certificate Signing Request 의 약자로, 인증서를 발급받기 위해 개인이나 단체의 정보가 포함된 인증서다. SSL 인증기관에 신청시 이 csr 파일의 값을 제출한다.
- nginx에서 개인키를 SSL로 사용하기 위해서는 `example.key` 파일을 RSA 방식으로 한번더 인코딩을 해줘야한다.
```bash
openssl rsa -in example.key -out example-rsa.key
```

## 2. SSL 인증서 구입
- 나는 [ssls.com](https://ssls.com) 이라는 COMODO 인증 기관 대행(?) 사이트를 이용했다. 이 곳은 SSL을 구입한뒤 CSR 파일을 제출하여 SSL을 Activate 하는 방식으로 진행된다.
- CSR 파일 제출 후 몇 단계를 거치면 SSL을 적용할 사이트 루트 디렉토리에 인증 파일을 업로드하라고 한다. 적절하게 업로드 한 뒤 정상적으로 처리 된 다면 잠시 후 메일로 SSL 인증에 필요한 CA 파일들이 날아온다.
- 나는 다음과 같은 파일들을 받았다.
```bash
AddTrustExternalCARoot.crt
COMODORSADomainValidationSecureServerCA.crt
COMODORSAAddTrustCA.crt
STAR_example_co_kr.crt
```
- `STAR_example_co_kr.crt` 파일을 제외한 나머지는 SSL 인증서의 유효성을 체크하는 Certificate 들이다.
- 위 4개의 파일은 나중에 nginx에서 사용한다. 그러기 위해서는 하나의 파일로 번들링해두어야 한다. 다음과 같이 `cat` 명령어로 쉽게 bundling 할 수 있다. 미리 해두자
```bash
cat STAR_example_co_kr.crt \
COMODORSADomainValidationSecureServerCA.crt \
COMODORSAAddTrustCA.crt \
AddTrustExternalCARoot.crt > example.ca-bundle
```

## 3. nginx 설정
- 위에서 만든 `example.ca-bundle` 파일과 `example-rsa.key` 파일을 적절한 위치에 집어넣자. 나는 `/etc/nginx/ssl` 에 넣었다.
- 이제 SSL 적용을 위해 `/etc/nginx/sites-available` 에 있는 사이트 설정 파일을 수정하자.
```nginx
server {
    listen 443 ssl default_server;
    listen [::]:443 ssl default_server;

    ssl on;
    ssl_certificate /etc/nginx/ssl/example.ca-bundle;
    ssl_certificate_key /etc/nginx/ssl/eample-rsa.key;
    ssl_prefer_server_ciphers on;

    server_name example.co.kr
    ...
}
```
### 약간의 꿀팁
  - 기존 http(80)을 https(443)으로 포워딩(리다이렉션) 하기 위해서는 사이트 설정 파일에 다음 구문을 추가하자
  ```nginx
  server {
      listen 80;
      server_name example.co.kr;
      rewrite ^ https://$server_name$request_uri? permanent;
  }
  ```
  - 설정을 마치고 `sudo service nginx restart` 명령어로 nginx를 재시작 할 때 에러가 나는 경우가 있다. 다음 명령어로 위험을 줄일 수 있다.
  ```bash
  nginx -c /etc/nginx/nginx.conf -t # 설정파일 미리 검사.
  sudo service nginx reload # 서비스를 재시작 하지 않고 설정 파일만 다시 불러온다. 설정이 잘못되더라도 서비스가 꺼지지 않는다.
  ```

## 4. 마무리
- 이제 https (SSL) 설정이 잘 되었다.
- 사실 최근 몇 년간 Apache2만 썼었는데, 요즘 nginx를 열심히 써보니 nginx가 좀 더 나은 것 같다. 무게 대비 성능이라던지 등등.
