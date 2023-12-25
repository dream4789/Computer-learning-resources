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

    // 所有包含指定字段的数据
    // r = await grade1.find({
    //     hobby: {
    //         $all: ['妹子'],
    //     },
    // }).toArray()
    // console.log("r:", r);


    // -----------------------------

    // 查找指定字段只有指定内容其一的数据
    // r = await grade1.find({
    //     hobby: {
    //         $in: ['妹子', '睡觉'],
    //     },
    // }).toArray()
    // console.log("r:", r);

    // -----------------------------

    // r = await grade1.find({  // 查找爱好数量是3个的
    //     hobby: {
    //         $size: 3
    //     },
    // }).toArray()
    // console.log("r:", r);

    // 关闭客户端的链接
    client.close()
})()