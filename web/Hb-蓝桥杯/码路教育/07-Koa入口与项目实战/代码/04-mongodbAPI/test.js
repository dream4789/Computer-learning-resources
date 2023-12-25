const MongoClient = require('mongodb').MongoClient;
(async function() {
	const client = new MongoClient('mongodb://127.0.0.1:27017')
	// 链接服务端
	await client.connect()
	console.log('链接成功')

	// 获取数据库 
	const db = client.db('school')
	// 获取集合
	const grade1 = db.collection('grade1')

	// ------------------------ 查询数据 ------------------------	
	// 查询一条
	// console.log(grade1.findOne({ name: "张三" }))  // 耗时
	
	// let res = await grade1.find({
	// 	name: "王五",
	// 	age: 20
	// })
	// console.log(res);  // <ref *2> FindCursor {}

	let res = await grade1.findOne({
		name: "王五",
		age: 20
	})
	console.log(res);  //  {}
	res = await grade1.findOne({
		name: "王五"
	})
	console.log(res);  // {}


	// 查询多条
	res = await grade1.find({
		name: "王五",
		age: 20
	}).toArray(); // 找 name 是 王五 且 age 是 20
	console.log(res);  // [{}]


	// 关闭客户端的链接
	client.close()
})()
