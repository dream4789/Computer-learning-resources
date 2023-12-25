// session是数据存储在服务器，是基于cookie的，第1次访问服务器时
// 会生成一个sid，sid会以cookie的形式种植到客户端，
// 客户端后面再去访问服务器时，会带上sid
// 服务器去验证sid的合法性

const Koa = require("koa");
const session = require('koa-session');
const app = new Koa();

// 对cookie进行加密签名
app.keys = ['some secret hurr'];

// 对sesson的配置
const SESSION_CONFIG = {
	key: 'wc', //设置cookie的key名字
	maxAge: 86400000, //有效期，默认是一天
	httpOnly: true, //仅服务端修改
	signed: true, //签名cookie
}
app.use(session(SESSION_CONFIG, app))


// 写一个中间件
app.use(async ctx => {
	console.log(ctx.path);
	if (ctx.path === "/xxx") {
		return;
	}
	let n = ctx.session.count || 0
	ctx.session.count = ++n;
	ctx.body = `第${n}次访问本网站`
})

app.listen(3000, () => {
	console.log("server is running on 3000");
})
