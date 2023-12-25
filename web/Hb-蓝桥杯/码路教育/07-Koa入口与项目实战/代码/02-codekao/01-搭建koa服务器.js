// 框架：
//    学习规则：按人家的要求，在合适的位置，写合适的代码
// IP: 127.0.0.1  域名：localhost  端口：3000
const Koa = require("koa");
const app = new Koa();
// ctx是上下文
// 就是一个中间件
app.use(async ctx => {
	// 响应一个字符串，叫 hello koa
	ctx.body = "hello koa~"
})

app.listen(3000);
