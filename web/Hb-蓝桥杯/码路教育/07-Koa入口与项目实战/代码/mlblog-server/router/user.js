const Router = require("@koa/router");

const router = new Router();

router.prefix("/user")

router.get("/list", (ctx, next) => {
    ctx.body = "用户列表"
})

router.get("/add", (ctx, next) => {
    ctx.body = "增加用户"
})

router.get("/delete", (ctx, next) => {
    ctx.body = "删除用户"
})

module.exports = router;