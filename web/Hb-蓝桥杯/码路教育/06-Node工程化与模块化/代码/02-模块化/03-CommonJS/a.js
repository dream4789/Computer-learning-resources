let name = "wc";
let age = 18;
function sayHello() {
    console.log("sayHello...");
}

// module 模块的意思  module.exports是正儿八经导出数据
// modules.xx = xx;  不是正儿八经导出数据
// console.log(module);

// 导出的方案一：开发中不常用
// exports.name = name;
// exports.age = age;
// exports.sayHello = sayHello;

// 导出的方案二：开发中不常用
// 源码中：exports和module.exports指向了同一个堆
// exports(地址) = module.exports(地址)
// console.log(exports === module.exports);
// module.exports.name = name;
// module.exports.age = age;
// module.exports.sayHello = sayHello;

// console.log(exports.name);
// console.log(exports.age);

// 导出的方案三：开发中常用
// module.exports是正儿八经导出数据
// 让module.exprots指向了新堆
// module.exports = {
//     name,
//     age,
//     sayHello
// }
// exports还是指向老堆，此时，module.exports和exports没有关系了
// console.log(exports);  // {}

// 问：如下的导出是否OK
// exports(地址) = module.exports(地址)
// 答：不OK，因为，正经导出数据是通过 module.exports
// 如果让exports指向新堆，数据是没有办法导出去的
// exports = {
//     name,
//     age,
//     sayHello
// }

// --------------------------------------

// 导出数据的方式：
//     方式一：
//          exprots.a = a;
//          exprots.b = b;
//     方式二：
//          module.exprots.a = a;
//          module.exprots.b = b;
//     方式三：
//          module.exprots = {a,b}
