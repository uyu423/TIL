# PhoneGap : Content-Security-Policy 메타 태그를 사용하여 외부 컨텐츠를 허용해보자

## 도대체 왜 이런 TIL을 작성하나?
- 이왕에 폰갭으로 Hello World를 찍은 김에 **기존 React Project 중 하나를 폰갭으로 이식해보자!** 라는 원대한 꿈을 가짐.
- 이식해보려는 프로젝트는 `Serverless Architecture`를 준비하면서 만들었던 `Pure React Web App`형태의 웹 페이지였음. (해당 React App을 구동하는데 필요한 서버가 없음, 필요한 데이터 작업은 API 콜을 사용함)
- 해당 React 프로젝트를 `npm run build` 후 나온 `html`과 `css`, `js` 파일을 폰갭 프로젝트의 `www`에 집어넣고 `phonegap serve` !!
- 안드로이드 테스트 앱으로 확인해보니 **이미지 리소스가 전혀 뜨지 않음.** 그리고 콘솔에는 다음과 같은 `Warning`이 출력됨.
```bash
[phonegap] [console.warn] Content Security Policy has been added:
<meta http-equiv="Content-Security-Policy" content="default-src * gap: ws: https://ssl.gstatic.com;img-src 'self' data: content:;style-src 'self' 'unsafe-inline' data: blob:;script-src * 'unsafe-inline' 'unsafe-eval' data: blob:;">
```

## 도대체 이 문제가 왜 발생하였나?
- [Weinre](https://www.npmjs.com/package/weinre)라는 원격 디버깅 툴로 체크해봤지만 아무것도 뜨지 않았음.
- 해당 React 프로젝트는 대부분의 Static Resource(Image, Font 등)를 CDN에 넣어두고 필요할 때만 `Http GET Request`를 통해 가져오고 있었음.
- 대충 구글을 훓어보니 XSS Injection을 방지하기 위해 [Github Issue](https://github.com/phonegap/connect-phonegap/issues/143)에서 다양한 논의가 오고갔으며 **결국 `Content-Security-Policy`(이하 `CSP`) 메타 태그로 허가 되지 않은 URL에서 Static Resource를 가져오는 것이 막히게 되었음.**

## 그렇다면. 우리는. 이것을. 어떻게. 대처해야하나??
- 영어에는 취약하지만 왠지 위 `Warning`에 나온 `meta` 태그를 추가해줘야 할 것만 같다..!
- 그래서 `index.html`에 다음 메타 태그를 추가해주었다.
```html
<meta http-equiv="Content-Security-Policy" content="default-src * gap: ws: https://ssl.gstatic.com; style-src * 'unsafe-inline' data: blob: 'self' ;script-src * 'unsafe-inline' 'unsafe-eval' * data: blob: ;img-src https://당신이허가하려는URL data: content: * 'self';">
```
  - https://ssl.gstatic.com : 외부의 gap과 ws와 관련된 리소스들을 가져올 수 있도록 Default로 포함된듯 하다.
  - 나의 경우 현재 이미지 리소스를 가져오는 것이 문제였으므로 `img-src` 다음에 허가 해주려는 URL을 추가해주었다.
- 이제 이미지 리소스가 잘 뜬다.
![image](https://cloud.githubusercontent.com/assets/8033320/20536931/73723892-b12e-11e6-8834-8147148cd354.png)
![image](https://cloud.githubusercontent.com/assets/8033320/20536936/769cda4a-b12e-11e6-95d5-f35764c1d548.png)

## 기타사항
- `PhoneGap (Adobe)` 말고 부모 프로젝트 격인 `Cordova (Apache)`의 경우 [`cordova-plugin-whitelist`](https://github.com/apache/cordova-plugin-whitelist/tree/master/doc/ko) 라는 친구가 있다. 이 친구가 폰갭에도 적용될런지는 아직 모르지만 현재 단계에서는 필요하지 않아 사용을 하지 않았다.
  - 혹시나 싶어 폰갭 프로젝트 루트 디렉토리의 `config.xml`에 `<allow-navigation href="*://*.내가허가하려는URL/*" />`를 추가해봤었지만 쓸모가 없었다.
- 안드로이드의 경우 `CSP`에 관련된 기능을 4.4 (Kitkat) 부터 지원한다고 함.
- React App 내에서 사용한 [`node-fetch`](https://www.npmjs.com/package/node-fetch)와 같은 `XHRHttpRequest` 친구들은 `CSP` 없이도 Call이 잘 되었음...? (이젠 나도 뭐가 뭔지 모르겠다.)
- 아직 `apk` 파일로 빌드해본 것이 아니니 방심할 수는 없다..
- 참고 URL
  - [content security policy(CSP) - 소개](http://gseok.tistory.com/entry/Web-TechIntroduction-Content-Security-Policy)
  - [(W3C) Content Security Policy Level 3](https://w3c.github.io/webappsec-csp/)
  - [cordova-plugin-whitelist Document](https://cordova.apache.org/docs/en/latest/reference/cordova-plugin-whitelist/)
