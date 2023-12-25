const fs = require('fs')
const path = require('path')
const textPath = path.join(__dirname, '/test.md')

// 读取示例文件
fs.readFile(textPath, 'utf8', (err, contrast) => {
	// 通过promisefy转化为链式调用
	const readFileSync = promisefy(fs.readFile)

	readFileSync(textPath, 'utf8')
		.then((res) => {
			console.log(res === contrast) // 此处结果预期：true，即promise返回内容与前面读取内容一致
		})
		.catch((err) => {})
})

const promisefy = (fn) => {
	// TODO 此处完成该函数的封装
	return function(...params) {
		return new Promise((resolve, reject) => {
			fn(...params, (err, data) => {
				if (err) {
					reject(err);
				} else {
					console.log(data)
					resolve(data)
				}
			})
		})
	}
}

module.exports = promisefy // 请勿删除该行代码
