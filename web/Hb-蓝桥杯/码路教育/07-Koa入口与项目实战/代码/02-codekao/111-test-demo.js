// 引入Koa
const Koa = require('koa');
// 实例化Koa
const app = new Koa();

const main = ctx => {
	// ctx.response.body = 'Hello World';
	ctx.body = 'Hello World';
};

app.use(main);

app.listen(3000);
