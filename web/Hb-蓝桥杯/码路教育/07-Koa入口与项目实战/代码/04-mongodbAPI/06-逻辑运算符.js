const MongoClient = require('mongodb').MongoClient
    ; (async function () {
        const client = new MongoClient('mongodb://127.0.0.1:27017')
        // 链接服务端
        await client.connect()
        console.log('链接成功')

        const db = client.db('school')
        const grade1 = db.collection('grade1')

        // 找name是王五，age是20
        // let res = await grade1.find({
        //     name: "王五",
        //     age:21
        // }).toArray();
        // console.log("res:", res);

        // ------------------------------

        // 查找姓名为张三或者年龄为20的人
        // let res = await grade1.find({
        //     $or: [
        //         { name: "张三" },
        //         { age: 20 }
        //     ]
        // }).toArray();
        // console.log("res:", res);

        // ------------------------------

        // 查找年龄不大于20岁并且年龄不小于16岁的人
        let res = await grade1.find({
            $nor: [
                { age: { $gt: 20 } },
                { age: { $lt: 16 } }
            ]
        }).toArray();
        console.log("res:", res);

        // 关闭客户端的链接
        client.close()
    })()
