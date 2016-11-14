-- 사용자
CREATE TABLE `users` (
	`idx`                BIGINT UNSIGNED  NOT NULL COMMENT '인덱스', -- 인덱스
	`email`              VARCHAR(160)     NOT NULL COMMENT '이메일', -- 이메일
	`name`               VARCHAR(255)     NOT NULL COMMENT '사용자이름', -- 사용자이름
	`encrypted_password` VARCHAR(255)     NOT NULL COMMENT '비밀번호', -- 비밀번호
	`phone`              VARCHAR(160)     NOT NULL COMMENT '연락처', -- 연락처
	`created_at`         DATETIME         NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '생성 날짜', -- 생성 날짜
	`updated_at`         DATETIME         NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT '갱신 날짜', -- 갱신 날짜
	`t_idx`              INTEGER UNSIGNED NOT NULL COMMENT '등급 인덱스' -- 등급 인덱스
)
COMMENT '사용자';

-- 사용자
ALTER TABLE `users`
	ADD CONSTRAINT `PK_users` -- 사용자 기본키
		PRIMARY KEY (
			`idx` -- 인덱스
		);

ALTER TABLE `users`
	MODIFY COLUMN `idx` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '인덱스';

-- 방
CREATE TABLE `rooms` (
	`idx`           BIGINT UNSIGNED  NOT NULL COMMENT '인덱스', -- 인덱스
	`u_idx`         BIGINT UNSIGNED  NOT NULL COMMENT '관리자 인덱스', -- 관리자 인덱스
	`name`          VARCHAR(255)     NOT NULL COMMENT '방 이름', -- 방 이름
	`address`       VARCHAR(255)     NOT NULL COMMENT '주소', -- 주소
	`desc`          TEXT             NULL     COMMENT '설명', -- 설명
	`max_cnt`       INTEGER UNSIGNED NOT NULL COMMENT '최대 수용', -- 최대 수용
	`default_cnt`   INTEGER UNSIGNED NOT NULL COMMENT '기본 수용', -- 기본 수용
	`cnt_price`     INTEGER UNSIGNED NOT NULL COMMENT '인원 추가당 가격', -- 인원 추가당 가격
	`weekday_price` INTEGER UNSIGNED NOT NULL COMMENT '주간 가격', -- 주간 가격
	`weekend_price` INTEGER UNSIGNED NOT NULL COMMENT '주말 가격' -- 주말 가격
)
COMMENT '방';

-- 방
ALTER TABLE `rooms`
	ADD CONSTRAINT `PK_rooms` -- 방 기본키
		PRIMARY KEY (
			`idx` -- 인덱스
		);

ALTER TABLE `rooms`
	MODIFY COLUMN `idx` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '인덱스';

-- 예약 테이블
CREATE TABLE `reservation` (
	`r_idx`   BIGINT UNSIGNED  NOT NULL COMMENT '방 인덱스', -- 방 인덱스
	`date`    DATETIME         NOT NULL COMMENT '예약 날짜', -- 예약 날짜
	`u_idx`   BIGINT UNSIGNED  NOT NULL COMMENT '사용자 인덱스', -- 사용자 인덱스
	`cnt`     INTEGER UNSIGNED NOT NULL COMMENT '예약자 수', -- 예약자 수
	`payment` INTEGER UNSIGNED NOT NULL COMMENT '결제 금액' -- 결제 금액
)
COMMENT '예약 테이블';

-- 예약 테이블
ALTER TABLE `reservation`
	ADD CONSTRAINT `PK_reservation` -- 예약 테이블 기본키
		PRIMARY KEY (
			`r_idx`, -- 방 인덱스
			`date`   -- 예약 날짜
		);

-- 사용자 등급
CREATE TABLE `tiers` (
	`idx`         INTEGER UNSIGNED NOT NULL COMMENT '인덱스', -- 인덱스
	`tier_name`   VARCHAR(255)     NULL     COMMENT '등급 명', -- 등급 명
	`discountPer` DOUBLE           NOT NULL COMMENT '할인' -- 할인
)
COMMENT '사용자 등급';

-- 사용자 등급
ALTER TABLE `tiers`
	ADD CONSTRAINT `PK_tiers` -- 사용자 등급 기본키
		PRIMARY KEY (
			`idx` -- 인덱스
		);

ALTER TABLE `tiers`
	MODIFY COLUMN `idx` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '인덱스';

-- 특정 기간 가격 테이블
CREATE TABLE `events` (
	`b_idx`      BIGINT UNSIGNED NOT NULL COMMENT '방 인덱스', -- 방 인덱스
	`type`       VARCHAR(255)    NOT NULL COMMENT '타입', -- 타입
	`st_at`      DATETIME        NOT NULL COMMENT '시작 날짜', -- 시작 날짜
	`ed_at`      DATETIME        NOT NULL COMMENT '끝 날짜', -- 끝 날짜
	`calc_price` INTEGER         NOT NULL COMMENT '추가 가격' -- 추가 가격
)
COMMENT '특정 기간 가격 테이블';

-- 사용자
ALTER TABLE `users`
	ADD CONSTRAINT `FK_tiers_TO_users` -- 사용자 등급 -> 사용자
		FOREIGN KEY (
			`t_idx` -- 등급 인덱스
		)
		REFERENCES `tiers` ( -- 사용자 등급
			`idx` -- 인덱스
		);

-- 방
ALTER TABLE `rooms`
	ADD CONSTRAINT `FK_users_TO_rooms` -- 사용자 -> 방
		FOREIGN KEY (
			`u_idx` -- 관리자 인덱스
		)
		REFERENCES `users` ( -- 사용자
			`idx` -- 인덱스
		);

-- 예약 테이블
ALTER TABLE `reservation`
	ADD CONSTRAINT `FK_rooms_TO_reservation` -- 방 -> 예약 테이블
		FOREIGN KEY (
			`r_idx` -- 방 인덱스
		)
		REFERENCES `rooms` ( -- 방
			`idx` -- 인덱스
		);

-- 예약 테이블
ALTER TABLE `reservation`
	ADD CONSTRAINT `FK_users_TO_reservation` -- 사용자 -> 예약 테이블
		FOREIGN KEY (
			`u_idx` -- 사용자 인덱스
		)
		REFERENCES `users` ( -- 사용자
			`idx` -- 인덱스
		);

-- 특정 기간 가격 테이블
ALTER TABLE `events`
	ADD CONSTRAINT `FK_rooms_TO_events` -- 방 -> 특정 기간 가격 테이블
		FOREIGN KEY (
			`b_idx` -- 방 인덱스
		)
		REFERENCES `rooms` ( -- 방
			`idx` -- 인덱스
		);
