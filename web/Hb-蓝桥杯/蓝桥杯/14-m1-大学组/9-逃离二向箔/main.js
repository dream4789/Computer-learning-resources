// const jsdom = require("jsdom");
// const { JSDOM } = jsdom;
// const dom = new JSDOM(`<!DOCTYPE html><p>Hello world</p>`);
// window = dom.window;
// document = window.document;

// 使用 promise 模拟请求 + 3000ms后完成得到发射后结果
function createRequest(i) { // 发射飞船请求的 promise。
	return function() {
		return new Promise((resolve, reject) => {
			const start = Date.now();
			setTimeout(() => {
				if (Math.random() >= 0.05) {
					resolve(
						`第${i + 1}艘曲率飞船达到光速，成功逃离，用时${Date.now() - start}`
					);
				} else {
					reject(
						`第${i + 1}艘曲率飞船出现故障，无法达到光速，用时${Date.now() - start}`
					);
				}
			}, 3000 + i * 100);
		});
	};
}

class RequestControl {
	constructor({
		max,
		el
	}) {
		this.max = max;
		this.requestQueue = [];
		this.el = document.querySelector(el);
		setTimeout(() => {
			this.requestQueue.length > 0 && this.run();
		});
		this.startTime = Date.now();
	}
	addRequest(request) { // 收集飞船发射请求，将飞船发射请求放入 this.requestQueue 发射队列中
		this.requestQueue.push(request);
	}
	async run() { // 实现依据发射结果自动排配下一批次的飞船发射
		// TODO：待补充代码
		console.log("run");
		let waitArr = [];
		for (let i = 0; i < this.requestQueue.length; i++) {
			waitArr.push(
				this.requestQueue[i]()
				.then(res => {
					// console.log("飞船发射成功");
					this.render(res) // 打印信息
					waitArr.shift() // 删除数组的第一个元素
				})
				.catch(err => {
					// console.log("飞船发射失败");
					this.render(err); // 打印信息
					waitArr.shift()
				})
			)
			if (waitArr.length === this.max) {
				await Promise.race(waitArr)
			}
		}
	}

	render(context) { // 在页面渲染每次飞船发射结果
		const childNode = document.createElement("li");
		childNode.innerText = context;
		this.el.appendChild(childNode);
	}
}

let requestControl = new RequestControl({
	max: 10, // 飞船最大发射数量
	el: "#app"
});
for (let i = 0; i < 25; i++) {
	const request = createRequest(i);
	requestControl.addRequest(request);
}


// module.exports = {
// 	requestControl,
// };
