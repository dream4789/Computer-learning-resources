// import { name, age, sayHello } from "./a.js"
// console.log(name);
// console.log(age);
// sayHello();

// -------------------------------
// let flag = true;

// if (flag) {
//     // import导入不能放到条件中，只能位于一个模块最前面
//     import { name, age, sayHello } from "./a.js"
//     console.log(name, age);
// }

// -------------------------------

// let flag = true;

// if (flag) {
//     // 如果确实需要根据不同的条件，加载不同的模块，使用import函数
//     let res = import("./b.js");
//     res.then(value => {
//         console.log(value.name,value.age);
//     }).catch(err => {
//         console.log(err);
//     })
// }

// -------------------------------

// let flag = true;

// if (flag) {
//     // 如果确实需要根据不同的条件，加载不同的模块，使用import函数
//     let res = await import("./a.js");
//     console.log(res.name);
//     console.log(res.age);
// }

// -------------------------------

let flag = true;

if (flag) {
    try {
        let res = await import("./b.js");
        console.log(res.name);
        console.log(res.age);
    } catch (err) {
        console.log(err);
    }
}

