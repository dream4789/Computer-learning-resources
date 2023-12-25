const Koa = require("koa");
const app = new Koa();

// 1
// app.use(async (ctx, next) => {
//     console.log(1);
//     await next();
//     console.log(5);
// })
// app.use(async (ctx, next) => {
//     console.log(2);
//     await next();
//     console.log(4);
// })
// app.use(async (ctx, next) => {
//     console.log(3);
//     ctx.body = "hello koa~"
// })

// 2
const one = (ctx, next) => {
  console.log('>> one');
  next();
  console.log('<< one');
}

const two = (ctx, next) => {
  console.log('>> two');
  next();
  console.log('<< two');
}

const three = (ctx, next) => {
  console.log('>> three');
  next();
  console.log('<< three');
}
app.use(one);
app.use(two);
app.use(three);
// >> one
// >> two
// >> three
// << three
// << two
// << one



app.listen(3000)
