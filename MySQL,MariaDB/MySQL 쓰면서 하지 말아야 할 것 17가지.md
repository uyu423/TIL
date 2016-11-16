# MySQL 쓰면서 하지 말아야 할 것 17가지

권장사항이다. 이것을 이해하면 당신의 어플리케이션이 더 나은 성능을 발휘할 것이다.

다만 이것이 사람의 실력을 판단하는 척도로 사용되서는 안 될 것이다.

Original Post : https://blog.lael.be/post/370

## 작게 생각하기
- 조만간 규모가 커질거라면 MySQL ecosystem을 봐야된다.
- 그리고 캐싱 빡시게 안 하는 메이저 웹사이트는 없다.
- develooper.com의 Hansen PT랑 Ilia 튜토리얼 볼 것
- 처음부터 확장 가능하게 아키텍처 잘 쪼개놔야된다.
- 복제랑 파티셔닝 어떻게 할지 미리 계획 세워놔라.
- 파일 기반 세션 좀 쓰지마
- 그렇다고 너무 쓸데없이 크게 생각하지도 말 것
- 특히 성능하고 확장성 구분 못 하면 난감함

## EXPLAIN 안 써보기
- SELECT 앞에 EXPLAIN 이라고 붙이기만 하면 되는 것을 (..)
- 실행 계획 확인
- 타입 컬럼에 index 써있는거랑 Extra 컬럼에 index 써있는거랑 “매우 큰” 차이 있음
- 타입에 있으면 Full 인덱스 스캔 (안 좋다.)
- Extra 컬럼에 있으면 Covering 인덱스 찾았다는 의미임 (좋다!)
- 5.0 이후부터는 index_merge 최적화도 한다.

## 잘못된 데이터 타입 선택
- 한 메모리 블럭 단위에 인덱스 레코드가 많이 들어갈수록 쿼리가 빨리 실행될 것이다. (중요)
- 아.. 정규화 좀 해… (이거 정말 충격과 공포인 듯)
- 가장 작은 데이터 타입을 써.. (진짜 BIGINT가 필요하냐고..)
- 인덱스 걸리는 필드는 정말 최소한으로 데이터 크기를 써야된다고.
- IP는 INT UNSIGNED로 저장해!! (아주 공감)
- 이럴 때 쓰라고 INET_ATON 함수가 아예 내장되어 있음.

## PHP에서 pconnect 쓰는 짓
- 아파치에서 좀비 프로세스라도 생기면 그 커넥션은 그냥 증발하는거야..
- 어차피 MySQL 접속 속도는 Oracle이나 PostgreSQL 보다 10~100배 빠르다고.

## 너무 과도한 DB 추상화 계층을 두는 것
- 어디 포팅 열심히 할 거 아니면 추상화 계층 쓰지마 (ADODB, MDB2, PearDB 등)
- scale out 가능한걸 쓰라고.

## 스토리지 엔진 이해 못 하는 것
- 단일 엔진만으로 전체 아키텍처를 결정했다면 대부분 최적이 아님
- 엔진 별 장단점을 공부할 것
- ARCHIVE : zlib으로 압축해주고 UPDATE 안 되고 로그 Bulk Insert에 유용함.
- MEMORY : 서버 재시작하면 증발. 인덱스가 HASH나 BTREE로 가능함. 임시, 요약 데이터에 사용.
* 주간 top X 테이블 같은 것.
* 하여튼 메모리에 박아넣고 싶은 데이터 있으면..

## 인덱스 레이아웃 이해 못 하는 것
- 제대로 인덱스랑 스토리지 엔진 선택하려면 공부 좀 해
- 엔진은 데이터와 인덱스 레코드를 메모리나 디스크에 레이아웃하는 걸 구현한 것
- clustered 구성은 데이터를 PK 순서에 따라 저장함.
- non-clustered 구성은 인덱스만 순서대로 저장하고 데이터는 순서 가정하지 않음.
- clustered에서는 인덱스만 타면 추가적인 조회 없이 바로 데이터 가져오는 것임.
- 그래서 clustered PK는 작은 놈으로 할 필요가 있다는거
* 다른 인덱스는 각 레코드마다 PK를 앞에 더 붙이게 되니까.
* PK 지정 안 하면 아무렇게나 해버림

## 쿼리 캐시 이해 못 하는 것
- 어플리케이션 read/write 비율은 알고 있어야지
- 쿼리 캐시 설계는 CPU 사용과 읽기 성능 간의 타협
- 쿼리 캐시 크기를 늘린다고 읽기 성능이 좋아지는게 아님. heavy read라도 마찬가지.
- 과도한 CPU 사용을 막기 위해 무효화 할 때는 캐시 항목들을 뭉텅이로 날려버림
- 한마디로 SELECT가 참조하는 테이블 데이터 하나라도 변경되면 그 테이블 캐시는 다 날라간다는 얘기임
- 수직 테이블 파티셔닝으로 처방
* Product와 ProductCount를 쪼갠다든지..
* 자주 변하는 것과 변하지 않는 것을 쪼개는게 중요하다 이 말임.

