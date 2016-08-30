-- 예약 테이블
CREATE TABLE `reservation` (
	`r_idx` BIGINT UNSIGNED  NOT NULL COMMENT '방 인덱스', -- 방 인덱스
	`date`  DATETIME         NOT NULL COMMENT '예약 날짜', -- 예약 날짜
	`u_idx` BIGINT UNSIGNED  NOT NULL COMMENT '사용자 인덱스', -- 사용자 인덱스
	`cnt`   INTEGER UNSIGNED NULL     COMMENT '예약자 수' -- 예약자 수
)
COMMENT '예약 테이블';

-- 예약 테이블
ALTER TABLE `reservation`
	ADD CONSTRAINT `PK_reservation` -- 예약 테이블 기본키
		PRIMARY KEY (
			`r_idx`, -- 방 인덱스
			`date`   -- 예약 날짜
		);
