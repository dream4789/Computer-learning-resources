/**
 * @description: 数据类型检测
 * @param {*} data 传入的待检测数据
 * @return {*} 返回数据类型
 */
function getType(data) {
	// TODO：待补充代码
	// var a = Object.prototype.toString;
	// return a.call(data).slice(8, -1);

	// typeof可区分除了null类型以外的原始数据类型（nudefined、number、string、symbol、boolean）和对象类型中的函数，针对其他类型时typeof一律返回object
	if (typeof data !== "object") {
		return typeof data;
	}
	// object.protrtype.tostring.call能够满足大部分场景下的需求，但是无法区分数字类型和数字对象类型
	return Object.prototype.toString.call(data);
}


module.exports = {
	getType
}
