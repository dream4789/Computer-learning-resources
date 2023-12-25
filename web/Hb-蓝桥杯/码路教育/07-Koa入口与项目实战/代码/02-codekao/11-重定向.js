const Koa = require("koa");
const user = require("./router/user.js")
const bodyParser = require('koa-bodyparser')
const app = new Koa();

app.use(bodyParser());


// 注册路由
app.use(user.routes())
user.allowedMethods();

app.listen(3000, () => {
    console.log("server is running on 3000");
})


