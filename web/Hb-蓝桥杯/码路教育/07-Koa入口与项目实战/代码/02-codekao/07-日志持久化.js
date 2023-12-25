const Koa = require("koa");
const onerror = require("koa-onerror")
const {
	accessLogger,
	logger
} = require('./logger/index.js')
const app = new Koa();

// 错误处理中间件
onerror(app)
// 持久化日志
app.use(accessLogger())

// app.use(async ctx => {
//     ctx.body = "hello koa~"
// })

app.use(async (ctx, next) => {
	ctx.throw(401, '未授权', {
		data: '你瞅瞅'
	})
})

app.on('error', (err) => {
	// 利用logooer.error就可以把错误处理持久化本地
	logger.error(err)
})

app.listen(3000, () => {
	console.log("server is running on 3000");
})
