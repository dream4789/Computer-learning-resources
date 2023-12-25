const MongoClient = require('mongodb').MongoClient;
(async function () {
    const client = new MongoClient('mongodb://127.0.0.1:27017')
    // 链接服务端
    await client.connect()
    console.log('链接成功')

    // 获取数据库 
    const db = client.db('school')
    // 获取集合
    const grade1 = db.collection('grade1')

    // 正则表达式  找以张开头的人员  ^表示以什么打头
    r = await grade1.find({
        name: {
            $regex: /^张/,
        },
    }).toArray()

    console.log("r:", r);

    // 关闭客户端的链接
    client.close()
})()