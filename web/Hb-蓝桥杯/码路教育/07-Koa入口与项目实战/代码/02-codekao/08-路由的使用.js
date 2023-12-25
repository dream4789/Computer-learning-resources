const Koa = require("koa");
const index = require("./router/index.js")
const user = require("./router/user.js")
const cart = require("./router/cart.js")

const app = new Koa();

// 注册首页模块路由
app.use(index.routes())
index.allowedMethods();

// 注册用户模块路由
app.use(user.routes())
user.allowedMethods();

// 注册用户模块路由
app.use(cart.routes())
cart.allowedMethods();


app.listen(3000, () => {
    console.log("server is running on 3000");
})

// http://localhost:3000/cart
// http://localhost:3000/cart/add

// http://localhost:3000/xxx
