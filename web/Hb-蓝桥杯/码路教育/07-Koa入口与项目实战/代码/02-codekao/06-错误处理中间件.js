const Koa = require("koa");
const logger = require('koa-logger')
const onerror = require('koa-onerror');
const app = new Koa();

app.use(logger())
// 用来处理错误
onerror(app);

app.use(async (ctx, next) => {
    // let err = new Error("未授权，不能访问")
    // err.status = 401;
    // throw err;

    ctx.throw(401, "未授权，不能访问", { data: "你需要登录后才能访问~" })
})

app.on("error", err => {
    console.log("全局错误：", err.message, err.status, err.data);
})

app.listen(3000, () => {
    console.log("server is running on 3000");
})