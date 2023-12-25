import "./js/vue.js";
import store from "./store/index.js";

var app = new Vue({
	store,
	el: "#app",
	template: `
        <div class="box"> 
            <div class="info" v-for="(item,index) in $store.state.data.list"> 
                <div>姓名：{{item.name}}</div>
                <div>性别：{{item.gender}}</div>
                <div>年龄：{{item.age}}</div>
            </div>
        </div>
    `,
	// 请在下方三个生命周期钩子中的最合理的位置补充数据初始化代码，只需要在其中之一补充即可。
	//todo *
	created() {
		this.$store.commit("data/init");
	},
	mounted() {},
	beforeDestroy() {},
});
