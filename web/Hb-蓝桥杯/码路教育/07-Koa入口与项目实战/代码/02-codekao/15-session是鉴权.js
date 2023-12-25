// 登录接口   登录成功后，得到的用户信息
// 退出登录接口   如果退了登录了，不能得到用户信息
// 获取用户信息接口

// 也就是说，有些接口，只有在你登录的情况下，才能访问
// 所谓的登录就是身份认证，身份认证就是鉴权

const Koa = require("koa");
const session = require('koa-session');
const bodyParser = require('koa-bodyparser')
const user = require("./router/user.js")
const app = new Koa();

// post请求获取数据
app.use(bodyParser());

app.keys = ['some secret hurr'];
const SESSION_CONFIG = {
    key: 'wc', //设置cookie的key名字
    maxAge: 86400000, //有效期，默认是一天
    httpOnly: true, //仅服务端修改
    signed: true, //签名cookie
}
app.use(session(SESSION_CONFIG, app))

// 注册路由
app.use(user.routes())
user.allowedMethods();


app.listen(3000, () => {
    console.log("server is running on 3000");
})

