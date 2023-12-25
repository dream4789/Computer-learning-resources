const Router = require("@koa/router");

// 创建一个路由器对象
// router叫路由器   route叫路由
const router = new Router();

router.get("/", (ctx, next) => {
    ctx.body = "欢迎访问首页面"
})

// 导出路由器对象
module.exports = router;