const Koa = require("koa");
const logger = require('koa-logger')
const app = new Koa();

app.use(logger())

// 浏览器地址栏，只能发get请求
// a标签，img标签，link标签，script标签 只能发get请求
// form表单中有一个method属性，如果method属性是get，表示发get请求
// form表单中有一个method属性，如果method属性是post，表示发post请求
// postman，也可以发送post请求
// ajax可以发get请求，也可以发post请求
app.use(async ctx => {
    ctx.body = "hello node~"
})

app.listen(3000, () => {
    console.log("server is running on 3000");
})

// <-- GET /
// --> GET / 200 9ms 11b