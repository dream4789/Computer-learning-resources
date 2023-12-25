// RestfulAPI
//   说白了，就是url的设计风格

// get  /students   获取所有的学生
// post /students   新增一个学生
// get  /students/:id    获取某个学生的信息
// put  /students/:id   修改某个学生信息(提供学生所有的信息)
// patch   /students/:id    修改某个学生信息(提供学生部分的信息)
// delete  /students/:id   删除某一个学生
// get    /class/id/students   获取某个班级中的所有学生
// delete  /class/id/students/id    删除某个班级中的某个学生

// post  /createUser  // createUser不是名字  错误的
// post  /deleteuser   错误的

// post  /user   正确的
// delete /user  正确的

// get  /books
// get  /book

// GET /authors/2/categories/2  获取ID=2的作者 的 分类=2的文章
// GET /authors/2?categories=2

// GET /articals
// GET /articals/published   获取所有的已发布的文章
// GET /articals?published=true   获取所有的已发布的文章


const Koa = require("koa");
const bodyParser = require('koa-bodyparser')

const index = require("./router/index");
const user = require("./router/user");

const app = new Koa();

app.use(bodyParser());  // 路由接受参数

// 注册路由
app.use(index.routes());
index.allowedMethods();

app.use(user.routes());
user.allowedMethods();

// app.use(bodyParser());  // 路由不接受参数

app.listen(3000, () => {
    console.log("服务器在3000端口运行起来了~");
})