let Koa = require("koa");
let app = new Koa();

// app.use(async ctx => {
//     ctx.body = "hello node~"
// })

// 这是我们自己写的中间件，用来处理错误
app.use(async (ctx, next) => {
    try {
        await next()
    } catch (error) {
        console.log("error:", error);
        ctx.status = 500; // 表示响应的状态码
        ctx.type = "json"; // 告诉客户端，响应的数据是json数据
        ctx.body = {
            ok: 0,
            message: error.message
        }

        // 手动触发
        ctx.app.emit("error", error, ctx)
    }
})


// 抛出一个错误
app.use(async ctx => {
    throw new Error("未知错误")
})

// 全局错误处理，后台打印
app.on("error", err => {
    console.log("全局错误处理", err);
})


app.listen(3000, () => {
    console.log("server is running on 3000");
})