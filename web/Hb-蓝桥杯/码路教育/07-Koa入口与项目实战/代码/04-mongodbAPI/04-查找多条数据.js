const MongoClient = require('mongodb').MongoClient
    ; (async function () {
        const client = new MongoClient('mongodb://127.0.0.1:27017')
        // 链接服务端
        await client.connect()
        console.log('链接成功')

        const db = client.db('school')
        const grade1 = db.collection('grade1')

        let res = await grade1.find().toArray();
        console.log("res:",res);

        // 关闭客户端的链接
        client.close()
    })()
