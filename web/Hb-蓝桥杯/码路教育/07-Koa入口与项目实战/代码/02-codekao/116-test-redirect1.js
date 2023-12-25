const router = require("koa-route");
const Koa = require('koa');
const app = new Koa();
// const router = new Router();

// router.redirect('/login', '/aaa');

app.use(router.get('/', ctx => {
	console.log('zzzzz');
	ctx.response.redirect('/aaa');
	// ctx.status = 301;
}))

const main = ctx => {
	console.log('xxxx');
	ctx.response.body = 'Hello World';
};

app.use(router.get('/aaa', main));
app.listen(3000);

// const route = require('koa-route');
// const Koa = require('koa');
// const app = new Koa();

// const main = ctx => {
// 	if (ctx.request.accepts('xml')) {
// 		ctx.response.type = 'xml';
// 		ctx.response.body = '<data>hello world</data>';
// 	}
// };

// const about = ctx => {
// 	//...code
// 	ctx.response.body = 'about!';
// };

// const redirect_test = ctx => {
// 	ctx.response.redirect('/about');
// 	// ctx.response.body = 'redirect_test!'; //无效
// }
// app.use(route.get('/', main));
// app.use(route.get('/about', about));
// app.use(route.get('/redirecttest', redirect_test));


// app.listen(3000, () => {
// 	console.log('server is running at http://localhost:3000');
// });
