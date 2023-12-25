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

// data表示服务器端的所有的数据
let data = require("./cityData.min.json")

// 响应所有的省份
router.get("/province", (ctx) => {
    let province = [];
    data.forEach(item => {
        // item代表每一个省的所有数据
        province.push(item.n)
    })
    // json有两种形式：1）对象的形式 2）数组的形式
    ctx.body = province; // 响应给xhr一个json字符串  ["北京市","河南省","河北省"...]
})

// 根据省份，响应对应的市
router.get("/city", (ctx) => {
    let province = ctx.query.province;
    let cities = [];
    data.forEach(item => {
        if (item.n === province) {
            item.s.forEach(item1 => {
                cities.push(item1.n)
            })
        }
    })
    ctx.body = cities
})

app.use(router.routes())
router.allowedMethods();

app.listen(3000, () => {
    console.log("running in http://127.0.0.1:3000");
});
