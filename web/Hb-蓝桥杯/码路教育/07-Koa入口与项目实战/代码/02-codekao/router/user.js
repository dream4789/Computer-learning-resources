const Router = require("@koa/router");
const jwt = require("jsonwebtoken")
const jwtAuth = require("koa-jwt")

const router = new Router();

router.prefix("/user")

const secret = "12345678adfghjkl;ertyui7￥%……&*&……%4"

// 登录
router.post("/login-token", (ctx, next) => {
	// 1）得到用户信息
	let userinfo = ctx.request.body.user;
	console.log("userinfo:", userinfo);

	// 2）根据用户信息生成token
	let token = jwt.sign({
	    data: userinfo,  // 不要存放敏感数据 
	    exp: Math.floor(Date.now() / 1000) + 60 * 60 // 1个不时后，令牌就失效了
	}, secret);
	console.log("token:", token);

	// 3）给客户端响应数据
	ctx.body = {
		ok: 1,
		message: "登录成功",
		user: userinfo,
		token: jwt.sign({
			data: userinfo, // 不要存放敏感数据 
			exp: Math.floor(Date.now() / 1000) + 60 * 60 // 1个不时后，令牌就失效了
		}, secret)
	}
})

// 登出
router.post("/logout", (ctx, next) => {

})

// 用户信息
router.get("/getUser-token", jwtAuth({
	secret
}), async (ctx, next) => {
	ctx.body = {
		message: "获取用户令牌",
		userinfo: ctx.state.user.data
	}
})

// 第三方登录
//    自学一下
// 短信登录 
//    用的也比较多

module.exports = router;

// 常见的鉴权方案
//   一：session鉴权
//   二：jwt+token鉴权
//   三：第三方登录（自学）
//   四：短信登录
//   五：扫码登录
