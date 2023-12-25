import helloWorld from "./page/helloWorld.js";

var app = new Vue({
	el: "#app",

	components: {
		helloWorld: helloWorld
	},

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
			// 已知数据，请勿修改。
			data1: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
			data2: ["a", "b", "c", "d", "e", "f", "g"],
			data3: ["H", "E", "L", "L", "O", " ", "W", "O", "R", "L", "D"],
		};
	},

	methods: {
		// 请完成下列函数，并且绑定到对应的子组件 *
		sumIt: (data) => {
			return data.reduce((sum, current) => {
				sum += current;
				return sum;
			});
		},
		// 补全reverseIt，使其能完成：传入data数组，返回倒置的data数组。 *
		reverseIt: (data) => {
			return data.reverse();
		},

		// 补全displayIt，使其能完成：传入data数组，返回“HELLO WORLD”的功能。 *
		displayIt: (data) => {
			return data.join('');
		},
	},
});
