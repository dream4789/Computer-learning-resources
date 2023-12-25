// "use strict"

// 1）不能使用没有加var的全局变量
// uname = "wc";
// console.log(uname);

// 2）在严格模式下形参不能重名
// function fn(x, y, z, x) {
//     console.log(x, y, z, x);
// }
// fn(1, 2, 3, 4)

// 3）不能使用老的8进制数据的写法
// let num1 = 0x123; // 16进制
// let num2 = 0o10; // 8进制
// let num3 = 010;  // 8进制 (老的写法)
// console.log(num1,num3);

// 4）不能使用with语句
// let obj = { msg: "hello" }
// with (obj) {
//     console.log(msg);
// }

// 5）在严格模式下，JS串中定义的数据，外界不能使用
// 外界定义的数据，在JS串中还是可以使用
// let msg = "hello";
// let jsStr = "var a = 110; console.log(a); var b = 666;";
// eval(jsStr)
// console.log(b);

// 6）在非严格模式下，this是window  在严格模式下，不会默认绑定，this是und
// 独立函数调用，this不再表示window，是und
// function fn() {
//     console.log(this);
// }
// fn();

// ......

// 在某个函数中开启严格模式
// function fn() {
//     "use strict";  // 只会约束函数内部的代码
//     a = 110;
//     console.log(a);
// }
// // fn();

// b = 666;
// console.log(b);

// -------------------- 
function gn() {
    a = 123;
    console.log(a);
}
function fn() {
    "use strict";
    gn();
}
fn();
