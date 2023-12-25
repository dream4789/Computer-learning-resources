const Koa = require("koa");
const index = require("./router/index.js")
const bodyParser = require('koa-bodyparser')
const static = require('koa-static');

const app = new Koa();

app.use(bodyParser());
app.use(static(__dirname + '/public'))

app.use(index.routes())
index.allowedMethods();


app.listen(3000, () => {
    console.log("server is running on 3000");
})


