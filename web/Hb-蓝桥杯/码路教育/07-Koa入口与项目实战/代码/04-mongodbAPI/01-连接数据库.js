const MongoClient = require('mongodb').MongoClient;

(async function() {
	const client = new MongoClient('mongodb://127.0.0.1:27017');
	
	// 链接服务端
	await client.connect()
	console.log('链接成功')

	// 获取数据库 
	const db = client.db('school')
	console.log("db:", db);
	
	// 获取集合
	const grade1 = db.collection('grade1')

	await grade1.insertOne({
		name: "旺财",
		age: 20,
		hobby: ['吃饭', '睡觉', '打豆豆'],
		score: 90
	})

	// 关闭客户端的链接
	client.close()
})()
