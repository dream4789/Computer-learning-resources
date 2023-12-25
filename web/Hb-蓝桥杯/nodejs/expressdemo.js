//1. 引入express
const express = require('express');
const {request, response} = require("express");

//2. 创建应用对象
const app = express();

//3. 创建路由规则
app.get('/', (request, response) => {
    response.send("Hello,Express");
});

//4. 启动监听端口
app.listen(8000, () => {
    console.log("服务已启动，8000端口监听中。。。")
})