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

-- 가격 테이블
ALTER TABLE `price`
	ADD CONSTRAINT `FK_rooms_TO_price` -- 방 -> 가격 테이블
		FOREIGN KEY (
			`r_idx` -- 방 인덱스
		)
		REFERENCES `rooms` ( -- 방
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
