const Router = require("@koa/router");

const router = new Router();

router.prefix("/user")

router.get("/", ctx => {
    ctx.redirect("/user/list");
    // ctx.body = "hello"
    ctx.status = 301; // 重定向
})
router.get("/list", (ctx, next) => {
    ctx.body = "用户列表"
})
router.get("/add", (ctx, next) => {
    ctx.body = "添加用户"
})

module.exports = router;