# Dependency Injection whth Node.js

## 왜 Node.js에서 Dependency Injection을 찾으셈?
- Express.js로 API Server를 구성해야하는 작업을 진행 중이다. 기존에 내가 하던 방식은 Dependency가 너무 심했다.
- 나는 전형적인 Controller-Model 방식으로 API Server를 구성하는 것을 선호하는데, 대부분 1 Controller, 1 Model 방식이다. 그러다 보니 Controller에서 Model을 사용하기 위해 Model의 내부 로직을 알아야하는 상황이었다.
- 주로 MySQL을 사용했다. 그래도 DB Connection 부분은 한번 추상화를 거쳐 Model에서 쿼리만 날리면 작동했지만 만약에 DBMS가 바뀌면? NoSQL을 쓰게 된다면? 모든 것을 다시 만들어야하는 상황이 온다.
  - SQL Building 역시 Model에서 이루어졌다.

## 나는 너무 컴맹이야
- 지금까지 Dependency Injection을 잘못이해하고 있었다. Dependency Injection을 처음 접한 것은 스쳐 지나가듯이 사용해본 Spring 프레임워크 덕분이었는데, 간단하게 사용만 했던 터라 해당 개념을 자세히 익히지 못했다.
- 나는 Dependency Injection을 단순히 객체간의 의존성을 낮추기 위해 마치 Redux 처럼 Pool Container 같은 친구를 구성하는 것이라 알고 있었다.
  - 아마 나는 이 것을 어떤 Spring 동영상 강의에서 처음 접했는데, 동영상 강의가 이상한 것이었는지, 내가 잘 못 이해한 것인지.. 물론 후자일 가능성이 훨씬 크다.
- 지금 관련 문서를 보고 있지만 확실한 것은 Object간의 Dependency를 줄이는 것은 맞지만 그 방법이 Object Pool Container를 구성하는 것은 아니라는 것이다.

## Dependency Injection은?
- http://greatkim91.tistory.com/41
- https://blog.risingstack.com/dependency-injection-in-node-js/

## Express에서 좀 더 유연한 설계는 어떻게 해야될까.
- 그걸 모르니깐 이걸 쓰고 있다. 이 부분을 고민해보자
  - Controller를 작성할 때 Model을 주입할까? 그럼 Controller를 Class로 작성하고 `constructor()`에 Model Option을 주입해야하는데 과연 올바른 것인가? 모델을 여러개 사용해야할 경우에는? 하나의 Object로 묶어야하나?

  ```javascript
  // 대충 짜보는 코드 1
  // route.js
  import mysqlModels from 'model/MySQL';
  import mongodbModels from 'model/MongoDB';
  import { Menu } from 'controllers';

  app.get('/menu/:idx', (req, res) => new Menu(mysqlModels).getMenuByIdx(req, res));
  app.get('/menu', (req, res) => new Menu(mysqlModels).getMenuAll(req, res));
  ```

  ```javascript
  // 대충 짜보는 코드 2
  // controllers/Menu.js
  export default class Menu extends Controller {
    constructor(model) {
      this.model = model;
    };

    getMenuAll(req, res) {
      this.model.menu.getMenuAll((err, result) => {
        if(err) throw new Error(err);
        else res.json(result);        
      })
    };

    getMenuByIdx(req, res) {
      this.model.menu.getMenuByIdx({req.prams.idx}, (err, result) => {
        if(err) throw new Error(err);
        else res.json(result);
      })
    };
  }
  ```

  - Model을 작성할 때 실제 DB 타입과 Query에 관한 Option을 주입해야할까? 이것이 좀 더 효과적일 수도 있겠다. 나의 방식에서 Model은 정말 DB Connection과 Query Building만 하는데 이렇게 되면 Model이 하게되는 일 자체가 없어지지 않을까? 그냥 Interface처럼 추상화 객체로 가는건가? 근데 난 JAVA 고자라 Interface를 잘 모르잖아? Interface가 추상화 객체는 맞는건가? 만약 이렇게 한다고 했을때 Model에서 `getMenuByIdx`를 호출하고 또다시 DI된 객체에서 `getMenuByIdx`를 호출해야하는 것인가?

  ```javascript
  // 대충 짜보는 코드 3
  // route.js
  import mysqlAndQuerys from 'config/mysql';
  import mongodbAndQuerys from 'config/mongodb';
  import { Menu } from 'models';

  app.get('/menu/:idx', (req, res) => {
    new Menu(mysqlAndQuerys).getMenuByIdx(req.params.idx, (err, result) => {
      if(err) res.send(String(err), 500);
      else res.json(result);
    })
  })
  ```

  ```javascript
  // 대충 짜보는 코드 4
  // models/Menu.js
  export default class Menu extends Model {
    constructor(executor) {
      this.executer = executor;
    }
    getMenuByIdx(idx, callback) {
      this.executer.getMenuByIdx(idx, (err, res) => {
        callback(err, res);
      })
    }
  }
  ```
- 조금 더 고민해보자.
