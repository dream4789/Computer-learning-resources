// user.js
const state = {
	name: 'zhangsan',
	age: 20
}
const getters = {
	getName: state => state.name
}
// module.exports = {
// 	namespaced: true, // 命名空间
// 	state,
// 	getters
// }
