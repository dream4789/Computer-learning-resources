const mongoose = require('mongoose');
// demo表示数据库名字，如果没有，会自动创建
mongoose.connect('mongodb://127.0.0.1:27017/demo', {
	useNewUrlParser: true,
	useUnifiedTopology: true 
});

// 定义模式
const db = mongoose.connection;

// 订阅  error是一个事件
db.on("error", (err) => {
	console.log(err, "连接失败");
})
// on表示一直绑定  once表示一次绑定
db.once("open", () => {
	console.log("连接成功");
})
db.once("close", () => {
	console.log("断开连接");
})


// Schema 定义文档中的数据结构  约束文档是什么样的
let userSchema = new mongoose.Schema({
	name: String,
	age: Number
})

// 需要根据Schema创建model
// model 模型
// MVC   Model数据模型，主要是给数据库打交道   View视图，前端写的页面   Controller控制器

// User 说白了，就是对应数据库中的集合，数据中可以有N个集合，一个集合中可以有N个文档   
let User = mongoose.model("User", userSchema);
// 第一个参数是为模型所创建集合的别名（Mongoose 将为 User 模型创建数据库集合），第二个参数是创建模型时使用的模式。

// user1就是对应mongod中的文档 
let user1 = new User({
	name: "wc",
	age: 18
});

user1.save((err, user) => {
	if (!err) {
		console.log("文档保存成功");
		console.log(user);
	}
})


// --------------------------------------

// eat是一个自定义事件
// 需要写代码去触发自定义事件
// emit("eat","123")  发布
// db.on("eat",(data)=>{lg("xxx")})  订阅

// --------------------------------------

/* <button id="btn">点我</button>
// 原生DOMAPI
btn.onclick = function (e) { };
btn.addEventListener("click", (e) => { })
// JQ
$("#btn").click(function () { })
// on可以绑定事件  也可以实现事件委托
$("#btn").on("click", function () { }) */
