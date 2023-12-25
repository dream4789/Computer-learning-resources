/**
 * @description:
 * @param {*} str
 * @param {*} rule
 * @param {*} symbol
 * @param {*} dealPhone
 * @return {*}
 */
const toDesensitization = (str, rule, symbol = "*", dealPhone = true) => {
	if (!str) {
		return null;
	} else if (!rule) {
		return str;
	} else {
		// let a = {
		// 	"ids": [],
		// 	"newStr": ""
		// }
		// console.log(typeof rule)
		// if (typeof rule == 'string') {

		// 	let sy = symbol.repeat(rule.length)
		// 	// console.log(sy)


		// 	a["newStr"] = str.replace(rule, sy);
		// 	// console.log(b)

		// 	let newStr = str.replace(pattern, (e, index) => {
		// 	    ids.push(index)
		// 	    return symbol.repeat(e.length)
		// 	})
		// } else {
		// }

		// return a;

		let pattern = new RegExp(Array.isArray(rule) ? rule.join("|") : rule, 'g')
		let ids = []

		let newStr = str.replace(pattern, (e, index) => {
			ids.push(index)
			return symbol.repeat(e.length)
		})

		if (dealPhone) {
			let pattern = /\d{3}(.+)\d{3}/g
			newStr = newStr.replace(pattern, (a, $1) => {
				return a.replace($1, "*".repeat($1.length))
			})
		}

		return {
			ids,
			newStr
		}
	}
};



let str = '人的一生，好不好只有自己知道，乐不乐只有自己明白。快乐是一种心情，一种自然、积极向上的心态。在平凡之中寻求快乐，在磨难之中寻求快乐，在曲折之中需求快乐。'
let rule = '向上'

console.log(toDesensitization(str, rule))

// module.exports = toDesensitization;


// 函数传递参数，输出 {ids: [1], newStr: '开*每一天'}
// toDesensitization("开心每一天", ["心"], "*", false);
