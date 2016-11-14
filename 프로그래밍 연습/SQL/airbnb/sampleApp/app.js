import express from 'express';
import morgan from 'morgan';
import bodyParser from 'body-parser';
import colors from 'colors';
import qsb from 'node-qsb';
import moment from 'moment';
import dotenv from 'dotenv';

// include MySQL Config js file
import { execute } from './mysql';

// Load .env file Sets
dotenv.load();

const app = express();

// using Middleware
app.use(morgan('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

// Api Call Routing
app.get('/showAbleRoomsByGuestCnt', (req, res) => {
  // http://localhost:3000/showAbleRoomsByGuestCnt?people_cnt=5
  // SELECT * FROM rooms WHERE max_cnt > 4 AND default_cnt <= 4;
  console.log("-- Call Func : showAbleRooms --".green);
  const peopleCnt = req.query.people_cnt;
  const qs = new qsb().select('rooms')
    .where('max_cnt', '>=', peopleCnt)
    .where('default_cnt', '<=', peopleCnt);

  execute(qs, (error, result) => {
    if(error) {
      res.status(500).send(error);
    }
    else {
      res.json(result);
    }
  })
});

app.get('/showAbleRoomsByDate', (req, res) => {
  // http://localhost:3000/showAbleRoomsByDate?st_at=20160910&ed_at=20160912
  console.log("-- Call Func : showAbleRooms --".green);
  const stAt = moment(req.query.st_at, 'YYYYMMDD');
  const edAt = moment(req.query.ed_at, 'YYYYMMDD');
  const subQs = "SELECT RE.r_idx FROM rooms RO LEFT JOIN reservation RE ON "
    + "RO.idx = RE.r_idx WHERE RE.date > '" + stAt.format('YYYY-MM-DD')
    + "' AND RE.date < '" + edAt.format('YYYY-MM-DD') + "'";

  const qs = new qsb().forceQuery("SELECT * FROM (" + subQs + ") AS T "
    + "RIGHT JOIN rooms R ON R.idx = T.r_idx WHERE T.r_idx IS NULL");
  execute(qs, (error, result) => {
    res.json(result);
  })
});

app.get('/showRoomPriceTable', (req, res) => {
  console.log("-- Call Func : showRoomPriceTable --".green);
  // require Define
});

app.get('/showRoomReservation', (req, res) => {
  console.log("-- Call Func : showAbleRooms --".green);
  // require Define
});


// Server Open
app.listen(process.env.PORT, () => {
  console.log("API Testing Server listening " + process.env.PORT);
})
