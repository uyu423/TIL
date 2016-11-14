import mysql from 'mysql';
import dotenv from 'dotenv';

dotenv.load();

const poolCluster = mysql.createPool({
	"host"				: process.env.DB_HOST,
	"user"				: process.env.DB_USERNAME,
	"password"			: process.env.DB_PASSWORD,
	"database"			: process.env.DB_DATABASE,
});

export const execute = (qs, callback) => {
    poolCluster.getConnection(function(err, connection) {
        if(err) {
            // cb(err, null);
            throw err;
            console.log('db error');
            connection.release();
            process.exit(1);
        }
        else {
            connection.query(qs.build().returnString(), function (err, rows) {
                connection.release();
                console.log(qs.returnString().inverse);
                if(err) {
					callback(err, null);
					console.error(err.red);
				}
                else {
					console.log("SUCCESS !".green);
					callback(null, rows);
				}
            });
        }
    });
};
