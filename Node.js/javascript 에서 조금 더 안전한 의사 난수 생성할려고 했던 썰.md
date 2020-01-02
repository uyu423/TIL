# javascript 에서 조금 더 안전한 의사 난수(랜덤 숫자) 생성할려고 했던 썰

## 발단

최근 작성한 코드에서 아래와 같은 코드 퀄리티 이슈가 발생함

> Make sure that using this pseudorandom number generator is safe here.

![sonarqube](https://user-images.githubusercontent.com/8033320/71661454-8d28f180-2d91-11ea-9ac0-823a1df63b10.png)

> As the Math.random() function relies on a weak pseudorandom number generator, this function should not be used for security-critical applications or for protecting sensitive data. In such context, a cryptographically strong pseudorandom number generator (CSPRNG) should be used instead.

대충 `Math.random()` 함수는 약한 의사 난수 생성기이고 상황에 따라 충분히 다음에 도출될 난수를 예측가능하기 때문에 때문에 보안 목적으로는 사용하면 안된다고 한다. 만약 크리티컬한 내용과 관련된 기능이라면 *Cryptographically Strong Pseudorandom Number Generator (CSPRNG)* 를 사용을 권장한다.

(물론 이번에 개발한 코드는 보안과 전혀 상관 없고 크리티컬하지 않은 코드지만 이 기회에 바꿔본다.)

제시하는 대안이 `crypto` 패키지에 내장된 `getRandomVlues`, `randomBytes` 패키지를 사용하는 것인데, 실제로 `crypto.randomBytes(1)` 을 사용해서 다음과 같이 난수를 생성할 수 있다.

```javascript
const { randomBytes } = require('crypto');
const random = parseInt(randomBytes(1).toString('hex'), 16);
```

## 하지만 쓸 수 없어...

하지만 위 방법으로는 1 byte 에 해당하는 0~255 까지의 수 밖에 생성할 수 없다. 물론 `randomBytes(2)` 로 0~65535 까지 생성할 수 있고, 인자의 숫자를 늘리면 더 큰 난수도 생성가능하지만 이 방법은 *편향된 난수* 를 발생시킬 수 있으므로 올바르지 않다고 한다.

예를 들어 `randomBytes(1)` 로 0~255 난수를 발생시키고, modular 연산으로 난수 범위로 지정했을 때 다음과 같은 문제가 발생할 수 있다.

```javascript
let randomCharacter = randomByte % 36;
```

> 0-35 stays 0-35.
> 36-71 becomes 0-35.
> 72-107 becomes 0-35.
> 108-143 becomes 0-35.
> 144-179 becomes 0-35.
> 180-215 becomes 0-35.
> 216-251 becomes 0-35.
> 252-255 becomes 0-3.
>
> If you look at the above list of ranges you'll notice that while there are 7 possible values for each randomCharacter between 4 and 35 (inclusive), there are 8 possible values for each randomCharacter between 0 and 3 (inclusive). This means that while there's a 2.64% chance of getting a value between 4 and 35 (inclusive), there's a 3.02% chance of getting a value between 0 and 3 (inclusive).
>
> (출처: https://gist.github.com/joepie91/7105003c3b26e65efcea63f3db82dfba)

요약하자면 0~255 난수가 발생했을 때 36으로 modular 연산하게 될 경우 252~255 에서는 반드시 0~3 만 도출되므로 다른 케이스에 비해 바이어스되어 도출될 확률이 높다. 원문에서는 아예 *Don't use crypto.getRandomBytes directly.* 라고 쓰여있다.

## 하지만 쓸 수 없어...2

그래서 아예 도출 숫자가 커버리면 크게 문제가 없지 않을까하여 꼼수로 다음과 같이 구현을 했었고 실제로 쓸려고 했었다.

```javascript
const random = crypto.randomBytes(8).readUInt32LE(0)
// 1317034331
```

위 값을 적당히 modular 연산하면 될 줄 알았으나 성능 이슈로 인해 이번에 문제가된 코드에는 사용하지 않기로 했다. 아래는 `Math.random()` 과 `crypto.randomByte()` 를 100,000회 루프 돌렸을 때 걸린 시간을 10 Cycle 돌린 결과 값이다.

> == Cycle 1 ==
> crypto: 518.536ms
> math: 3.901ms
> 
>  == Cycle 2 ==
> crypto: 487.265ms
> math: 3.491ms
> ...
>  == Cycle 9 ==
> crypto: 501.247ms
> math: 0.841ms
> 
>  == Cycle 10 ==
> crypto: 485.678ms
> math: 1.641ms

이번의 내가 구현한 코드의 경우 보안과는 무관했고, 호출 횟수가 많기 때문에 crypto 를 사용하지 않기로 했다. 

## 역시 무난한건 mathjs 야..

당연한 사실이지만 `mathjs` 에도 random 관련된 기능이 포함되어 있다. `mathjs.random()` 의 경우 `Math.random()` 과 동일한 동작을 보장하면서도 min, max 를 파라미터로 전달 받을 수 있는 등 조금 더 편리하다.

그리고 `mathjs.random()` 의 경우 내부에서 `seed-random` 이라는 패키지로 조금 더 안전하게 랜덤 값을 뽑아준다. 자세히는 못 뜯어봤지만 seed-random 패키지 저장소를 보면 RC4 를 사용하므로 조금 더 임의성이 보장된다.

`mathjs.random()` 은 성능도 준수해서 `Math.random()` 과 크게 차이나지 않는다.

> == Cycle 1 ==
> crypto: 485.578ms
> mathjs: 15.037ms
> math: 1.975ms
> 
>  == Cycle 2 ==
> crypto: 556.57ms
> mathjs: 6.451ms
> math: 1.994ms
> ...
>  == Cycle 9 ==
> crypto: 460.319ms
> mathjs: 19.881ms
> math: 0.883ms
> 
>  == Cycle 10 ==
> crypto: 555.885ms
> mathjs: 4.594ms
> math: 0.792ms

`mathjs` 는 이외에도 랜덤 관련된 편리한 기능들을 제공한다.

- `math.random(min, max)` 와 같이 최소/최대 값을 파라미터로 넘겨 사용할 수 있다.
- `math.randomInt(min, max)` 의 경우 0~1 사이의 소수가 아닌 바로 정수로 뽑아준다.

## 결론

아무튼 이번 이슈에 대해서는 `mathjs.random()` 을 사용해 문제를 해결했고, 앞으로 보안 요소에 대해서는 `crypto` 를 사용한 난수 생성, 이 외에는 `mathjs` 를 사용한 난수 생성을 하게 될 것 같다.

만약 내 글이 너무 똥망이라서 이해하기 힘들었다면 대충 다음과 같이 정리가 가능.

- 크리티컬한 보안 요소의 난수 생성: `crypto.randomBytes()`
- 보안이 중요하지 않고 성능이 더 중요한 난수 생성: `Math.random()`
- 그 중간 어딘가 + 편리성 + 코드 퀄리티 이슈 해소 : `mathjs.random()`
 
## 여담

- [예측 가능한 의사 난수 생성기](http://find-sec-bugs.github.io/bugs.htm#PREDICTABLE_RANDOM) 글을 살펴보면 다음과 같은 피해가 발생할 수 있다고 한다.
  - 예측 가능한 CSRF 토큰이 생성됨
  - 예측 가능한 토큰으로 비밀번호 변경 페이지 URL 이 만들어짐.
    - 대부분의 비밀번호 변경 페이지는 Query String 에 개인 식별 token 을 물고 들어가니깐.
- [Random Seeds, Coded Hints, and Quintillions](http://davidbau.com/archives/2010/01/30/random_seeds_coded_hints_and_quintillions.html)
  - seed-random 패키지 관련 글
- 가만보면 [seed-random 패키지의 저장소](https://www.npmjs.com/package/seed-random)는 정말 특이한 패키지 저장소 중에 하나다.
  - 코드 단 173줄
  - 마지막 npm 배포: 2013년
  - 2015년에 등록된 이슈에 답글이 달린 것은 2018년
  - 사실상 활동이 없는 npm 패키지고, github 저장소지만
  - 아무튼 npm 주간 다운로드 20만에 육박