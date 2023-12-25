const Router = require("@koa/router");
const router = new Router();
router.prefix("/user")

//  //bodyparser()会解析路由和请求体的参数，在注册路由前引入则无法解析之后的路由参数和请求体，所以就得不到请求体参数


// --------------------------------------------------

// 列出所有信息 get
// http://localhost:3000/user

// ---------------------------------------------------

// router.get("/list", ctx => {
//     ctx.body = "用户列表"
// })

// router.get("/add", ctx => {
//     ctx.body = "添加用户"
// })

let users = [{
	id: 1,
	name: "wc",
	age: 18
}, {
	id: 2,
	name: "xq",
	age: 28
}]

// 根据前端传递的 name，得到用户信息
// 1）parmas  2)query     /user?name=wc
router.get("/", ctx => {
	let name = ctx.query.name;
	console.log(name);
	let data = users;
	if (name) {
		data = users.filter(u => u.name === name)
	}
	ctx.body = {
		ok: 1,
		data
	}
})
// http://localhost:3000/user?name=wc


// /user/1
router.get("/:id", ctx => {
	let id = ctx.params.id;
	console.log("id:", id);
	console.log(typeof id);
	let data = users;
	if (id) {
		data = users.filter(u => u.id === +id)
	}
	ctx.body = {
		ok: 1,
		data
	}
})
// http://localhost:3000/user/1


// 添加用户的
router.post("/", ctx => {
	let name = ctx.request.body.username;
	let age = ctx.request.body.userage;
	let id = users.length + 1
	let user = {
		id,
		name,
		age
	};
	users.push(user);
	ctx.body = {
		ok: 1,
		message: "添加用户成功"
	}
})
// fetch(new Request('http://localhost:3000/user/',{
//     method: 'post', 
//     headers: {'Content-Type': 'application/json'},
//     body: JSON.stringify({ username: 'aa', userage: 18})
// })).then((resp)=>{console.log(resp)})

// fetch(new Request('http://localhost:3000/user/',{
//     method: 'post', 
//     headers: {'Content-Type': 'application/x-www-form-urlencoded'},
//     body: new URLSearchParams({ username: 'aa', userage: 18}).toString()
// })).then((resp)=>{console.log(resp)})

// fetch('http://localhost:3000/user/', {
// 	method: 'POST',
// 	headers: {'Content-Type': 'application/x-www-form-urlencoded'},
// 	body: 'username=aa&userage=18'
// }).then((resp) => {
// 	console.log(resp)
// })


// 修改用户
router.put("/", ctx => {
	let id = +ctx.request.body.id;
	const idx = users.findIndex(u => u.id === id);
	if (idx > -1) {
		users[idx].name = ctx.request.body.name;
		users[idx].age = ctx.request.body.age;
	}
	ctx.body = {
		ok: 1,
		message: "修改成功"
	}
})
// fetch(new Request('http://localhost:3000/user/',{
//     method:'put', 
//     headers: {'Content-Type': 'application/json'},
//     body:JSON.stringify({ id: 3, name:'bb', age: 20})
// })).then((resp)=>{console.log(resp)})


// 删除用户  /user/1
router.delete("/:id", ctx => {
	let id = +ctx.params.id;
	const idx = users.findIndex(u => u.id === id);
	console.log("idx:", idx);
	if (idx > -1) {
		users.splice(idx, 1)
	}
	ctx.body = {
		ok: 1,
		message: "删除成功"
	}
})
// fetch(new Request('http://localhost:3000/user/4',{
//     method:'delete', 
//     headers: {'Content-Type': 'application/x-www-form-urlencoded'},
//     body:"1111"
// })).then((resp)=>{console.log(resp)})


module.exports = router;


// https://blog.csdn.net/riant110/article/details/121973815
