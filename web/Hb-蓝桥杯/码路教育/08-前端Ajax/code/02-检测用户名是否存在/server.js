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

// 模拟从数据库中取到的用户信息
let users = ["wc", "xq", "admin"];

router.post("/check", (ctx) => {
    let username = ctx.request.body.username.trim();
    if (users.find(user => user === username)) {
        ctx.body = {
            code: 0,
            msg: "对不起,该用户名已经被注册,请换个用户名"
        }
    } else {
        ctx.body = {
            code: 1,
            msg: "恭喜你,该用户可以使用"
        }
    }

})

app.use(router.routes())
router.allowedMethods();

app.listen(3000, () => {
    console.log("running in http://127.0.0.1:3000");
});
