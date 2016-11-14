# Airbnb Database를 Reversing 해보자

## 현재 까지의 문제점.
  Issue #3 : [DB의 부담을 덜어주자](https://github.com/uyu423/Programming-Practice/issues/3)

## 관계도 (미완성)
- 0.0.1 : initial
![image](https://cloud.githubusercontent.com/assets/8033320/18083204/1fdccbea-6edd-11e6-9d08-95bb5a1d2f4f.png)
- 0.0.2
![image](https://cloud.githubusercontent.com/assets/8033320/18138894/dfacfea6-6fe9-11e6-9709-1a9ff6c75fdc.png)

## 요구사항
일반적인(https://www.airbnb.com/s/seoul) 숙박 예약 시스템을 만드려고 합니다.
현재 방정보는 만들어져 있으며 금액과 관련된 내용을 개발해야 합니다.

- 기본 금액 정책
  - 주중금액
    - 일-목
  - 주말금액
    - 금-토
  - 준성수기금액
    - 기간
    - 방마다 기간이 다름
  - 성수기금액
    - 기간
    - 방마다 기간이 다름
  - 특별가
    - 특정 날짜별로 커스터마이징
- 옵션 금액 정책
  - 추가인원에 따른 추가금액
- API
  - 조건에 맞는 방리스트 검색
    - 체크인 날짜
    - 체크아웃 날짜
    - 최소금액
    - 최대금액
    - 게스트 수
- 그외 확장성
  - 지금 설계 하지는 않지만 확장성 고려
  - VIP 회원 우대 기능
  - 특정 방 전체 일정 일괄 할인 기능
  - 그외 예약시스템을 고려한 확장

## Using Tool
 - Development Server : [MariaDB](https://mariadb.org/) 10.0.25
 - Designer : [eXERD](http://ko.exerd.com/)
 - DB Tool : [phpMyAdmin](https://www.phpmyadmin.net/), [HeidiSQL](http://www.heidisql.com/)
