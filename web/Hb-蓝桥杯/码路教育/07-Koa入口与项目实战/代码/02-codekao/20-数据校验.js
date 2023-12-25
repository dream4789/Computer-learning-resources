const Koa = require("koa");
const index = require("./router/index.js")
const bouncer = require("koa-bouncer")
const bodyParser = require('koa-bodyparser')

const app = new Koa();

app.use(bodyParser());
app.use(bouncer.middleware());

app.use(index.routes())
index.allowedMethods();


app.listen(3000, () => {
    console.log("server is running on 3000");
})


