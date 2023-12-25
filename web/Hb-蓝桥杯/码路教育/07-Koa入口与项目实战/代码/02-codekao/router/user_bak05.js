const Router = require("@koa/router");

const router = new Router();

router.prefix("/user")

router.get("/list", (ctx, next) => {

    // 给客户端种植一个cookie
    // 后面浏览器每一次请求服务器，都带着cookie
    // 当会话结束，cookie就死了
    // ctx.cookies.set("username", "wangcai")

    // 设置cookie存活七天
    // ctx.cookies.set("username", "xiaoqiang", {
    //     maxAge: 60000 * 60 * 24 * 7
    // })

    // 获取cookie
    // console.log("获取cookie", ctx.cookies.get("username"));

    // ctx.body = "用户列表"

    // --------------------------------------------------------------

    let last = ctx.cookies.get("last")
    // 第1次访问时，需要种植一个cookie
    ctx.cookies.set("last", new Date().toLocaleString(), {
        maxAge: 60000 * 60 * 24 * 365
    })

    if (last) {
        ctx.body = `你上一次访问本网站的时间是:${last}`
    } else {
        // 第1次访问
        ctx.body = '这是你第1次访问本网站~'
    }

})
router.get("/add", (ctx, next) => {
    ctx.body = "添加用户"
})

module.exports = router;