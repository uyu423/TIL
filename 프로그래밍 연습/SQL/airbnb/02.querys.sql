# 특정 방의 요금 테이블 조회
SELECT * FROM `rooms` R JOIN `events` E ON R.`idx` = E.`b_idx` WHERE R.`idx` = 1

# 체크인, 체크아웃 날자로 예약 가능한 방 조회
SELECT
  *
FROM
  (
  SELECT
    RE.r_idx
  FROM
    rooms RO
  LEFT JOIN
    reservation RE ON RO.idx = RE.r_idx
  WHERE
    RE.date > '2016-09-10' AND RE.date < '2016-09-12'
) AS T
RIGHT JOIN
  rooms R ON R.idx = T.r_idx
WHERE
  T.r_idx IS NULL

# 게스트 수로 예약 가능한 방 조회
SELECT * FROM rooms WHERE max_cnt > 4 AND default_cnt <= 4;

# 금액 범위로 예약 가능한 방 조회 (할인 미적용?)
select 'ah...';

# 특정 방의 예약 정보 조회
SELECT
  RO.idx AS r_idx,
  RO.name AS r_name,
  RE.date AS DATE,
  U2.idx as host_idx,
  U2.email as host_email,
  U2.name as host_name,
  U.idx AS guest_idx,
  U.email AS guest_email,
  U.name AS guest_name,
  RE.payment AS payment
FROM
  reservation RE
JOIN
  rooms RO ON RE.r_idx = RO.idx
JOIN
  users U ON RE.u_idx = U.idx
JOIN
  users U2 ON RO.u_idx = U2.idx
WHERE
  RE.r_idx = 1 # room idx

# 특정 유저의 예약 현황 조회
SELECT
  RO.idx AS r_idx,
  RO.name AS r_name,
  RE.date AS DATE,
  U2.idx as host_idx,
  U2.email as host_email,
  U2.name as host_name,
  U.idx AS guest_idx,
  U.email AS guest_email,
  U.name AS guest_name,
  RE.payment AS payment
FROM
  reservation RE
JOIN
  rooms RO ON RE.r_idx = RO.idx
JOIN
  users U ON RE.u_idx = U.idx
JOIN
  users U2 ON RO.u_idx = U2.idx
WHERE
  RE.u_idx = 1 # guest idx

# 특정 호스트가 가진 방들의 예약 정보 조회
SELECT
  RO.idx AS r_idx,
  RO.name AS r_name,
  RE.date AS DATE,
  U2.idx as host_idx,
  U2.email as host_email,
  U2.name as host_name,
  U.idx AS guest_idx,
  U.email AS guest_email,
  U.name AS guest_name,
  RE.payment AS payment
FROM
  reservation RE
JOIN
  rooms RO ON RE.r_idx = RO.idx
JOIN
  users U ON RE.u_idx = U.idx
JOIN
  users U2 ON RO.u_idx = U2.idx
WHERE
  U2.idx = 5 # host idx

# 방 예약
INSERT INTO `reservation` (`r_idx`, `date`, `u_idx`, `cnt`, `payment`) VALUES
  ('3', '2016-09-21 00:00:00', '1', '50', '40000'),
  ('3', '2016-09-22 00:00:00', '1', '50', '40000'),
  ('3', '2016-09-23 00:00:00', '1', '50', '50000');
