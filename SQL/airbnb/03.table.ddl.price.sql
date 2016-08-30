-- 가격 테이블
CREATE TABLE `price` (
	`r_idx` BIGINT UNSIGNED  NULL     COMMENT '방 인덱스', -- 방 인덱스
	`type`  VARCHAR(160)     NOT NULL COMMENT '타입', -- 타입
	`st_at` DATETIME         NULL     COMMENT '시작 날짜', -- 시작 날짜
	`ed_at` DATETIME         NULL     COMMENT '끝 날짜', -- 끝 날짜
	`price` INTEGER UNSIGNED NOT NULL COMMENT '가격' -- 가격
)
COMMENT '가격 테이블';

-- 가격 테이블 유니크 인덱스
CREATE UNIQUE INDEX `UIX_price`
	ON `price` ( -- 가격 테이블
		`r_idx` ASC, -- 방 인덱스
		`type` ASC   -- 타입
	);
