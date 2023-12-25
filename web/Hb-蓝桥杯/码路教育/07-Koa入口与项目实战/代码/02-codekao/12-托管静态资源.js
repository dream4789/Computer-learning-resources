const Koa = require("koa");
const user = require("./router/user.js")
const bodyParser = require('koa-bodyparser')
const static = require('koa-static');
const app = new Koa();

app.use(bodyParser());

// 托管静态资源（静态网页）
app.use(static(__dirname + '/public'))

// 注册路由
app.use(user.routes())
user.allowedMethods();

app.listen(3000, () => {
    console.log("server is running on 3000");
})

// 总结今日重点：
//   1）中间件   洋葱模型
//   2）get请求
//         params   /user/001
//         query    /user?name=wc&age=18
//   3）post请求
//         安装一个包   kao-bodyParser
//         ctx.request.body
//   4）重定向
//   5）静态资源托管

