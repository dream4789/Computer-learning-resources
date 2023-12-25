const Koa = require("koa");
const index = require("./router/index.js")
const static = require('koa-static');

const app = new Koa();

// 托管静态资源（静态网页）
app.use(static(__dirname + '/public'))

// 注册首页模块路由
app.use(index.routes())
index.allowedMethods();


app.listen(3000, () => {
    console.log("server is running on 3000");
})


