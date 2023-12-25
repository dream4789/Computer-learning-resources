// index.js是入口，在这里，可以导入其它模块中的数据
// import { formatDate } from "./format.js"
// import { formatMoney } from "./parse.js"

// export {
//     formatDate,
//     formatMoney
// }

// -------------------------------------

// 优化一
// export { formatDate } from "./format.js"
// export { formatMoney } from "./parse.js"

// -------------------------------------

// 优化二
export * from "./format.js"
export * from "./parse.js"