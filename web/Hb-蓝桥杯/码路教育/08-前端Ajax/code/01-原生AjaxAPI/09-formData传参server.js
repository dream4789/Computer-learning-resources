const Koa = require("koa");
const cors = require("koa2-cors");
const logger = require("koa-logger");
const Router = require("@koa/router");
// 之前: body-parser
// 现在: koa-body
const koaBody = require("koa-body");
const app = new Koa();
const router = new Router();

app.use(cors());
app.use(logger());
app.use(koaBody({ multipart: true }));

router.post("/post", async (ctx, next) => {
    ctx.status = 200;
    ctx.body = ctx.request.body;
});

app.use(router.routes())
router.allowedMethods();

app.listen(3000, () => {
    console.log("running in http://127.0.0.1:3000");
});
