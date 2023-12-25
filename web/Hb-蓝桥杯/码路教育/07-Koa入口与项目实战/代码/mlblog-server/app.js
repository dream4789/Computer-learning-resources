const Koa = require("koa");
const app = new Koa();

// 美化json
const json = require("koa-json");
// 接收post参数
const bodyparser = require("koa-bodyparser");
// 控制台美化日志
const logger = require("koa-logger");
// 前端表单校验
const bouncer = require("koa-bouncer");
// 托管静态资源
const static = require("koa-static")
// 解决跨域
const cors = require('koa2-cors');

// 引用项目的配置文件
const config = require("./config");
// 导入连接数据库文件
const db = require("./db");
// 检查出对应的参数错误、404错误、权限错误、xxx已存在的错误可以这样使用
// 如：throw new global.errs.Existing('管理员已存在')
// errors是一个对象，这个对象中包含了6个类，其中有一个是Existing类
const errors = require("./core/http-exception");
// 当出现任何的错误时，我们需要错误处理中间件来处理  exception是错误处理中间件
const catchError = require("./middlewares/exception");

// 路由的引入
const user = require("./router/user.js")
const admin = require("./router/admin.js")
const category = require("./router/category.js")
const article = require("./router/article.js")
const comment = require("./router/comment.js")
const reply = require("./router/reply.js")
const advertise = require("./router/advertise.js")

// 把errors挂载到GO的errs这个属性上
// GO的属性上有一个errs属性，值是一个对象，对象中有6个类
global.errs = errors;
// 把config挂载到GO，用的时候，直接global.config，到时候就不用导入
global.config = config;
// node app.js PORT=5000
// node app.js 没有传参  process.env.PORT是und  整体的值是config.port
// config.port就是3000
const port = process.env.PORT || config.port;

// 错误处理中间件
app.use(catchError);

// 使用中间件
app
  .use(bodyparser())
  .use(bouncer.middleware())
  .use(json())
  .use(logger())
  .use(cors())
  .use(static(__dirname + '/public'))

// 日志打印中间件
app.use(async (ctx, next) => {
  const start = new Date();
  await next();
  const ms = new Date() - start;
  console.log(`${ctx.method} ${ctx.url} - $ms`);
});

// 路由注册
app.use(user.routes())
user.allowedMethods();

// 注册管理员模块的路由
app.use(admin.routes())
admin.allowedMethods();

// 注册分类模块的路由
app.use(category.routes())
category.allowedMethods();

// 注册文章模块的路由
app.use(article.routes())
article.allowedMethods();

// 注册评论模块的路由
app.use(comment.routes())
comment.allowedMethods();

// 注册回复模块的路由
app.use(reply.routes())
reply.allowedMethods();

// 注册广告模块路由
app.use(advertise.routes());
advertise.allowedMethods();

// 无效
// app.use(cors({
//     origin: 'http://127.0.0.1', //webpack打包后会生成index.html和static目录，我直接放在本地启动的nginx静态目录html下用来运行webpack打包文件，所以Origin地址为http://127.0.0.1 
//     allowedHeaders: 'Origin, x-requested-with, Content-Type, X-Token', //X-Token为自定义的头字段
//     credentials: true //设置成true 请求中才会带上cookie信息，否则请求失败
// }));

// 绑定error事件
app.on("error", function (err, ctx) {
  console.log(err)
  // logger.error('server error', err, ctx)
});

module.exports = app.listen(config.port, () => {
  console.log(`Server is running on ${config.port}`);
});
