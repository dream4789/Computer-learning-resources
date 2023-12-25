// npm install --save koa-route 

const Koa = require('koa');
const route = require('koa-route');
const app = new Koa();

// const Router = require("koa-router");
// const route = new Router();

const redirect = ctx => {
  ctx.response.redirect('/');
};

const main = ctx => {
  ctx.response.body = 'Hello World';
};

app.use(route.get('/', main));
app.use(route.get('/redirect', redirect));

app.use(main);
app.listen(3000);

// http://127.0.0.1:3000/redirect