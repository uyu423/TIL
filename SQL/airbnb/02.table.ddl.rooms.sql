-- 방
CREATE TABLE `rooms` (
	`idx`         BIGINT UNSIGNED  NOT NULL COMMENT '인덱스', -- 인덱스
	`u_idx`       BIGINT UNSIGNED  NOT NULL COMMENT '관리자 인덱스', -- 관리자 인덱스
	`name`        VARCHAR(255)     NOT NULL COMMENT '방 이름', -- 방 이름
	`address`     VARCHAR(255)     NOT NULL COMMENT '주소', -- 주소
	`desc`        TEXT             NULL     COMMENT '설명', -- 설명
	`max_cnt`     INTEGER UNSIGNED NOT NULL COMMENT '최대 수용', -- 최대 수용
	`default_cnt` INTEGER UNSIGNED NOT NULL COMMENT '기본 수용', -- 기본 수용
	`add_price`   INTEGER UNSIGNED NOT NULL COMMENT '인원 추가당 가격' -- 인원 추가당 가격
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
