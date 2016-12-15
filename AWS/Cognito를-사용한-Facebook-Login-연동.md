# AWS Cognito를 사용한 Facebook Login 연동
- [AWS Cognito](https://aws.amazon.com/ko/cognito/)는 Facebook이나 Twitter와 같은 소셜 로그인 기능을 추상화하여 통합적으로 쉽게 관리해주는 서비스다.
  - npm에 있는 passport와 비슷한 친구다.
- Facebook Login은 [Facebook Developer](https://developers.facebook.com/)에서 App을 생성한 뒤 사용하여 Facebok Login 앱을 사용 설정하면 사용할 수 있다.

# AWS Cognito 설정
- 간단하게 인증 Pool만 관리해주는 Federated Indentities를 사용한다.
- Create New Identity Pool로 새로운 Identity Pool을 생성할 수 있고, Authentication providers에서 페이스북이나 트위터 같은 서트파티 OAuth의 ID 값을 추가할 수 있다.
  - 현재 사용가능한 서트파티 인증 제공자(Authentication providers) 목록
    - Cognito 자체 (User Pool 사용?)
    - Amazon
    - Facebook
    - Google+
    - Twitter/Digits (Digits?)
    - OpenID
    - SAML
    - Custom (기타?)
- 기본적으로 서드파티 인증 성공 후 다음 코드를 실행시켜 주면 된다. 예시는 Javascript 지만 Swift, Java, Xamarin 등 다양하게 있다.
  ```javascript
  AWS.config.region = 'ap-northeast-1' // Region;
  AWS.config.credentials = new AWS.CognitoIdentityCredentials({
    IdentityPoolId: 'YOUR_AWS_COGNITO_IDENTITY_POOL_ID',
    Logins: {
      'graph.facebook.com': response.authResponse.accessToken
    }
  });
  ```
  - `YOUR_AWS_COGNITO_IDENTITY_POOL_ID`는 Identity Pool 생성 후 Sample Code 메뉴에서 확인 할 수 있다.

# Facebook App 설정
- Facebook Developer에서 App 생성은 생략한다.
- App 생성 후 App Id를 어딘가에 잘 기록해둔다.
- 앱 기본 설정에서 앱 도메인과 사이트 URL을 설정한다.
  - 앱 도메인은 `file://`로 시작하는 것은 안되는 것 같다. 간단한 웹서버라도 띄워서 `http://`를 사용하자.  
- 제품 추가에서 Facebook Login을 선택하여 추가한다. 이 때 유효한 OAuth 리디렉션 URI에 리디렉션할 URI를 설정해준다. (ex. http://localhost/cognito)
  - 이 것이 설정되어 있지 않으면 로그인 시 리디렉션 Exception이 발생한다.
  ![image](https://cloud.githubusercontent.com/assets/8033320/21236332/f9742a88-c33d-11e6-91b7-ff488a82731f.png)
- Facebook Developer Guide에도 나와있지만 최하단의 Sample 코드처럼 작성하면 아래와 같은 샘플 로그인 페이지가 나타난다.
  ![image](https://cloud.githubusercontent.com/assets/8033320/21236759/a745dbe2-c33f-11e6-9f4c-310ed0f83ff3.png)


# 마무리
- 설정을 모두 마치고 아래에 있는 Sample HTML Code처럼 `aws-sdk`와 `facebook-sdk`가 Load된 상태에서 로그인을 시도 후 성공하면 샘플 페이지에서 아래와 같이 상태가 변경되고 Cognito Token 값이 리턴된다.
![image](https://cloud.githubusercontent.com/assets/8033320/21236715/89686d4c-c33f-11e6-84e2-2554e3810f43.png)
  ```json
  {
    "Credentials":{
      "AccessKeyId":"ASIA...",
      "Expiration":1481829283,
      "SecretKey":"V+2AWc...",
      "SessionToken":"AgoGb3JpZ..."
      },
    "IdentityId":"YOUR_AWS_COGNITO_IDENTITY_POOL_ID"
  }
  ```
  - `Credentials`로 넘어온 모든 값들을 DB에 저장해 놓고, 인증이 필요할 때마다 사용하면 될 듯하다.
  - `Expiration`은 누가봐도 UNIX TIME 포맷이다.. moment 같은 곳에 넣고 돌려서 re-formating 해주면 될 듯하다.
- AWS Console의 Cognito에서 GUI로 Dashboard를 확인 할 수 있다.
  ![image](https://cloud.githubusercontent.com/assets/8033320/21236851/f060df70-c33f-11e6-878e-13f9d5d5badf.png)
- 앞으로 확인해볼 것은 `aws-sdk`의 `CognitoSyncManager`를 사용해서 dataset에 key와 value를 집어넣어서 사용하는 것과 카카오톡 SDK 사용가능 여부. 그리고 실제 환경에서의 인증 테스트 정도다. 하.. 아직도 할게 많네 ㅜㅜ

## Sample HTML Code
- Cognito와 Facebook App 설정만 잘 되었다면 아래 코드에서 Cognito ID와 Facebook App ID만 바꾼다면 잘 될 것으로 추정한다..!
  ```html
  <!DOCTYPE html>
  <html>
  <head>
  <title>Facebook Login JavaScript Example</title>
  <meta charset="UTF-8">
  <script src="https://cdnjs.cloudflare.com/ajax/libs/aws-sdk/2.7.14/aws-sdk.min.js"></script>
  </head>
  <body>
  <script>
    // This is called with the results from from FB.getLoginStatus().
    function statusChangeCallback(response) {
      console.log('statusChangeCallback');
      console.log(response);
      // The response object is returned with a status field that lets the
      // app know the current login status of the person.
      // Full docs on the response object can be found in the documentation
      // for FB.getLoginStatus().
      if (response.status === 'connected') {
        // Logged into your app and Facebook.
        testAPI(response);
      } else if (response.status === 'not_authorized') {
        // The person is logged into Facebook, but not your app.
        document.getElementById('status').innerHTML = 'Please log ' +
          'into this app.';
      } else {
        // The person is not logged into Facebook, so we're not sure if
        // they are logged into this app or not.
        document.getElementById('status').innerHTML = 'Please log ' +
          'into Facebook.';
      }
    }

    // This function is called when someone finishes with the Login
    // Button.  See the onlogin handler attached to it in the sample
    // code below.
    function checkLoginState() {
      FB.getLoginStatus(function(response) {
        statusChangeCallback(response);
      });
    }

    window.fbAsyncInit = function() {
    FB.init({
      appId      : 'YOUR_FACEBOOK_APP_ID',
      cookie     : true,  // enable cookies to allow the server to access
                          // the session
      xfbml      : true,  // parse social plugins on this page
      version    : 'v2.8' // use graph api version 2.8
    });

    // Now that we've initialized the JavaScript SDK, we call
    // FB.getLoginStatus().  This function gets the state of the
    // person visiting this page and can return one of three states to
    // the callback you provide.  They can be:
    //
    // 1. Logged into your app ('connected')
    // 2. Logged into Facebook, but not your app ('not_authorized')
    // 3. Not logged into Facebook and can't tell if they are logged into
    //    your app or not.
    //
    // These three cases are handled in the callback function.

    FB.getLoginStatus(function(response) {
      statusChangeCallback(response);
    });

    };

    // Load the SDK asynchronously
    (function(d, s, id) {
      var js, fjs = d.getElementsByTagName(s)[0];
      if (d.getElementById(id)) return;
      js = d.createElement(s); js.id = id;
      js.src = "http://connect.facebook.net/en_US/sdk.js";
      fjs.parentNode.insertBefore(js, fjs);
    }(document, 'script', 'facebook-jssdk'));

    // Here we run a very simple test of the Graph API after login is
    // successful.  See statusChangeCallback() for when this call is made.
    function testAPI(response) {
      console.log('Welcome!  Fetching your information.... ');
    	AWS.config.region = 'ap-northeast-1';
    	AWS.config.credentials = new AWS.CognitoIdentityCredentials({
    		IdentityPoolId: 'YOUR_AWS_COGNITO_IDENTITY_POOL_ID',
    		Logins: {
    			'graph.facebook.com': response.authResponse.accessToken
    		}
    	});

  	// Obtain AWS credentials
  	AWS.config.credentials.get(function(){
  		// Access AWS resources here.
  	});
      FB.api('/me', function(response) {
        console.log('Successful login for: ' + response.name);
        document.getElementById('status').innerHTML =
          'Thanks for logging in, ' + response.name + '!';
      });
    }
  </script>

  <!--
    Below we include the Login Button social plugin. This button uses
    the JavaScript SDK to present a graphical Login button that triggers
    the FB.login() function when clicked.
  -->

  <fb:login-button scope="public_profile,email" onlogin="checkLoginState();">
  </fb:login-button>

  <div id="status">
  </div>

  </body>
  </html>
  ```
