const Koa = require('koa');
const app = new Koa();

// 1：
// const main = ctx => {
// 	console.log(`${Date.now()} ${ctx.request.method} ${ctx.request.url}`);
// 	ctx.response.body = 'Hello World';
// };



// 2：
const logger = (ctx, next) => {
  console.log(`${Date.now()} ${ctx.request.method} ${ctx.request.url}`);
  next();
}
const main = ctx => {
  ctx.response.body = 'Hello World';
};
app.use(logger);


// 1674569889153 GET /
// 1674569889421 GET /favicon.ico
app.use(main);
app.listen(3000);