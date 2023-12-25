// 每一个文件都是一个模块，模块与模块之间天生隔离
// 要让别人使用数据，需要导出

// 在ESModule中，通过export导出数据
// 导出方案一
// 导出去的并不是一个对象，导出去的是标识符
export let uname = "wc";
export let uage = 18;
export function sayHello() {
    console.log("sayHello...");
}

// commonjs规范
// exports.uname = uname;
// module.exports.uname = uanme;
// module.exports = {uname}



