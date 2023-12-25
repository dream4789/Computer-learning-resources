const Router = require("@koa/router");

const router = new Router();

router.prefix("/user")

router.get("/list", (ctx, next) => {
    ctx.body = "用户列表"
})

// 我们可以把数据传递给后端，get请求，有get请求的传递方式
// get传参有两种方式
//    1）params传参     /user/1   /user/2    /user/3    动态路由
//    2）query传参      /user?name=wc&age=18
//    get传参，参数需要放在url中   post传参，参数需要放在请求体中
router.get("/add", (ctx, next) => {
    console.log(ctx.query);
    ctx.body = "增加用户"
})

router.get("/del/:id", (ctx, next) => {
    console.log(ctx.params.id);
    ctx.body = "删除用户"
})

module.exports = router;