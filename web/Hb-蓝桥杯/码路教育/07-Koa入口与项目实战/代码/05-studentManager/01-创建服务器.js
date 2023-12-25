const Koa = require("koa");
const bodyParser = require('koa-bodyparser')
const Router = require("@koa/router")
const static = require('koa-static');
const mongod = require("./db/index.js")
const ObjectId = require("mongodb").ObjectId;

// 解决跨域
const cors = require('koa2-cors');


const app = new Koa();
const router = new Router();

// 使用中间件
app.use(bodyParser());
// app.use(cors());

// 解决跨域
app.use(async (ctx, next) => {
  ctx.set("Access-Control-Allow-Origin", "*")
  ctx.set("Access-Control-Allow-Headers", "authorization")
  await next()
})

// 托管静态资源（静态网页）
app.use(static(__dirname + '/public'))

router.get("/", ctx => {
	ctx.body = "首页面"
})

// 获取所有的学生
// http://localhost:3000/api/classList
// http://localhost:3000/api/classList?pageSize=1&pageIndex=3
router.get("/api/classList", async ctx => {
	let {
		pageSize,
		pageIndex
	} = ctx.query;
	pageSize = Number(pageSize)
	pageIndex = Number(pageIndex)

	console.log("pageSize:", pageSize);
	console.log("pageIndex:", pageIndex);

	// 得到students集合
	let students = mongod.col("students");

	// 得到所有的学生
	let classList = await students.find().skip((pageIndex - 1) * pageSize).limit(pageSize).toArray();
	console.log("classList:", classList);
	let total = await students.countDocuments();

	ctx.body = {
		ok: 1,
		data: classList,
		total
	}
})

// 删除某个学生
router.post("/api/deleteUser", async ctx => {
	let _id = ctx.request.body._id;
	console.log("---------------_id:", _id);
	let students = mongod.col("students");
	let res = await students.deleteOne({
		_id: ObjectId(_id)
	})
	console.log("res:", res);
	if (res.deletedCount == 1) {
		ctx.body = {
			ok: 1,
			msg: "删除成功"
		}
	}
})

// fetch(new Request('http://localhost:3000/api/deleteUser',{
//     method: 'post', 
//     headers: {'Content-Type': 'application/json'},
//     body: JSON.stringify({ _id: '63d67d4f8dde1318e433fd6d'})
// })).then((resp) => {console.log(resp)})


// app.use(bodyParser());  // 一样的
app.use(router.routes()).use(router.allowedMethods());

// app.use(router.allowOrgins())

app.listen(3000, () => {
	console.log("server is running on 3000");
})
