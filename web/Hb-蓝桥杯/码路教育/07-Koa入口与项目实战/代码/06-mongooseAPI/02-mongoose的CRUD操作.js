const mongoose = require('mongoose');
// demo表示数据库名字，如果没有，会自动创建
mongoose.connect('mongodb://127.0.0.1:27017/blog', {
	useNewUrlParser: true,
	useUnifiedTopology: true 
});

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

// -----------------------------------------

let userSchema = new mongoose.Schema({
    name: String,
    age: Number
})

let User = mongoose.model("yonghu", userSchema)

// 添加一个文档
// User.create({ name: "wc", age: 18 }, (err, res) => {
//     if (!err) {
//         console.log("插入成功");
//         console.log(res);
//     }
// })

// ---------------------------------------------

// 添加多个文档
// User.create([
//     { name: "xq", age: 18 },
//     { name: "dw", age: 19 },
//     { name: "ok", age: 20 },
// ], (err, res) => {
//     if (!err) {
//         console.log("插入成功");
//         console.log(res);
//     }
// })

// ---------------------------------------------

// User.create([
//     { name: "xq", age: 18 },
//     { name: "dw", age: 19 },
//     { name: "ok", age: 20 },
// ]).then(res => {
//     console.log("res:",res);
// })

// ---------------------------------------------

// ;(async function () {
//     let res = await User.create([
//         { name: "xq", age: 18 },
//         { name: "dw", age: 19 },
//         { name: "ok", age: 20 },
//     ]);
//     console.log("res:", res);
// })()

// ---------------------------------------------

// User.find({}, (err, res) => {
//     if (!err) {
//         console.log(res);
//     }
// })

// ---------------------------------------------

// User.find({name:"xq"}, (err, res) => {
//     if (!err) {
//         console.log(res);
//     }
// })

// ---------------------------------------------

// _id:0 表示查询出来的结果中不要有_id
// User.find({ name: "xq" }, { _id: 0, __v: 0, age: 0, name: 0 }, (err, res) => {
//     if (!err) {
//         console.log(res);
//     }
// })

// ---------------------------------------------

// ; (async function () {
//     let res = await User.find({ name: "xq" }, { _id: 0, __v: 0, age: 0 });
//     console.log("res:", res);
// })()

// ---------------------------------------------

// ; (async function () {
//     let res = await User.find({}, { _id: 0, __v: 0 }, { limit: 3 });
//     console.log("res:", res);
// })()

// ---------------------------------------------

// ; (async function () {
//     let res = await User.find({}, { _id: 0, __v: 0 }, { skip: 3, limit: 3 });
//     console.log("res:", res);
// })()

// ---------------------------------------------

// User.update({ name: "dw" }, { $set: { age: 100 } }, (err, res) => {
//     if (!err) {
//         console.log("更新成功");
//         console.log(res);
//     }
// })

// ---------------------------------------------

// User.update({ name: "dw" }, { $set: { age: 100 } }, { multi: true }, (err, res) => {
//     if (!err) {
//         console.log("更新成功");
//         console.log(res);
//     }
// })

// ---------------------------------------------

// User.deleteOne({ name: "dw" }, (err, res) => {
//     if (!err) {
//         console.log("删除成功");
//         console.log(res);
//     }
// })

// ---------------------------------------------

User.remove({ name: "dw" }, (err, res) => {
    if (!err) {
        console.log("删除成功");
        console.log(res);
    }
})


