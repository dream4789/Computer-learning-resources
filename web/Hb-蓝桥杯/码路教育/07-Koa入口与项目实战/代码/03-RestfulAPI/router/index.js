const Router = require("@koa/router");
const router = new Router();

router.get("/home", ctx => {
    ctx.body = "欢迎访问首页面"
})

module.exports = router;