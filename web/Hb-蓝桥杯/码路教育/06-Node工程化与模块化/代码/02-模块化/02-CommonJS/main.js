// ./必须写  因为a.js这个模块是你开发的
// 你开发的模块，叫自定义模块，自定义模块必须以./或../打头
// console.log(require("./a.js"));  // { name: 'wc' }

// let obj = require("./a.js");
// console.log(obj.name);

// -------------------------------------

// let obj = require("./b.js");
// console.log(obj.address);

// -------------------------------------

// let obj = require("./utils");
// console.log(obj.PI);
// console.log(obj.formatTime());
// console.log(obj.sum(1, 2));

// // 第1次require时，会把对应的模块中的代码都执行一次
// // 得到结果会放到缓存中，当你再去require时，会从缓存中取结果，对应的模块不会再执行
// require("./utils");
// require("./utils");
// require("./utils");

// -------------------------------------

// let obj = require("./b.js");
// console.log(obj.address);
