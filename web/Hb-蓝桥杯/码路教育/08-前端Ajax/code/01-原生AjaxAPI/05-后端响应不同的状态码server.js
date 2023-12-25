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

router.post("/status/500", async (ctx, next) => {
    ctx.status = 500;
    ctx.body = 500;
});

router.post("/status/503", async (ctx, next) => {
    ctx.status = 503;
    ctx.body = 503;
});

router.post("/status/403", async (ctx, next) => {
    ctx.status = 403;
    ctx.body = 403;
});

router.post("/status/404", async (ctx, next) => {
    ctx.status = 404;
    ctx.body = {
        ok: 1
    };
});

app.use(router.routes())
router.allowedMethods();

app.listen(3000, () => {
    console.log("running in http://127.0.0.1:3000");
});
