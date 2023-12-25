const mongodb = require("./index.js")

mongodb.once('connect', async () => {
    const students = mongodb.col('students');
    try {
        // 插入测试数据
        await students.deleteMany();
        await students.insertMany([{
            "name": '张三',
            "age": 20,
            "score": 90,
            "class": 1
        },
        {
            "name": '李四',
            "age": 24,
            "score": 90,
            "class": 4
        },
        {
            "name": '王五',
            "age": 28,
            "score": 95,
            "class": 2
        },
        {
            "name": '张三',
            "age": 20,
            "score": 93,
            "class": 1
        },
        {
            "name": '张三2',
            "age": 40,
            "score": 40,
            "class": 1
        },
        {
            "name": '张三3',
            "age": 20,
            "score": 90,
            "class": 1
        },
        {
            "name": '张三4',
            "age": 20,
            "score": 90,
            "class": 1
        },
        {
            "name": '张三6',
            "age": 20,
            "score": 90,
            "class": 1
        },
        {
            "name": '张三7',
            "age": 20,
            "score": 90,
            "class": 1
        },
        {
            "name": '张三',
            "age": 20,
            "score": 90,
            "class": 1
        }
        ])
        console.log('测试数据插入成功');

    } catch (error) {
        console.log(error.stack);
    }
})