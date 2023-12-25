const Router = require("@koa/router");

const router = new Router();

router.prefix("/user")

router.get("/list", (ctx, next) => {
    ctx.body = "用户列表"
})
// 1）下载 npm i koa-bodyparser@4.3.0
// 2）配置
//     const bodyParser = require('koa-bodyparser')
//     app.use(bodyParser());
// 3）通过ctx.request.body得到post提交过来数据了
router.post("/add", (ctx, next) => {
    console.log(ctx.request.body);
    ctx.body = "添加用户"
})

module.exports = router;