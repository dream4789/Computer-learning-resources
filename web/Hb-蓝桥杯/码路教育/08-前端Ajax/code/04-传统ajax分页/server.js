const Koa = require("koa");
const cors = require("koa2-cors");
const logger = require("koa-logger");
const Router = require("@koa/router");
const koaBody = require("koa-body");
const MongoClient = require('mongodb').MongoClient
const app = new Koa();
const router = new Router();

app.use(cors());
app.use(logger());
// app.use(koaBody());

const client = new MongoClient('mongodb://127.0.0.1:27017')
// 链接服务端
client.connect()
console.log('链接成功')

// 获取数据库 
const db = client.db('newsDB')
// 获取集合
const grade1 = db.collection('news')

router.get("/news", async ctx => {

    let page = ctx.query.page || 1;
    (page <= 0) && (page = 1)

    let pageSize = ctx.query.pageSize;
    let r = await grade1
        .find()
        .skip((page - 1) * pageSize)
        .limit(+pageSize)
        .toArray()

    let total = await grade1.find().count();
    let size = Math.ceil(total / pageSize) // size表示一共有多少页

    ctx.body = {
        news: r,
        total: total,
        pageSize,
        page,
        size
    }
    // 关闭客户端的链接
    // client.close()
})

app.use(router.routes())
router.allowedMethods();

app.listen(3000, () => {
    console.log("running in http://127.0.0.1:3000");
});
