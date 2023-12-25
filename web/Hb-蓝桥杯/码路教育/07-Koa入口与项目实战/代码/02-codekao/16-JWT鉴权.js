const Koa = require("koa");
const bodyParser = require('koa-bodyparser')
const user = require("./router/user.js")
const app = new Koa();

// post请求获取数据
app.use(bodyParser());

// 注册路由
app.use(user.routes())
user.allowedMethods();


app.listen(3000, () => {
    console.log("server is running on 3000");
})

