- `nginx`를 proxy server로 사용하고 `pm2`를 사용해 `nginx` 뒤에서 앱을 구동하다로 구동하다 보니 log의 ip가 모두 127.0.0.1 로 찍힌다. 이를 해결해보자

```javascript
const express = require('express');
const morgan = require('morgan');

const app = express();

app.enable('trust proxy');
app.set('trust proxy', () => true);
app.use(morgan('combined'));

// 223.62.8.96 - - [08/May/2017:08:38:09 +0000] "GET /?query=%EB%AA%A9%EB%8F%99 HTTP/1.0" 200 4577 "-" "okhttp/3.4.1"
```

- http://expressjs.com/ko/guide/behind-proxies.html
- https://github.com/expressjs/morgan/issues/114
