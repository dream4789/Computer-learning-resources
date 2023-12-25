let Koa = require("koa");
let app = new Koa();

// 1.此中间件响应了正确的内容
// app.use(async ctx => {
//     ctx.body = "hello koa~"
// })

// 2.抛出一个错误
app.use(async ctx => {
    throw new Error("未知错误")
})



// 全局错误处理，后台打印
app.on("error", err => {
    console.log("全局错误处理", err);
})

app.listen(3000)