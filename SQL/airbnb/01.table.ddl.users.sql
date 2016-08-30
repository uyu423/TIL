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
