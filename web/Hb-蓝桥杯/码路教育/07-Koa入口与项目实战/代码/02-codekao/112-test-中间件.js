var Koa = require('koa');
var Router = require('koa-router');
var app = new Koa();
var router = new Router();
// Koa 错误处理中间件
// 无论app.use放到路由前面还是后面
// 都是先执行app.use再去执行路由
app.use(async (ctx, next) => {
    console.log('这是一个中间件');       // 执行顺序1
    await next();
    if (ctx.status == 404) {           // 执行顺序3
        ctx.body = '这是一个404页面';
    } else {
        console.log(ctx.url);
    }
});
// 配置新闻页                            // 执行顺序2
router.get('/news', async (ctx, next) => {
    console.log('这是新闻路由');
    await next();
});
 
app.use(router.routes());
app.use(router.allowedMethods());
 
app.listen(3000);