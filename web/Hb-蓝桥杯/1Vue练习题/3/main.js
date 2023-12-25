import "./js/vue.js";
import router from "./router/index.js";

var app = new Vue({
	router,
	el: "#app",
	template: `
        <div>
            <router-link to="./"> / </router-link>
            <router-link to="./Home"> Home </router-link>
            <router-link to="./Login"> Login </router-link> 
			
			<router-view></router-view>
        </div>
    `,
});
