import "./js/vue.js";
import "./js/axios.js";

var app = new Vue({
	el: "#app",
	template: `
        <div class="box">
            {{list}}
        </div>
    `,
	data() {
		return {
			list: [],
		};
	},
	created() {
		//请使用axios的get请求向后端请求数据（请先按要求开启后端进程）
		//url: http://127.0.0.1:1145/api/list
		//携带参数:  page:1, limit:6
		//todo *
		axios
			.get("http://127.0.0.1:1145/api/list", {
				params: { page: 1, limit: 10 },
			})
			.then((res) => {
				this.list = res.data.join("-");
			});
	},
});
