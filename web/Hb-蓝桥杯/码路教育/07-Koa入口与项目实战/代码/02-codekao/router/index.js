const Router = require("@koa/router");
const bouncer = require("koa-bouncer")
const captcha = require("trek-captcha")
const router = new Router();

// 生成图形验证码
router.get("/captcha", async (ctx, next) => {
    let { buffer, token } = await captcha({ size: 4 })

    // token的作用：前端输入验证码与此token进行对比

    // 生成验证码图片
    ctx.body = buffer;
})

router.get("/xxx", (ctx, next) => {
    ctx.body = "欢迎访问首页面"
})

module.exports = router;

// http://localhost:3000/xxx