import helloWorld from "./page/helloWorld.js";

var app = new Vue({
	el: "#app",

	components: { helloWorld: helloWorld },

	// 请修改、补全此处代码 *
	template: `
    <div id="root">
        <helloWorld :data="data1" :handle="sumIt"/>
        <helloWorld :data="data2" :handle="reverseIt"/> 
        <helloWorld :data="data3" :handle="displayIt"/> 
    </div>
    `,

	data() {
		return {
			data1: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
			data2: ["a", "b", "c", "d", "e", "f", "g"],
			data3: ["H", "E", "L", "L", "O", " ", "W", "O", "R", "L", "D"],
		};
	},

	methods: {
		// 请完成下列函数，并且完成绑定到子组件
		sumIt: (data) => {
			return data.reduce((sum, current) => {
				sum += current;
				return sum;
			});
		},
		reverseIt: (data) => {
			return Array.from(data).reverse();
		},
		displayIt: (data) => {
			return data.join("");
		},
	},
});
