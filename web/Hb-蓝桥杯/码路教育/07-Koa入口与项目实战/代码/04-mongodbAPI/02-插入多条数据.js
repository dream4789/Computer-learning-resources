const MongoClient = require('mongodb').MongoClient ;
(async function () {
    const client = new MongoClient('mongodb://127.0.0.1:27017')
    // 链接服务端
    await client.connect()
    console.log('链接成功')

    // 获取数据库 
    const db = client.db('school')
    // 获取集合
    const grade1 = db.collection('grade1')

    let r = await grade1.insertMany([{
        name: '张三',
        age: 20,
        hobby: ['吃饭', '睡觉', '打豆豆'],
        score: 90
    },
    {
        name: '李四',
        age: 40,
        hobby: ['妹子', '篮球'],
        score: 93
    },
    {
        name: '王五',
        age: 20,
        hobby: ['妹子', '睡觉'],
        score: 70
    },
    {
        name: '赵六',
        age: 16,
        hobby: ['妹子'],
        score: 50
    },
    {
        name: '张丽',
        age: 38,
        hobby: ['妹子'],
        score: 56
    },
    {
        name: '小红',
        age: 40,
        hobby: ['妹子'],
        score: 87
    },
    {
        name: '小马',
        age: 20,
        hobby: ['妹子'],
        score: 79
    },
    {
        name: '小王',
        age: 59,
        hobby: ['妹子'],
        score: 102
    },
    {
        name: '小黑',
        age: 16,
        hobby: ['妹子'],
        score: 60
    },
    {
        name: '小哥',
        age: 18,
        hobby: ['篮球'],
        score: 49
    },
    ])

    // 关闭客户端的链接
    client.close()
})()