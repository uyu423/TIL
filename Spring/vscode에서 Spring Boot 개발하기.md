# Visual Studio Code에서 Spring Boot 개발하기

- 최근 이직한 회사에서는 Java + Spring Boot 기술 스택으로 개발을 하게 되었다.
- 회사에서 IntelliJ 를 사주기는 하지만, 너무 복잡하다. (내가 기능을 다 쓰기는 할까..?) 나는 아직 텍스트 기반 에디터 + 터미널 질로 개발하는 것을 좋아한다.
- 그리고 집 컴퓨터에는 IntelliJ 를 쓸 수 없다. (라이센스 없음, 그렇다고 이클립스는...흠..)
- 위와 같은 사유로 vscode 로 Spring Boot 개발을 시도한다.

## Install Java Development Kit

- 당연히 JDK는 설치되어 있어야한다.
- https://www.oracle.com/kr/java/technologies/javase-jdk11-downloads.html
- Ubuntu 환경에서는 그냥 `openjdk-11-jdk-headless` 를 apt 로 설치했다.
  - `sudo apt install openjdk-11-jdk-headless`
  - 좀 찾아보니 Oracle JDK 나 Open JDK 나 큰 의미는...없나..? 있을거 같은데..?

## Install vscode Extensions

- 아래 커맨드로 관련 Extensions 한방에 설치하기

```bash
code --install-extension vscjava.vscode-java-debug
code --install-extension vscjava.vscode-java-pack
code --install-extension vscjava.vscode-java-test
code --install-extension redhat.java
code --install-extension vscjava.vscode-maven
code --install-extension vscjava.vscode-java-dependency
code --install-extension vscjava.vscode-spring-initializr
code --install-extension vscjava.vscode-spring-boot-dashboard
code --install-extension pivotal.vscode-boot-dev-pack
code --install-extension pivotal.vscode-spring-boot
```

- `pivotal.vscode-boot-dev-pack` 을 설치하면, 하위 의존 패키지로 몇가지가 같이 설치되지만 뭐.. 걍 커맨드 한방에 하는게 편하다.
- 큰 기대하지 않았는데, Editor 내에서 다양한 기능을 제공한다. main procedure 에서 Run 이나 Debug 기능이라던지..

## Create Spring Boot Project

- 명령행을 열고 (`Cmd(Ctrl)` + `Shift` + `p`) `Spring Initializer` 를 검색하면, 사용할 수 있는 기능이 몇개 나온다. IntelliJ 에서 처럼, Spring Boot Version, Maven/Grade, Java Version, Dependencies 선택해서 스프링 부트 프로젝트를 프로비저닝 할 수 있다.

## Maven Execute Commands

- 마찬가지로 명령행에서 `Maven Execute` 를 검색하면, Maven 스크립트를 실행 할 수 있다.

### F-cking Windows..

- 나의 경우는 집 개발환경이 Windows + WSL Terminal (Ubuntu) 환경인데, 이로 인해 Windows 에서 Maven Command 를 실행하면, vscode Terminal (Ubuntu) 에서 당연히 실행이 안된다. (`mvnw.cmd` 로 매핑됨)
- vscode setting 을 잘 만지면, 방법이 있을 것도 같지만, 터미널로 실행시키는게 속편하다.
  - `./mvnw spring-boot:run`
- 물론 환경이 통합되어 있는 MacOS 나 Ubutnu 에서는 이런 삽질이 없다.
