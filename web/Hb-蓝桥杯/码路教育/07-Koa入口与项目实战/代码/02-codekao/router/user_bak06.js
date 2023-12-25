const Router = require("@koa/router");

const router = new Router();

router.prefix("/user")

// 登录接口
router.post("/login", (ctx, next) => {
    let { body } = ctx.request;  // body就是前端传递过来的数据
    console.log("body:", body);  // {user:"123",pwd:"123"}
    ctx.session.userinfo = body.user; // 仅仅存储的是用户名
    // 后端API接口，一般都是响应JSON数据
    ctx.body = {
        ok: 1,
        message: "登录成功"
    }
})

// 退出登录接口   登出
router.post("/logout", (ctx, next) => {
    if (ctx.session.userinfo) {
        delete ctx.session.userinfo
    }
    ctx.body = {
        ok: 1,
        message: "退出成功"
    }
})

// 获取用户信息接口
router.get("/getUser", require("../middleware/auth.js"), (ctx, next) => {
    // if (ctx.session.userinfo) {
    //     ctx.body = {
    //         ok: 1,
    //         message: "获取用户信息成功",
    //         userinfo: ctx.session.userinfo
    //     }
    // } else {
    //     ctx.body = {
    //         ok: 0,
    //         message: "获取用户信息失败，先请登录"
    //     }
    // }

    ctx.body = {
        ok: 1,
        message: "获取用户信息成功",
        userinfo: ctx.session.userinfo
    }
})

// 获取个人收藏数据
router.get("/getLike", require("../middleware/auth.js"), (ctx, next) => {
    ctx.body = {
        ok: 1,
        message: "获取个人收藏数据成功",
    }
})

router.get("/add", (ctx, next) => {
    ctx.body = "添加用户"
})

module.exports = router;