## Stored Procedure를 쓰는 것
- 무조건 쓰면 안 된다는게 아니고..
- 컴파일 할 때 무슨 일이 일어나는지 이해 못 하고 쓰면 재앙이 된다 이 말.
- 다른 RDBMS랑 다르게 connection thread에서 실행 계획이 세워짐.
- 이게 뭔 얘기냐 하면 데이터 한 번 가져오고 연결 끊으면 그냥 CPU 낭비 (7~8% 정도)하는 꼴이라는 것.
- 웬만하면 Prepared 구문과 Dynamic SQL을 써라.. 아래 경우를 제외하고
* ETL 타입 프로시저
* 아주아주 복잡하지만 자주 실행되지는 않는 것
* 한 번 요청할 때마다 여러번 실행되는 간단한 것 (연결한 상태로 여러번 써야 된다니까)

## 인덱스 컬럼에 함수 쓰는 것
- 함수에 인덱스 컬럼 넣어 호출하면 당연히 인덱스 못 탄다
- 함수를 먼저 계산해서 상수로 만든 다음에 = 로 연결해야 인덱스 탈 수 있다.
* 여기 실행 계획 보면 LIKE도 range type 인덱스 타는 것 보임

## 인덱스 빼먹거나 쓸모없는 인덱스 만들어 놓는 것
- 인덱스 분포도(selectivity)가 허접하면 안 쓴다.
- S = d/n
* d = 서로 다른 값의 수 (# of distinct values)
* n = 테이블의 전체 레코드 수
- 쓸모없는 인덱스는 INSERT/UPDATE/DELETE를 느리게 할 뿐..
- FK는 무조건 인덱스 걸어라. (물론 FK 제약 걸면 인덱스 자동으로 생긴다.)
- WHERE나 GROUP BY 표현식에서 쓰이는 컬럼은 인덱스 추가를 고려할 것
- covering index 사용을 고려할 것
- 인덱스 컬럼 순서에 유의할 것!

## join 안 쓰는 짓
- 서브쿼리는 join으로 재작성해라
- 커서 제거해라
- 좋은 Mysql 성능을 내려면 기본
- 집합 기반으로 생각해야지 루프 돌리는거 생각하면 안 된다.

## Deep Scan 고려하지 않는 것
- 검색엔진 크러울러가 쓸고 지나갈 수 있다.
- 이 경우 계속해서 전체 집합을 정렬한 다음 LIMIT로 가져와야 하니 무진장 느려진다.
- 어떻게든 집합을 작게 줄인 다음 거기서 LIMIT 걸어 가져올 것

## InnoDB 테이블에서 WHERE 조건절 없이 `SELECT COUNT(*)` 하는 짓
- InnoDB 테이블에서는 조건절 없이 `COUNT(*)` 하는게 느리다.
- 각 레코드의 transaction isolation을 유지하는 MVCC 구현이 복잡해서 그렇다는..
- 트리거 걸어서 메모리 스토리지 엔진 쓰는 테이블에 통계를 별도로 유지하면 된다.

## 프로파일링이나 벤치마킹 안 하는 것
- 프로파일링 : 병목 찾아내기
- 벤치마킹 : 시간에 따른 성능 변화 추이 평가, 부하 견딜 수 있는지 테스트
- 프로파일링 할 때는 실제 데이터를 옮겨와서 할 것
- 어디가 병목이냐~ Memory? Disk I/O? CPU? Network I/O? OS?
- 느린 쿼리 로그로 남기기
* log_slow_queries=/path/to/log
* log_queries_not_using_indexes
- 벤치마킹 시에는 다 고정시키고 변수 하나만 바꿔가면서 해야 함. (쿼리 캐시는 끌 것.)
- 도구를 써라~~
* EXPLAIN
* SHOW PROFILE
* MyTop/innotop
* mysqlslap
* MyBench
* ApacheBench (ab)
* super-smack
* SysBench
* JMeter/Ant
* Slow Query Log

## `AUTO_INCREMENT` 안 쓰는 것
- PK를 AUTO_INCREMENT로 쓰는건 무진장 최적화 되어 있음
* 고속 병행 INSERT 가능
* 잠금 안 걸리고 읽으면서 계속 할 수 있다는!
- 새 레코드를 근처에 놓음으로써 디스크와 페이지 단편화를 줄임
- 메모리와 디스크에 핫 스팟을 생성하고 스와핑을 줄임

## `ON DUPLICATE KEY UPDATE`를 안 쓰는 것
- 레코드가 있으면 업데이트하고 없으면 인서트하고 이런 코드 필요없다!! 다 날려버려라!!
- 서버에 불필요하게 왔다갔다 할 필요가 없어짐
- 5-6% 정도 빠름
- 데이터 입력이 많다면 더 커질 수 있음

## 하지 말아야 할 것 총정리
- Thinking too small
- Not using EXPLAIN
- Choosing the wrong data types
- Using persistent connections in PHP
- Using a heavy DB abstraction layer
- Not understanding storage engines
- Not understanding index layouts
- Not understanding how the query cache works
- Using stored procedures improperly
- Operating on an indexed column with a function
- Having missing or useless indexes
- Not being a join-fu master
- Not accounting for deep scans
- Doing `SELECT COUNT(*)` without WHERE on an InnoDB table
- Not profiling or benchmarking
- Not using AUTO_INCREMENT
- Not using ON DUPLICATE KEY UPDATEK
