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

router.get("/json", async (ctx, next) => {
    ctx.status = 200;
    ctx.type = "json";
    ctx.body = {
        name: "码路教育",
        culture: "为学员服务",
    };
});

app.use(router.routes())
router.allowedMethods();

app.listen(3000, () => {
    console.log("running in http://127.0.0.1:3000");
});
