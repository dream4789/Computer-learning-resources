
// {} 不是对象，也不是结构赋值，{}中放标识符列表
// import { uname, uage, sayHello } from "./a.js"
// console.log(uname);
// console.log(uage);
// sayHello();

// ------------------------

// 如果给标识符起别名，只能使用别名
import { uname as username, uage as userage, sayHello } from "./a.js"

console.log(uname);
console.log(username);
console.log(userage);