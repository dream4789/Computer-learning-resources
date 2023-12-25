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

	// limit(n) 显示前 n 条数据
	// let res = await grade1.find().limit(4).toArray();
	// console.log("res:", res);

	// skip(n) 跳过前 n 条数据
	// let res = await grade1.find().skip(2).limit(3).toArray();
	// console.log("res:", res);
	
	// sort 排序  1表示正序  -1表示倒序
	// let res = await grade1.find().sort({
	//     age: -1
	// }).toArray()
	// console.log("res:", res);
	
	// -----------------------------------
	

	// pageno=1  第1页
	// pagesize=3  一页显示几条数据

	// 第1页数据：  skip(0).limt(pagesize)
	// 第2页数据：  skip(3).limt(pagesize)
	// 第3页数据：  skip(6).limt(pagesize)
	// 第4页数据：  skip(9).limt(pagesize)
	// 第n页数据：  skip((pageno - 1) * pagesize).limt(pagesize)


	// -----------------------------------
	
	const pageIndex = 2 //当前的索引
	const pageSize = 3 //当前一页显示的数据
	r = await grade1
		.find()
		.skip((pageIndex - 1) * pageSize)
		.limit(pageSize)
		.toArray()
	console.log("r:", r);


	// 关闭客户端的链接
	client.close()
})()
