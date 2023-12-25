const Router = require("@koa/router");
const jwtAuth = require("koa-jwt")
const AdminController = require("../controller/AdminController")
const config = require("../config/index.js")

const router = new Router();

router.prefix("/admin")

// router.post("/register", (ctx, next) => {
//     // 按理说，我们需要在这里，得到前端传递过来数据
//     // 连接数据库，插入数据到数据库
//     // ....
//     ctx.body = "注册管理员"
// })

// 注册
router.post("/register", AdminController.register)

// fetch(new Request('http://localhost:3000/admin/register',{
//     method: 'post', 
//     headers: {'Content-Type': 'application/json'},
//     body: JSON.stringify({ nickname: 'admin', password: 'admin000', password2: 'admin000'})
// })).then((resp) => {console.log(resp)})


// 登录 
router.post("/login", AdminController.login)
// fetch(new Request('http://localhost:3000/admin/login',{
//     method: 'post', 
//     headers: {'Content-Type': 'application/json'},
//     body: JSON.stringify({ nickname: 'admin', password: 'admin000'})
// })).then((resp) => {console.log(resp)})


// 获取用户
// http://localhost:3000/admin/user/info   ==> 1
router.get("/user/info", jwtAuth({
	secret: config.security.secretKey
}), AdminController.getUserInfo)


// fetch(new Request('http://localhost:3000/admin/user/info', {
// 	method: 'get',
// 	headers: {
// 		'Authorization': 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJkYXRhIjoiNjNkYmU4NjExYjUwZmMyNDljMTdlNzc1IiwiZXhwIjoxNjc2MjYzMDc3LCJpYXQiOjE2NzU2NTk2Mzd9.yt_uY9ea0WoqNhpVl5wlfN5jvzliCLPPVNZt_2wVbTc'
// 	}
// })).then((resp) => {
// 	console.log(resp)
// })

module.exports = router;
