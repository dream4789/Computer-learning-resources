const koa = require('koa');
const Router = require('koa-router');
const app = new koa();
const router = new Router();

// http://localhost:3000/not_found
const not = ctx => {
	ctx.response.status = 404;
	ctx.response.body = "Sorry we do not have this resource.";
}

// http://localhost:3000/hello
const test = ctx => {
	ctx.response.status = 200;
	ctx.response.body = "Hey there!";
}

// http://localhost:3000/dsasd 随便
const main = ctx => {
	console.log('111');
	if (404 != ctx.response.status) return;
	ctx.response.redirect('/not_found');  // 301 永久
	// ctx.response.status = 302;  // 修改
}

app.use(router.routes());
router.get('/hello', test);
router.get('/not_found', not);
app.use(main);
app.listen(3000);
