// cookie和session都是用来记录数据的
//     cookie数据存储在浏览器中，session数据是存储在服务器端
// cookie
//     大王要去喝咖啡，咖啡馆有一个活动，喝10杯，送1杯
//         积分卡   cookie是由服务器种植
//         cookie
// session
//     大王要去喝咖啡，咖啡馆有一个活动，喝10杯，送1杯
//         在咖啡馆记录信息   给大王一个会员号   大王只需要记住会员号
//         会员号会以cookie的形式种植的客户端   会员号还是保存在cookie中的
//         每一次去喝咖啡都需要报会员号  
//         session是基于cookie
// jwt+token

const Koa = require("koa");
const user = require("./router/user.js")
const bodyParser = require('koa-bodyparser')
const app = new Koa();

app.use(bodyParser());

app.use(user.routes())
user.allowedMethods();

app.listen(3000, () => {
    console.log("server is running on 3000");
})

