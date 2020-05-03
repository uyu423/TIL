# pm2-dev 로 TypeScript 프로젝트 띄우기

## Install pm2, ts-node

```bash
npm install pm2 --save && npm install ts-node --save-dev
```

- `pm2-dev` 는 `pm2` 패키지 내에 포함되어있다.

## Run pm2-dev with ts-node

```bash
pm2-dev --interpretor ./node_modules/.bin/ts-node ./src/index.ts
```

- 사실상 pm2 가 설치되어있다면 `nodemon` 은 거의 필요가 없다.
- 다만 `pm2-dev` 가 메이저 기능은 아니라서 뭐든 지원이 조금 느린 감은 있다.
- https://github.com/Unitech/pm2/issues/3100
  - ~생각안나서 찾아봤는데 3년전에 내가 이슈 띄워놓은게 있어서 놀라버렸다.~
