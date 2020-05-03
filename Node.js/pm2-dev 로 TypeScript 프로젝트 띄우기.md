# pm2-dev 로 TypeScript 프로젝트 띄우기

Keymetrics 사의 [pm2](https://pm2.keymetrics.io/) 는 최근 몇년간 가장 많이 쓰이는 **Node.js Process Manager** 가 아닐까 싶습니다. 예전에는 다른 것도 좀 썼던거 같은데, 서비스 제공을 위한 클러스터링, Reload Trigger, 대시보드 등 다양한 기능들이 추가되면서 Node.js 기반의 프로젝트 서빙에서 필수요소 처럼 되어가고 있습니다.

`pm2` 에는 `nodemon` 과 같이 개발을 위한 `pm2-dev` 가 내장되어 있습니다. 어차피 `pm2` 를 사용 중이고, `pm2-dev` 기능으로 `nodemon` 을 대체 할 수 있다면 굳이 둘 다 설치해야하나? 라는 생각입니다. ~(어차피 파일 변경 기반 reload 만 지원 된다면...)~

다만 `pm2-dev` 가 메인 기능은 아니라서 `pm2` 에 비해 뭐든 지원이 느린 감이 있습니다만 크게 불편함은 없습니다.

아무튼 아래는 `pm2-dev` 에서 `--interpreter` 옵션으로 `.ts` 파일을 띄우는 방법입니다. `pm2` 와 `pm2-dev` 는 비슷하게 공유하는 옵션이 많아서 `pm2` 에서도 그대로 사용할 수 있습니다.

## Install pm2, ts-node

```bash
npm install pm2 --save && npm install ts-node --save-dev
```

- `pm2-dev` 는 `pm2` 패키지 내에 되어있습니다.
- 필요에 따라 `pm2` 를 global 로 설치할 수 도 있습니다.
  - 저는 사실 글로벌로 씁니다.
- [ts-node](https://www.npmjs.com/package/ts-node) 는 `.ts` 파일을 마치 `node` 로 실행하듯이 띄워주는 타입스크립트 실행 환경. 아무튼 멋진 친구입니다.

## Run pm2-dev with ts-node

```bash
pm2-dev --interpretor ./node_modules/.bin/ts-node ./src/index.ts
```

- `pm2-dev` 에 인터프리터 옵션으로 `ts-node` 를 줘서 `.ts` 파일을 받아내게 만듭니다.

## 여담

- 저도 기억안나서 찾아봤던 내용인데... 3년전에 제가 뭔가를 물어봤더군요..
  - https://github.com/Unitech/pm2/issues/3100
