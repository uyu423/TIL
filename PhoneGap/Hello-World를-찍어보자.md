# PhoneGap으로 Hello World를 내 폰에 찍어보자
- 나는 CLI 성애자이니 `phonegap-cli`를 사용하여 내 폰에 Hello World를 찍어내겠다..!
- PhoneGap official site : http://phonegap.com/

## Requirement
- Node.js
- git

## Install `phonegap-cli`
```bash
sudo npm install phonegap --global
```

## Install PhoneGap Development App (Android)
![image](https://cloud.githubusercontent.com/assets/8033320/20527118/82d35614-b10a-11e6-837d-31d3a528c490.png)
- https://play.google.com/store/apps/details?id=com.adobe.phonegap.app

## Make New PhoneGap App Project
```bash
phonegap create phonegap-hello
```

## Running PhoneGap Development Server
```bash
cd phonegap-hello && phonegap serve
```
```bash
$ phonegap serve
[phonegap] starting app server...
[phonegap] listening on 192.168.0.254:3000
[phonegap] listening on xxx.xxx.xxx.xxx:3000
[phonegap] listening on xxx.xxx.xxx.xxx:3000
[phonegap] listening on xxx.xxx.xxx.xxx:3000
[phonegap]
[phonegap] ctrl-c to stop the server
[phonegap]
```

## Connect Your Android Device to PhoneGap Server
- Input server address at Phonegap Dev App

![image](https://cloud.githubusercontent.com/assets/8033320/20527078/56f5b88e-b10a-11e6-822e-dce06640bff6.png)

![image](https://cloud.githubusercontent.com/assets/8033320/20527179/af5b110e-b10a-11e6-8004-9ae976c29f69.png)

## Modify Context
- Open `phonegap-hello/www/index.html`

![image](https://cloud.githubusercontent.com/assets/8033320/20527236/e7c38e54-b10a-11e6-8513-a302322e12ba.png)

![image](https://cloud.githubusercontent.com/assets/8033320/20527289/16d84568-b10b-11e6-8daf-e53e655c1a5b.png)
