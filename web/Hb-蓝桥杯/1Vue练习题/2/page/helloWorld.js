import "../js/vue.js";

export default Vue.component("helloWorld", {
	props: ["data", "handle"],
	template: `<h2 :style="styles">{{computedData}}</h2>`,
	data() {
		return {
			styles: {
				margin: "12px",
				padding: "6px",
				"background-color": "#99e9f2",
			},
		};
	},
	computed: {
		computedData() {
			return this.$props.handle(this.$props.data);
		},
	},
});
