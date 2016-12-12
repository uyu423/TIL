# AWS CodeBuild 간단 사용기
- [AWS re:invent 2016](https://aws.amazon.com/ko/blogs/korea/2016-12-aws-webinars-for-developers/?adbsc=social_20161205_68501326&adbid=1803719293218097&adbpl=fb&adbpr=1563378127252216)에서 소개된 새로운 서비스 가운데 내 눈길을 끌었던 것 하나는 [AWS CodeBuild](https://aws.amazon.com/ko/codebuild/) 였습니다. CodeBuild는 기존의 Jenkins CI나 Travis CI를 대체할 수 있지 않을까? 라고 기대하고 있는 서비스 입니다.
- 개인적으로 CI 툴을 포함한 배포 자동화에 굉장히 약한 편입니다. (그냥 서버 들어가서 작업하는게 편해..) 그래서 이번 CodeBuild에 관심을 관심을 더 가졌고, 간단하게 나마 사용해봤습니다.
- CodeBuild는 현재 Virginia, Oregon, Ireland 에서만 사용할 수 있습니다.
- 비용은 Build에 걸리는 Computing Time이라고 합니다.

## 쓱 한번 해볼까?
- codeBuild에서 create project를 하면 아래와 같은 화면이 나타납니다.
   ![image](https://cloud.githubusercontent.com/assets/8033320/21104006/25d31bf2-c0c8-11e6-9c43-2ebea2c8e006.png)
  - Project name : CodeBuild에 나타나는 프로젝트 명입니다.
  - Source provider : 소스코드 제공자에 대한 정보를 선택합니다. 현재 AWS S3, CodeCommit, **Github(!!)** 를 선택할 수 있습니다. 저는 Github를 선택했습니다.
   - Repository : Source provider 선택에 따라 다른 선택상자가 나타납니다. Github를 선택할 경우 이 항목이 나타나며 Github와 OAuth를 통해 Repository 목록을 불러옵니다.
  - Enviorment Image : 뭔지는 잘 모르겠지만 Docker를 사용하지는 않았으니 기본 값을 선택했습니다.
  - Operating system : 운영체제를 선택할 수 있습니다. 현재는 Ubuntu 밖에 지원하지 않는 듯합니다.
  - Runtime : 개발 언어 환경을 설정합니다. 현재 Android, Java, Python, Ruby, Golang, Node.js, Docker를 지원합니다. 저는 Node.js를 선택했습니다.
  - Version : Runtime에서 선택한 언어 환경의 버전을 선택할 수 있습니다. 저는 node.js 6.3.1을 선택했습니다.
  - Build specifcation : 빌드에 필요한 설정 파일을 `buildspec.yml`로 제공할 것이냐, 그냥 command로 입력할 것이냐를 선택할 수 있습니다. 저는 yml 파일을 작성할 것이므로 기본 값을 사용합니다.
  - Artifacts type : 뭔지 모르겠으나, No artifacts와 S3 중 선택할 수 있습니다. 빌드의 산출물을 어디에 저장할 것인지 물어보는게 아닌가 싶습니다.
  - Service Role : 빌드에 필요한 Role을 설정합니다. 미리 만들어둔 role이 없으니 기본 값으로 두고 알아서 생성하게 했습니다.

![image](https://cloud.githubusercontent.com/assets/8033320/21104366/9c87feba-c0c9-11e6-9fef-28745c224eb8.png)
- 뭔가 프로젝트가 생성되었습니다. 하지만 git에 `buildspec.yml`을 만들어두지 않았으니 Start build는 이따가 눌러보겠습니다.
- 해당 프로젝트에 아래와 같은 yml 파일을 생성했습니다.

  ```yml
  version: 0.1

  phases:
    install:
      commands:
        - echo Insatlling NPM Packages and wget Enviorment File
        - npm install
        - npm install babel-cli cross-env --global
    pre_build:
      commands:
        - echo Nothing to do in the pre_build phase...
    build:
      commands:
        - echo Build started on `date`
        - npm run build
    post_build:
      commands:
        - echo Nothing to do in the post_build phase...
  artifacts:
    discard-paths: yes
  ```
  - 크게 `install`과 `pre_build`, `build`, `post_build`로 나눌 수 있을 것 같습니다.
    - `install` : 빌드를 위해 필요한 패키지를 설치하는 명령어들이 좋을 것 같습니다. Node.js의 경우 `npm install` 같은 명령어가 있겠네요.
    - `pre_build` : 빌드 전 해야하는 명령어가 좋을 것 같습니다. 예를 들어 Mocha나 Jest를 사용한 `npm run test`?
    - `build` : 실제 빌드에 사용되는 명령어가 좋을 것 같습니다. 저는 `npm run build`를 사용했고, 이 명령어는는 `babel server --out-dir build --presets=es2015 && webpack` 로 매핑되어 있었습니다.
    - `post_build` : 빌드가 끝난 뒤 해야할 행동을 기술하면 좋을 것 같습니다. 구체적으로 사용해보지는 않았지만 주로 deploy와 관련된 명령어가 아닐까 싶습니다.
    - 좀 더 상세한 스펙은 AWS CodeBuild 문서의 [Build Spec Reference](http://docs.aws.amazon.com/codebuild/latest/userguide/build-spec-ref.html)를 참고하면 됩니다.
- 해당 파일을 Git에 집어넣고 Start Build를 하면 아래와 같은 Confirm 화면이 나오고 여기서 Start Build를 한번 더 하면..!
![image](https://cloud.githubusercontent.com/assets/8033320/21104545/4994ad2e-c0ca-11e6-9aff-9b222cac1926.png)
- 아래와 같이 phase 별로 Build를 돌리고 Success/Failed를 확인할 수 있습니다. 저 같은 경우는 프로젝트 설정파일인 `.env`가 빠져있어서 에러가 났습니다.
![image](https://cloud.githubusercontent.com/assets/8033320/21104972/e9ac8b96-c0cb-11e6-9ee2-424ee693d6f7.png)
- Build History에서 빌드 결과를 모아서 확인할 수도 있습니다.
![image](https://cloud.githubusercontent.com/assets/8033320/21105550/f8fdb1c2-c0cd-11e6-8200-c003fcb8bd40.png)

## 마무리
- Jenkins와 같이 Github `master` Branch Push시 codeBuild를 돌릴 수 있는 지는 확인해보지 못 했습니다만 가능할 경우에는..?! 우오왕..! 앞으로 확인해봐야할 내용입니다.
- 마찬가지로 `post_build` phase에서 [AWS Elastic Beanstalk](https://aws.amazon.com/ko/documentation/elastic-beanstalk/)으로 deploy가 가능한지도 확인해봐야 할 내용입니다.
- 저 같이 배포 자동화가 더 어렵게 느껴지는 개발자 분들이 있다면 화이팅입니다..ㅜㅜ
