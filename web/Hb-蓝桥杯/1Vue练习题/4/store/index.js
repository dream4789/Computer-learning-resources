import "../js/vuex.js";
import data from "./data.js";

var store = new Vuex.Store({
	modules: {
		data,
	},
});

export default store;
