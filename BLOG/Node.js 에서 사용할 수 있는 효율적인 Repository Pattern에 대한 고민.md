## 선 코드 후 코멘트

```javascript
import config from 'getconfig';
import knex from 'knex';
import mongoose from 'mongoose';
import { User, Log } from './domainObjects';
import { Log as LogSchema } from './mongodbSchemas';

class MySQL {
  constructor() {
    this.driver = knex(config.DATABASE.MYSQL);
  }
  __findByIdx(table, idx) {
    return this.driver.select().table(table).where({ idx });
  }
  __findByValue(table, params) {
    return this.driver.select().table(table).where(params);
  }
}

class MongoDB {
  constructor() {
    mongoose.connect(config.DATABASE.MONGODB);
    this.driver = mongoose.connection;
  }
  __findByIdx(model, idx) {
    return model.find({ idx });
  }
}

class Repository {
  constructor(engine) {
    this.engine = engine;
    this.connector = this.setEngine(engine);
  }
  setEngine(engine) {
    switch (engine) {
      case 'mysql': {
        return new MySQL();
        break;
      }
      case 'mongodb': {
        return new MongoDB();        
        break;
      }
      default: {
        throw new Error('Unsupported Database Engine Type');
      }
    }
    return this;
  }
  __findByIdx(target, idx) {
    return this.connector.__findByIdx(target, idx)
  }
}

class UserRepository extends Repository {
  constructor() {
    super('mysql');
    this.TABLE_NAME = 'user';
  }
  async find(idx) {
    const result = await this.__findByIdx(this.TABLE_NAME, idx)
      .catch(error => Promise.reject(new Error(String(error)))); // using Super Class Method
    return new User(result[0]);
  }
  async findByEmail(email) {
    const result = await this.connector.__findByValue(this.TABLE_NAME, { email })
      .catch(error => Promise.reject(new Error(String(error)))); // using Super Class's connector object
    return new User(result[0]);
  }
}

class LogRepository extends Repository {
  constructor() {
    super('mongodb');
    this.MODEL = mongoose.model('logs', LogSchema);
  }
  async find(idx) {
    const log = await this.__findByIdx(this.MODEL, idx);
    return new Log(log);
  }
}

const repository = {
  user: new UserRepository(),
  log: new LogRepository(),
};

const findedUser = repository.user.find(49850).then(result => result);
const findedLog = repository.log.find(19910423).then(result => result);
const finedUser2 = repository.user.findByEmail('uyu423@gmail.com').then(result => result);
```
## 나의 어그로
https://www.facebook.com/LuckyYowu/posts/1408708212520239

제 코드를 물어뜯어주세요.

- 가정1. 하나의 도메인은 두 종류 이상의 DB를 사용하지 않는다. user의 경우 mysql만 사용하고 log의 경우는 mongodb만을 사용한다.
- 가정2. 각 레포지터리는 거의 동일한 메소드를 가지고 있어서, 클라이언트가 레포지터리를 사용할 때 mongoose나 knex를 어떻게 사용하는지 몰라도 된다.
- 가정3. 레포지터리에서 find 수행 뒤 돌려받는 것은 데이터원형이 아닌 Domain Object가 된다.
- 고민1. MySQL과 MongoDB 선택자를 주입할 때 조금 더 나은 방식은 없는가? 예를 들어 class Connector 와 같은 슈퍼 클래스를 만들고 상속받을 수 있는 여지는 없는가.
- 고민2. Repository.setEngine()은 충분히 리팩토링 가능한 부분인 것 같은데, 조금 더 나은 방법을 고민해봐야겠다.
- 고민3. Repository가 super(engine)으로 Database Connector를 선택하는 방식이 과연 옳은 DI 인가? (Object가 아닌 String을 넘기는데?)
- 고민4. 코드상에는 나타나지 않았지만 MySQL과 MongoDB 클래스가 Singletone이라면 각 Repository들도 Singletone이 될수 있는가? (MySQL과 MongoDB를 싱글톤으로 만든 이유는 connection count를 유지하기 위해서)

## 나의 어그로에 대한 응답
### GW님의 코드 리뷰

DI(dependency injection)는 DIP(dependency inversion principle)의 실천이고 DIP 정의는 다음과 같습니다.

- 높은 수준의 모듈은 낮은 수준의 모듈에 의존하지 않는다. 둘 모두는 추상화에 의존한다.
- 추상화는 세부사항에 의존하지 않는다. 세부사항이 추상화에 의존한다.

링크의 코드에는 DI가 존재하지 않습니다. 따라서 DI의 옳고 그름을 판단할 수 없습니다.

DI가 없으면 무조건 나쁜 코드라는 뜻은 아닙니다.

### 나의 코멘트

만약 가정1. 특정 도메인은 특정 DB엔진만을 사용한다. 이 부분이 없고, 여러 DB엔진을 사용할 수도 있다고 가정된다면

```javascript
import { MySQL, MongoDB } from './connectors';

class UserRepository {
  constructor(Connector) {
    this.connector = new Connector();
  }
  findByIdx() {
    return this.connector.__findByIdx(...);
  }
}

new UserRepository(MongoDB);
new UserRepository(MySQL);
```

위와 같이 구현하면 DI와 낮은 결합도를 가져갈 수 있게되는 건가요?

### GW님의 추가 코멘트
MySQL과 MongoDB의 반환값이 동일한 추상화를 구현하고 UserRepository가 이 추상화에 의존해 동작한다면 의존성 주입이라 할 수 있습니다. 그런데 UserRepository가 connector(인스턴스)가 아닌 Connector(팩토리)를 주입받는 이유는 위 코드만으로는 설명되지 않네요.

