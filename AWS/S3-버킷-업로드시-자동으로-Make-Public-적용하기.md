# AWS S3 버킷 업로드시 자동으로 'Make Public'을 적용해보자

## 이 TIL을 왜 쓰게 되었나?
- 현재 Static Web Hosting (React.js), CDN Origin 등으로 `AWS S3`를 사용하고 있다.
- 아직은 따로 S3 배포 툴을 사용하고 있지 않고, `AWS Console`에 접속해 수동으로 업로드를 해주고 있다.
- `S3` 버킷에 업로드된 `Object`를 외부에 공개하기 위해서는 `Make Public` 옵션을 적용해줘야한다.
- 그런데 업로드 하는 사용자가 한 번씩 `Make Public` 적용을 까먹어서, 막상 해당 리소스로 접근을 하면 `404`나 `403`이 뜬다.
- 그래! 이젠 업로드하면 무조건 `Make Public`을 시키는거야..!

## 그래서 내가 뭘 어떻게 하면 되나?
- 기본적으로는 다음과 같은 버킷 정책(`Bucket Policy`)를 `Auto Make Public` 적용하려는 버킷에 설정해주면 된다.
```json
{
	"Version": "2012-10-17",
	"Id": "Policy***********",
	"Statement": [
		{
			"Sid": "Stmt***********",
			"Effect": "Allow",
			"Principal": "*",
			"Action": "s3:GetObject",
			"Resource": "arn:aws:s3:::<bucket_name>/<key_name>"
		}
	]
}
```

### AWS Policy Generator를 사용한 정책 생성
- 우리의 갓 `AWS`님께서는 자비롭게도 `AWS Policy Generator`를 제공해주신다..!!
![image](https://cloud.githubusercontent.com/assets/8033320/20576523/a377f422-b201-11e6-9ebc-cd18d99c5272.png)
- `Bucket Properties`항목에서 `Edit bucket policy`를 선택하면 아래와 같은 정책 편집기가 나타난다. 우리는 이곳에 위와 같은 형태의 필요한 JSON Policy를 적용해주면 된다.
![image](https://cloud.githubusercontent.com/assets/8033320/20576595/d97fc66c-b201-11e6-9124-dd509f301013.png)
- 왼쪽 하단에에 있는 `AWS Policy Generator`를 사용해보자.  
![image](https://cloud.githubusercontent.com/assets/8033320/20576727/718f7218-b202-11e6-845d-a50292c5cbad.png)
- 대충 다음과 같은 항목들을 설정해주면 된다.
  - **Select Type of Policy** : S3 Bucket Policy
  - **Effect** : Allow
  - **Principal** : *
  - **AWS Service** : Amazon S3
    - 이건 Select Type Of Policy에 따라 자동으로 선택된다.
  - **Actions** : getObject를 선택해주자.
  - **Amazon Resource Name (ARN)** : 이건 조금 귀찮을 수 있는데 다음과 같은 포맷에 맞춰 입력하면 된다.
    - `arn:aws:s3:::<bucket_name>/<key_name>`
    - 예제 : `arn:aws:s3:::cloud.luckyyowu.co.kr/*`
- 필요한 항목을 설정하고 `Add Statement`를 선택하면 다음과 같이 첫번째 정책이 추가된다. 여러개의 정책을 추가할 수도 있다.
![image](https://cloud.githubusercontent.com/assets/8033320/20576866/0e748d70-b203-11e6-990d-37bd3ed99446.png)
- 최종적으로 `Generate Policy`를 선택하면 아래와 같이 JSON 형태의 `Policy`을 만들어 준다.
![image](https://cloud.githubusercontent.com/assets/8033320/20576914/3489d380-b203-11e6-82b5-5cdc63b713f0.png)


### Bucket에 정책을 설정해보자
- 이제 모든 것이 끝났다. 위에서 나는 다음과 같은 JSON을 획득했으며, 이것을 `Edit bucket policy`에 복사-붙여넣기 한 후 적용시키면 된다.
```json
{
  "Id": "Policy1479931362989",
  "Version": "2012-10-17",
  "Statement": [
    {
      "Sid": "Stmt1479931227473",
      "Action": [
        "s3:GetObject"
      ],
      "Effect": "Allow",
      "Resource": "arn:aws:s3:::cloud.luckyyowu.co.kr/*",
      "Principal": "*"
    }
  ]
}
```
![image](https://cloud.githubusercontent.com/assets/8033320/20577103/23b8784e-b204-11e6-9ae2-953fb2eff7a0.png)
- 이제 업로드 후 귀찮게 `Make Public`해 줄 필요가 없어진다. 야호

## 참고 도서
- 아마존 웹 서비스를 다루는 기술 (길벗/이재홍, 초판 2쇄, 2015)
