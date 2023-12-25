
// 在ESModule中导入是通过import xxx from xxx

// 如果是自定义模块，必须以./或../打头
// { }  不叫结构赋值  不叫结构赋值， {}中放标识符
// import {} from "./a.js"
import { uname, uage, sayHello } from "./a.js"
import { uage as age } from "./b.js"

console.log(uname, uage, sayHello);
// console.log(uage);
console.log(age);

