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

INSERT INTO `rooms` (`idx`, `u_idx`, `name`, `address`, `desc`, `max_cnt`, `default_cnt`, `cnt_price`, `weekday_price`, `weekend_price`) VALUES
  (NULL, '5', 'Purple Room 1', 'Purple Si, Works Dong 1', NULL, '4', '2', '10000', '40000', '60000'),
  (NULL, '5', 'Purple Big Room 2', 'Purple Si, Works Dong 2', NULL, '8', '4', '10000', '80000', '150000'),
  (NULL, '4', 'Gyeongbok Royal Palace', '서울특별시 종로구 사직로 161', NULL, '100', '2', '25000', '100000', '250000');

INSERT INTO `events` (`b_idx`, `type`, `st_at`, `ed_at`, `calc_price`) VALUES
  ('1', 'sale', '2016-09-01 00:00:00', '2016-09-10 00:00:00', '-20000'),
  ('1', 'semi_hot', '2016-09-11 00:00:00', '2016-09-17 00:00:00', '20000'),
  ('1', 'hot', '2016-09-18 00:00:00', '2016-09-30 00:00:00', '50000')

INSERT INTO `reservation` (`r_idx`, `date`, `u_idx`, `cnt`) VALUES
  ('1', '2016-09-02 00:00:00', '1', '3'),
  ('1', '2016-09-03 00:00:00', '1', '3'),
  ('1', '2016-10-02 00:00:00', '1', '3');
