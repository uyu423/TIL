# Javascript 활용 사례
```js
[1, 2, 3].forEach(alert);
```
* 위 코드는 '1', '2', '3' 이라고 쓰여진 각각의 경고 팝업(alert)를 띄워준다.
* `Array#forEach`는 ECMA-262에서 제정되었으며 함수를 인자로 받고 나서 배열의 각 요새를 한 개씩 함수의 파라미터로 전달하는 기능을 수행한다.
* (만약에 `for`문을 사용해 같은 기능을 구현하려 했다면 다음과 같았겠지)
	```js
	var arr = [1, 2, 3];
	for(var i=0; i<arr.length; i++) {
		alert(arr[i]);
	}
	```
---
```js
//splat.js
function splat(fun) {
	return function(array) {
  	return fun.apply(null, array);
  };
}

var addArrayElements = splat(function(x, y) {
	return x + y;
});

console.log(addArrayElements([1, 2]));
// => 3
```
* 함수를 return 하는 것은 `클로저(closure)`다.
* `apply` 메소드는 모든 자바스크립트 함수에 제공되며, 배열 요소를 함수의 인자처럼 제공한다.
* 위 예제는 `apply`를 사용해 `splat`이라는 간단한 함수를 만든 것이다.
* `splat`는 함수를 인자로 받아 다른 함수를 리턴한다. 배열을 인자로 받으며 원래 함수(`fun`)를 apply로 호출한다.
  * 배열의 요소가 `fun`의 인자로 전달된다.
* ~~와씨 벌써부터 무슨말인지 헷갈린다~~

```js
//unsplat.js
var _ = require('underscore');

function unsplat(fun) {
  return function() {
    return fun.call(null, _.toArray(arguments));
  };
}

var joinElements = unsplat(function(array) {
  return array.join(' ');
});

console.log(joinElements(1, 2));
//=> "1 2"

console.log(joinElements('Y', 'o', 'w', 'u'));
// => "Y o w u"
```
* 위 예제는 `splat`과 반대로 작동하는 `unsplat`이다.
* 반환되는 함수는 몇몇 인자를 받으며 원래 함수(`fun`)를 주어진 배열 값으로 호출한다.
* `arguments`는 함수의 인자로 제공되는 값을 저장하는 배열과 유사한 변수(`Object`)다. 매우 편리한 친구다.
* `_.toArray`는 `Object`의 `Values`를 `Array` 형태로 포맷팅 해준다. 마치 `parseArray` 같은 느낌.
* ~~아직도 잘 모르겠다~~
---
### Javascript의 몇 가지 한계
* 자바스크립트가 결점이 많은 언어라는 것은 분명하며, 아직도 깊이 있는 토론이 진행 중이다.
* 표현의 명확성과 관련한 문제.
  * 이 문제를 해결하려고 시도하려는 것은 '웹'을 망가뜨리는 일이 될 수도 있다.
  * (저자는 `CoffeeScript`, `TypeScript`와 같은  컴파일 플랫폼을 대상으로 하는 언어가 점점 많아지는 것을 예로 들었지만 무슨 얘기인지 모르겠다.)
* 자바스크립트에서 개발자가 흔히 사용하는 [명령형 기법](https://ko.wikipedia.org/wiki/%EB%AA%85%EB%A0%B9%ED%98%95_%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D), 지역 스코핑 의존은 기본적으로 안전하지 않다.
  * 프로그램 규모가 커질 수록 골치 아파짐.
* 자바스크립트를 선택하는데 가장 큰 걸림돌 세가지
	1. 언어의 이상한 점
	2. 안전하지 않은 특성
	3. 수많은 경쟁 라이브러리
* ~~이렇게 쓰고보니 자바스크립트 쓰지 말라는 소리인 것 같다.~~
* but, 훈련과 정해진 규칙을 준수하면 자바스크립트는 안전할 뿐만 아니라 이해하고 테스트하기 쉬우며 확장의 편리성 까지 갖췄다. ~~그러니깐 앞으로 제대로 쓸 수 있게 함수형 프로그래밍을 배울거다.~~
