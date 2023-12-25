const MongoClient = require('mongodb').MongoClient

    ;
(async function () {
    const client = new MongoClient('mongodb://127.0.0.1:27017')
    // 链接服务端
    await client.connect()
    console.log('链接成功')

    // 获取数据库 
    const db = client.db('school')
    // 获取集合
    const grade1 = db.collection('grade1')

    // 当你做删除的时候 一定要问一下自己 是否要删除
    r = await grade1.deleteOne({
        name: '小张三'
    })
    console.log(r.result);

    // 关闭客户端的链接
    client.close()
})()