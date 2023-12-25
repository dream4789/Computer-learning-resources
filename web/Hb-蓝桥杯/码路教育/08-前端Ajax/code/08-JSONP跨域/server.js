const Koa = require("koa");
const cors = require("koa2-cors");
const logger = require("koa-logger");
const Router = require("@koa/router");
const koaBody = require("koa-body");
const app = new Koa();
const router = new Router();

app.use(cors());
app.use(logger());
app.use(koaBody());

router.get("/", (ctx) => {
    let cb = ctx.query.callBack;
    // console.log(cb);

    // 后端返回函数调用字符串
    // ctx.body = "ok"
    // ctx.body = "fn()"
    // ctx.body = "fn({a:1,b:2})"
    ctx.body = `${cb}(${JSON.stringify({ a: 1, b: 2 })})`
})

app.use(router.routes())
router.allowedMethods();

app.listen(3000, () => {
    console.log("running in http://127.0.0.1:3000");
});