그리고 모듈간 결합도가 낮은지는 높은 모듈(repository)의 변경 없이 낮은 모듈(connector)을 교체할 수 있는지로 판단하시면 됩니다.

### 나의 추가 코멘트
connector(인스턴스)가 아닌 Connector(팩토리)를 주입한 것에는 특별한 상황을 고려한 것이 아닌 제 임의로 구현한 것입니다.
저는 `new UserRepository(MySQL)`로 던진 후 `UserRepository`의 생성자에서 `this.connector = new Connector()`로 생성했지만 GW님께서 저 발언을 하신 의도는 `new UserRepository(new MySQL())` 로 MySQL 인스턴스을 주입하고 `UserRepository`의 생성자에서 `this.connector = connector` 로 받아야한다는 뜻으로 해석했습니다.
여기서의 질문은 두 방식의 차이가 있나요? 만약 후자가 더 좋은 방식이라면 특별한 이유가 있을까요?

### JM님의 코멘트
매번 인스턴스를 생성한다는 메모리, 성능상의 이슈가 있죠. 위 코드만으로는 매번 다른 인스턴스를 생성해야 하는 이유가 보이지 않기 때문에 인스턴스를 넘겨주는게 훨씬 효율적으로 보입니다.
더불어 Factory 객체를 주입할 경우, 해당 팩토리가 instance 를 생성할 때도 DI가 필요한 상황(예를 들어 dbURL, credential 등)이 있을 수 있습니다. 이럴 경우 팩토리자체를 주입해버리면 여러모로 성가시게 될것같네요.
DB I/O 에 관련된 객체라 인스턴스가 매번 만들어지면 connection 과 I/O 부분에서도 문제가 발생하겠네요.

### GW님의 추가 코멘트
저는 JM님이 설명하신 내용들이 별로 중요하다고 생각하진 않습니다. 특히 JavaScript로 구현하는 응용프로그램 논리에서는 더욱요. 자세하게 얘기하자면 논점을 벗어나고 너무 길어지기 때문에 생략하겠습니다.

Yu Yongwoo님은 다른 개체를 생성할 때에도 팩토리를 매개변수로 사용하시나요? 만약 아니라면 이유는 뭔가요? 이것에 대해 고민해보시면 좋을 듯 합니다. 참고로 다음 링크의 코드는 팩토리를 주입받는데 그 이유는 높은 모듈 인스턴스와 낮은 모듈 인스턴스의 생명주기가 다르기 때문입니다.

https://github.com/gyuwon/Khala.EventSourcing/blob/master/source/Khala.EventSourcing.Sql/EventSourcing/Sql/SqlEventStore.cs#L19

### 나의 노트
>A. 고차원의 모듈은 저차원의 모듈에 의존하면 안된다. 이 두 모듈 모두 다른 추상화된 것에 의존 해야 한다.
>
>B. 추상화 된 것은 구체적인 것에 의존하면 안 된다. 구체적인 것이 추상화된 것에 의존해야 한다.
>
>더 쉽게 말할 수도 있다. 자주 변경되는 컨크리트 클래스에 의존하지 마라. 만약 어떤 클래스의 참조를 가져야 한다면, 참조 대상이 되는 클래스를 추상 클래스로 만들어라. 만약 어떤 함수를 호출해야 한다면, 호출 되는 함수를 추상 함수로 만들어라.
>
>일반적으로, 추상 클래스와 인터페이스는 자신에게서 유도된 구체적인 클래스 보다 훨씬 덜 변한다.
>
>Java 프로그래머를 위한 UML 실전에서는 이것만 쓴다!. 로버트 C.마틴 지음 / 이용원, 정지호 옮김, 인사이트 출판사, p140, 141
>
>출처: http://vandbt.tistory.com/42 [소프트웨어 디자인- Design Software by vandbt]

- 위 링크의 예제를 보면 abstract class ButtonClient 를 사용해서 Lamp Class를 정의할 때 TurnOn()과 TurnOff()를 재정의해준다.
- class ButtonImplementation 는 Button을 상속받고, abstract method로 정의된 Button.GetState를 ButtonImplementation에서 재정의한다.
- 자 이제 이것을 나의 코드에는 어떻게 적용을 시켜야할 것인가? 이건 숙제다...

## 마무리
- Repository를 사용하는 목적은 관심사의 분리(데이터와 저장소), 테스트 용이성, 다양한 데이터 소스(ex. MySQL, MongoDB)로 인한 코드의 복잡도 하락 등 여러가지가 있을 수 있다.
- 결국에는 비즈니스 로직과 데이터 엑세스 로직을 분리하는 것이 가장 큰 궁극적인 목적이다.
- 데이터 엑세스 로직을 분리하는데는 어느정도 성공했다. 데이터 엑세스 계층은 비즈니스 로직에 거의 공통된 접근 메소드를 제공한다.
- DI는 조금 더 생각해볼 문제. 시스템 아키텍쳐 상 각 도메인은 아직 특정 데이터 소스에 종속되어 있다. 굳이 DI로 Repository Connector를 컨트롤 할 필요가 없다.
- GW님의 언급한 높은 모듈 인스턴스와 낮은 모듈 인스턴스의 생명주기가 다를 때의 차이는 제대로 이해하지 못하고 있다. 공부가 부족하다...
- 쉬운게 하나도 없다.
