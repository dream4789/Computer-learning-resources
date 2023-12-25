
// C:\Users\admin\Desktop\Node工程化与模块化\代码
// console.log(__dirname);

// C:\Users\admin\Desktop\Node工程化与模块化\代码\index.js
// console.log(__filename);

// process本意是进程  提供了进程中相关的信息，如：node运行环境，传递参数..
// console.log(process);

// JS = ES + DOM + BOM
// node是JS（ES）的运行环境

// setTimeout  setInterval  setImmediate
// console.log("start...");
// 证明setImmediate是宏任务
// setTimeout 和 setImmediate 谁先执行不好说
// setImmediate(() => {
//     console.log("setImmediate");
// })
// setTimeout(() => {
//     console.log("setTimeout");
// }, 0)
// console.log("end...");


// console.log("start...");
// setImmediate(() => {
//     console.log("setImmediate...");
// })
// // nextTick中的回调是微任务
// process.nextTick(() => {
//     console.log("nextTick...");
// })
// console.log("end...");

// console.log(global);
// console.log(globalThis === global);

// 在node中定义的全局变量，并不会挂载到global上
var a = 110;
console.log(global.a);