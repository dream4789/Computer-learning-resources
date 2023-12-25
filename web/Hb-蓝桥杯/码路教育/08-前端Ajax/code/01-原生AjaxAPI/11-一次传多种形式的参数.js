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

router.post("/post/:name/:age", async (ctx, next) => {
    ctx.status = 200;
    let postData = ctx.request.body;
    let paramsData = ctx.params;
    let queryData = ctx.query;
    console.log("postData:", postData);
    console.log("paramsData:", paramsData);
    console.log("queryData:", queryData);
    ctx.body = ctx.request.body;
});

app.use(router.routes())
router.allowedMethods();

app.listen(3000, () => {
    console.log("running in http://127.0.0.1:3000");
});
