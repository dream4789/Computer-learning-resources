const express = require('express') //引入express 模块
const app = express() //创建实例
const mysql = require('mysql') //引入mysql 模块

var con = mysql.createConnection({
	host: "localhost",
	user: "root",
	password: "000000",
	database: "jxgl",
	port: 3306
});

// 连接数据库
con.connect(function(err) {
	if (err) {
		console.log('Error connecting to Database', err);
		return;
	}
	console.log("Connected!");
});

// 创建数据库 mydb
con.connect(function(err) {
	  if (err) throw err;
	  console.log("Connected!");
	  con.query("CREATE DATABASE mydb", function (err, result) {
			if (err) throw err;
			console.log("Database created");
	  });
});

// 创建表
con.connect(function(err) {
	if (err) throw err;
	console.log("Connected!");
	var sql =
		"CREATE TABLE customers (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), address VARCHAR(255))";
	con.query(sql, function(err, result) {
		if (err) throw err;
		console.log("Table created");
	});
});
con.connect(function(err) {
	if (err) {
		console.log('Error connecting to Database', err);
		return;
	}
	console.log("Connected!");
});


app.get('/a', (req, res) => {
	// var sql = 'select * from jxgl.score;' // 配置无db
	var sql = 'select * from score;' // 配置有db
	// var sql = "INSERT INTO score (SNO, CNO) VALUES ('960010', '001')"; // 插入
	con.query(sql, function(err, result, fields) {
		if (err) {
			console.log('sql error!', err);
			return;
		}
		console.log("Result: " + result);
	});
	// con.end(function(err){
	// 	if (err) {
	// 		console.log('end error!', err);
	// 		return;
	// 	}
	// });
})


// http://localhost:3000/a

// 转义查询
var adr = 'Mountain 21';
var sql = 'SELECT * FROM customers WHERE address = ?';
con.query(sql, [adr], function (err, result) {
	  if (err) throw err;
	  console.log(result);
});


// 插入多条数据
con.connect(function(err) {
	if (err) throw err;
	console.log("Connected!");
	var sql = "INSERT INTO customers (name, address) VALUES ?";
	var values = [
		['John', 'Highway 71'],
		['Peter', 'Lowstreet 4'],
		['Amy', 'Apple st 652'],
		['Hannah', 'Mountain 21'],
		['Michael', 'Valley 345'],
		['Sandy', 'Ocean blvd 2'],
		['Betty', 'Green Grass 1'],
		['Richard', 'Sky st 331'],
		['Susan', 'One way 98'],
		['Vicky', 'Yellow Garden 2'],
		['Ben', 'Park Lane 38'],
		['William', 'Central st 954'],
		['Chuck', 'Main Road 989'],
		['Viola', 'Sideway 1633']
	];
	con.query(sql, [values], function(err, result) {
		if (err) throw err;
		console.log("Number of records inserted: " + result.affectedRows);
	});
});

// result返回值: {
// 	fieldCount: 0,
// 	affectedRows: 14,
// 	insertId: 0, // 如果有自增id，会返回当前插入的id（只插入一条的情况下）
// 	serverStatus: 2,
// 	warningCount: 0,
// 	message: '\'Records:14  Duplicated: 0  Warnings: 0',
// 	protocol41: true,
// 	changedRows: 0
// }



// 开启服务器
app.listen(3000, () => {
	console.log('服务器在3000端口开启。。。。。');
})
