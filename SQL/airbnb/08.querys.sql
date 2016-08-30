# for views
SELECT
  RE.r_idx,
  RO.name,
  U2.idx AS host_idx,
  U2.email AS host_email,
  U2.name AS host_name,
  U2.phone AS host_phone,
  RE.u_idx AS guest_idx,
  U.email AS guest_email,
  U.name AS guest_name,
  U.phone AS guest_phone,
  RE.date,
  RE.cnt
FROM
  reservation RE
JOIN
  rooms RO ON RE.r_idx = RO.idx
JOIN
  users U ON RE.u_idx = U.idx
JOIN
  users U2 ON RO.u_idx = U2.idx
