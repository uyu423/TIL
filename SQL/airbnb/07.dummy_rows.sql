INSERT INTO `tiers` (`idx`, `tier_name`, `discountPer`) VALUES
  (NULL, 'Normal', '0'),
  (NULL, 'Good', '0.05'),
  (NULL, 'Best', '0.10'),
  (NULL, 'King', '0.20'),
  (NULL, 'God', '0.40');

INSERT INTO `users` (`idx`, `email`, `name`, `encrypted_password`, `phone`, `created_at`, `updated_at`, `t_idx`) VALUES
  (NULL, 'foo@bar.com', 'Foo Bar', PASSWORD('1234'), '+82100000000', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, '1'),
  (NULL, 'hello@world.com', 'Hello World', PASSWORD('4321'), '+82100000001', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, '2'),
  (NULL, 'goo@gle.com', 'Google', PASSWORD('1234'), '+82100000002', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, '3'),
  (NULL, 'king@sejong.co.kr', '건전한배틀태그', PASSWORD('4321'), '+82100000003', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, '4'),
  (NULL, 'purple@works.com', 'Purpleworks', PASSWORD('d...difficult'), '+82100000004', CURRENT_TIMESTAMP, CURRENT_TIMESTAMP, '5');

INSERT INTO `rooms` (`idx`, `u_idx`, `name`, `address`, `desc`, `max_cnt`, `default_cnt`, `add_price`) VALUES
  (NULL, '5', 'Purple Room 1', 'Purple Si, Works Dong 1', NULL, '4', '2', '10'),
  (NULL, '5', 'Purple Big Room 2', 'Purple Si, Works Dong 2', NULL, '8', '4', '5'),
  (NULL, '4', 'Gyeongbok Royal Palace', '서울특별시 종로구 사직로 161', NULL, '100', '2', '15');

INSERT INTO `price` (`r_idx`, `type`, `st_at`, `ed_at`, `price`) VALUES
  ('1', 'weekday', NULL, NULL, '40'),
  ('1', 'weekend', NULL, NULL, '50'),
  ('1', 'event', '2016-09-05 00:00:00', '2016-09-09 00:00:00', '25'),
  ('1', 'semi_hot', '2016-08-01 00:00:00', '2016-08-07 00:00:00', '60'),
  ('1', 'hot', '2016-08-08 00:00:00', '2016-08-26 00:00:00', '80');

INSERT INTO `reservation` (`r_idx`, `date`, `u_idx`, `cnt`) VALUES
  ('1', '2016-08-23 00:00:00', '1', '3'),
  ('1', '2016-08-24 00:00:00', '1', '3'),
  ('1', '2016-08-25 00:00:00', '1', '3')
