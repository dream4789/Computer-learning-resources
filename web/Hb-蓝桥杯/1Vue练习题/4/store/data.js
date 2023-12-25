export default {
	namespaced: true,
	state: {
		// 待初始化
		list: [{name: "张三",gender: 1,age: 20}],
	},
	mutations: {
		init(state) {
			//初始化数据，在这里作为中介请求后端数据，调用actions中的封装的api调用函数。
			//请补充完善，在此调用actions中的getData并且将接受到的数据处理后放到state中的list上完成数据绑定和渲染。
			//todo *
			// console.log('-----------',typeof JSON.stringify(this.state.data.list));
			// this.dispatch('getData');
			// this.state.data.dispatch('getData');
		},
	},
	actions: {
		getData(context) {
			//模拟请求后端数据
			return new Promise((resolve) => {
				let data = [
					{name: "张三",gender: 1,age: 20,},
					{name: "李四",gender: 0,age: 19,},
					{name: "王五",gender: 0,age: 21,},
					{name: "老六",gender: 1,age: 26,},
					{name: "陈七",gender: 1,age: 22,},
					{name: "王八",gender: 1,age: 28,},
				];
				// console.log(this.list);  不正确,this指的是全局
				this.state.data.list = data;
				// console.log(this.state.data.list);
				// console.log(JSON.stringify(this.state.data.list));
				// context.commit('init');
				setTimeout(() => {
					resolve(data);
				}, 1000);
			});
		},
	},
	getters: {},
};
