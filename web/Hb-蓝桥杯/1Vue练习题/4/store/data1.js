export default {
	namespaced: true,
	state: {
		// 待初始化
		list: [],
	},
	mutations: {
		init(state) {
			//初始化数据，在这里作为中介请求后端数据，调用actions中的封装的api调用函数。
			//请补充完善，在此调用actions中的getData并且将接受到的数据处理后放到state中的list上完成数据绑定和渲染。
			//todo *
			this.dispatch("data/getData").then((res) => {
				let temp = res.map((item) => {
					item["gender"] = item["gender"] == 0 ? "女" : "男";
					return item;
				});
				state.list = temp;
			});
		},
	},
	actions: {
		getData() {
			//模拟请求后端数据
			return new Promise((resolve) => {
				let data = [
					{
						name: "张三",
						gender: 1,
						age: 20,
					},
					{
						name: "李四",
						gender: 0,
						age: 19,
					},
					{
						name: "王五",
						gender: 0,
						age: 21,
					},
					{
						name: "老六",
						gender: 1,
						age: 26,
					},
					{
						name: "陈七",
						gender: 1,
						age: 22,
					},
					{
						name: "王八",
						gender: 1,
						age: 28,
					},
				];
				setTimeout(() => {
					resolve(data);
				}, 1000);
			});
		},
	},
	getters: {},
};
