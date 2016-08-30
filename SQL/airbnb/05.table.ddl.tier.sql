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
