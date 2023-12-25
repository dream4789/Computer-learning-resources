const Router = require("@koa/router");
const bouncer = require("koa-bouncer")
const router = new Router();

router.post("/", async (ctx, next) => {
    console.log(ctx.request.body);
    try {
        let res = ctx.validateBody('username')
            .required("用户名是必传参数")
            .isString()
            .trim()
            .isLength(4, 8, "用户名必须是4~8位")

        ctx.validateBody('email')
            .optional()
            .isString()
            .trim()
            .isEmail('非法的邮箱格式')
        
        ctx.validateBody('pwd1')
            .required('密码是必填项')
            .isString()
            .trim()
            .isLength(6, 16, '密码必须是6~16位')
        
        ctx.validateBody('pwd2')
            .required('密码是必填项')
            .isString()
            .trim()
            .eq(ctx.vals.pwd1, '两次密码不一致')
        

        console.log("res.vals:", res.vals);
        ctx.body = {
            ok: 1,
            message: "校验通过"
        }
    } catch (err) {
        if (err instanceof bouncer.ValidationError) {
            ctx.status = 400;
            ctx.body = {
                ok: 0,
                message: "校验失败：" + err.message
            }
            return;
        }
        throw err;
    }
})

router.get("/xxx", (ctx, next) => {
    ctx.body = "欢迎访问首页面"
})

module.exports = router;