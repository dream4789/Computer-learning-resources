
module.exports = async (ctx, next) => {
    if (ctx.session.userinfo) {
        await next();
    } else {
        ctx.body = {
            code: 401,
            message: "未授权"
        }
    }
}