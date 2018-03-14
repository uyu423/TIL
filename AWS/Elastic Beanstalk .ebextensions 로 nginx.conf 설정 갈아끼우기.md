# Elastic Beanstalk .ebextensions 로 nginx.conf 설정 갈아끼우기

- beanstalk 로 배포되는 서비스의 nginx 설정을 변경해야하는 일이 생겼다.
- 일반적인 방법은 `.ebextensions` 에 `nginx/conf.d/*` 를 생성하거나 `*.config` 파일을 생성하는 방법을 쓰면된다.
- 하지만 이번 경우에는 main `log_format` 을 변경해야겠고, 위 방식으로는 `log_format` override 가 되지 않았다.
- `.ebextensions/nginx/nginx.conf` 를 생성하면 빈스톡 배포시 nginx.conf 가 변경된다는 루머가 있어서 시도해봤더니 되지 않았고, 조금 더 확인해보니 해당 방법은 Java 와 Go 에서만 사용 가능한 방법이다.
  - https://aws.amazon.com/blogs/aws/elastic-beanstalk-update-support-for-java-and-go/ 
  - https://stackoverflow.com/questions/24860426/nginx-config-file-overwritten-during-elastic-beanstalk-deployment 
- 아쉬운대로 빈스톡에서 제공하는 Server Customize 기능을 사용해서 `nginx.conf` 를 overwrite 했다.
  - https://docs.aws.amazon.com/elasticbeanstalk/latest/dg/customize-containers-ec2.html
  ```yaml
  # .ebextensions/01_nginx_config_customize.config
  files:
  /etc/nginx/nginx.conf:
    owner: root
    group: root
    content: |
      # ... another nginx settings
      http {
          log_format  main  '{"createdTs":"$time_iso8601", '
              '"clientIp":"$remote_addr", '
              '"upstreamAddr":"$upstream_addr", '
              '"hostName":"$host", '
              '"path":"$uri", '
              '"query":"$args", '
              '"httpProtocol":"$server_protocol", '
              '"httpMethod":"$request_method", '
              '"statusCode":"$status", '
              '"pageReferrer":"$http_referer", '
              '"userAgent":"$http_user_agent", '
              '"http_x_forwarded_for":"$http_x_forwarded_for", '
              '"body_bytes_sent":"$body_bytes_sent", '
              '"upstream_response_time":"$upstream_response_time", '
              '"upstream_connect_time":"$upstream_connect_time", '
              '"upstream_status":"$upstream_status"}';

          access_log  /var/log/nginx/access.log  main;
          # ... another nginx.http settings 
      }
      # ... another nginx settings

  ```
- 해당 파일 생성 후 빈스톡 배포하니 `nginx.conf` 가 잘 교체되었다.