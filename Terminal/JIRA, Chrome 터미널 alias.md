# JIRA와 Chrome을 사용한다면 터미널에서 JIRA 이슈를 바로 띄워보자

- 사실 알프레도? 알프레드? 그 친구를 쓰면 된다는데 나는 영 맥이랑 안친해서..
- `.zshrc` or `.bashrc` 에 추가
  ```bash
  j() { open -n -a "Google Chrome" --args "--new-tab" "http://jira.yanolja.in/browse/$1" }
  jy() { open -n -a "Google Chrome" --args "--new-tab" "http://jira.yanolja.in/browse/YAJA-$1" }
  js() { open -n -a "Google Chrome" --args "--new-tab" "http://jira.yanolja.in/issues/?jql=text%20~%20\"$@\"" }
  ``` 
- example
  ```bash
  j YAJA-1234
  ```
  ```bash
  jy 1234
  ```
  ```
  js hello\ world
  ```