## 뭐가 문제였나
- 필자는 현재 HMR(가정간편식) 커머스를 다루는 모 스타트업에서 백엔드 개발자로 재직 중이다. 말이 백엔드지 최근 변화되고 있는 트렌드에 맞춰 열심히 API 작성 셔틀을 하고 있다.
- API 개발에 주로 사용하는 HTTP 상태 코드는 주로 `200 (정상)`, `400 (잘못된 요청)`, `401 (보안 토큰 에러)`, `403 (권한 없음)`, `404 (찾을 수 없음)` 정도가 있었다.
- 문제는 여기에서 발생했는데, API를 계속 개발해 나가다 보니 **API 요청 시 데이터가 없을 때 200 상태 코드에 빈 배열을 돌려주어야 하는지, 404 상태 코드를 돌려주어야 되는지 상황에 따라 다를 수 있겠다는** 생각이 들었다.
- 만약 '데이터가 없을 수도 있는 상황'과 '데이터가 없으면 안 되는 상황'에서 `404 Not Found` 에러 코드로 같게 응답할 경우 다음과 같은 애매한 상황이 펼쳐질 수 있다.
  - API를 사용하는 클라이언트가 `404` 에러에 대한 대응을 에러로 표시할지 데이터 없음으로 표시할지 상황에 따라 다르게 정의해줘야 한다. 결과적으로 클라이언트에서 API 요청에 대한 처리가 복잡해진다.
    ```javascript
    // front-end
    import fetch from 'node-fetch';

    function fetchUserList() {
      // 유저 목록을 가져오는 API를 사용한다고 가정
      return fetch('https://api.exmaple.com/users')
        .then((response) => {
          if (response.statusCode === 404) {
            // 이 404 Http 상태 코드를 에러로 처리할 것인가? 데이터 없음으로 처리할 것인가?
            // 에러일 경우 : throw new Error('Not Found');
            // 데이터 없음일 경우 : return [];
          } else if (response.statusCode === 200) {
            return response.json();
          } else {
            throw new Error('Unexpected Http Status Code');
          }
        })
        .then(result => render(successPage, result))
        .catch(error => render(failurePage, error));
    }
    ```
- 결국, 어떤 식으로 표시해야 명확하게 표현할 수 있을까 하여 페이스북 존잘 개발자님들에게 의견을 물었다. [#](https://www.facebook.com/LuckyYowu/posts/1441506412573752) 굉장히 많은 분이 의견을 주셨고 나름대로 생각을 정리할 수 있었다.
- 결론적으로는 **'데이터 없음'과 '404 Not Found'를 같은 용도로 사용하면 안 된다.**

## 그렇다면 뭘 어째야 하나
위에서 나온 결론을 조금 더 자세히 풀어보면 다음 내용이다.
- 상황에 따라 데이터가 없는 것이 정상인 상황이 있고, 데이터가 없는 것이 에러인 상황이 있다. 이를 구분 해야 한다.
  - 데이터가 없는 것이 정상일 수 있는 상황
    ```javascript
    // server-side
    API.get('/orders/date/:date', async (request, response) => {
      // 특정 날짜의 주문을 검색. 특정 날짜에 주문이 없을 수도 있다.
      const { date } = request.params;
      const orders = await Repository.Order.findByDate(date);
      // 200: OK
      // 204: No Contents
      response.statusCode(orders.length > 0 ? 200 : 204).json(orders);
    });
    ```
  - 데이터가 없는 것이 에러인 상황
    ```javascript
    API.get('/orders/:orderId', async (request, response) => {
      // 특정 ID의 주문을 검색. 데이터가 없으면 에러다.
      const { orderId } = request.params;
      const order = await Repository.Order.find(orderId);
      if (order.length > 0) {
        response.statusCode(200).json(order);
      } else {
        // 404: Not Found
        response.statusCode(404).json({
          message: `${orderId} is Not Found`
        });
      };
    });
    ```
- 그렇다면 요청한 API 리소스가 없는 경우에는 어떤 에러를 보여줘야 하는가? 일반적으로는 `404 Not Found` 가 통상적으로 사용되지만 우리는 이미 404를 다른 용도로 사용하고 있다. 다행히도 HTTP 상태 코드에는 `501 Not Implemented` 이라는 좋은 친구가 있다. 이 친구를 사용할 수 있다.
  ```javascript
  import { Users, Orders } from './Routes';

  app.route('/users', Users);
  app.route('/orders' Orders);
  app.all('*', (request, response) => {
    // 501: Not Implemented (구현되지 않음)
    response.statusCode(501).json({
      message: 'This Method is Not Implemented',
    });
  })
  ```
- 대충 이 정도면 클라이언트는 Http 상태 코드를 보고 다음 로직을 처리할 수 있을 것이다.
- 물론 일반적으로 사용되는 상태 코드들이지만 실제 개발 진행 시에는 클라이언트를 개발하는 개발자와 미리 어떤 상황에서 어떤 상태 코드를 보낼 것인지 정해야 할 것이다.

## 마무리
- API 개발 시 사용할 법 직한 응답 코드를 정리해보았다.
  - 200: OK (정상, 데이터 있음)
  - 204: No Contents (정상, 데이터 없음)
  - 301: Moved Permanently (리다이렉션)
  - 400: Bad Request (실패, 클라이언트에서 넘어온 파라미터가 이상함)
  - 401: Unauthorized (실패, 클라이언트에서 넘어온 보안 토큰이 이상함)
  - 403: Forbidden (실패, 사용자의 권한으로 리소스를 사용할 수 없음)
  - 404: Not Found (실패, 데이터가 있어야 하나 없음)
  - 410: Gone (실패, 데이터가 있었으나 삭제됨. 이건 굳이...?)
  - 500: Internal Server Error (실패, 서버 로직 문제)
  - 501: Not Implemented (실패, 없는 리소스 요청)
  - 기타 304나 502, 503 등의 상태 코드의 경우 API Application을 작성하는 개발자의 역할보다는 Server 쪽의 역할에 가깝다고 생각하여 작성하지 않음.
- 뭔가 어렵다고 느껴진다면 다음 짤을 참고해서 쉽게 이해할 수 있다.
  ![image](https://user-images.githubusercontent.com/8033320/27012495-86ce1ade-4f0b-11e7-8618-08a4716f65f1.png)
