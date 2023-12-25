const Router = require("@koa/router");

const router = new Router();

router.prefix("/cart")

router.get("/", (ctx, next) => {
    ctx.body = "购物车列表"
})

router.get("/add", (ctx, next) => {
    ctx.body = "添加购物车"
})

module.exports = router;

// http://localhost:3000/cart
// http://localhost:3000/cart/add


