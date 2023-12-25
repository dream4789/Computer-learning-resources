import "../js/vue-router.js";
import Home from "../page/Home.js";
import Login from "../page/Login.js";

var router = new VueRouter({
	// 请修改routes内容实现target.gif中的效果 *
	routes: [
		{ name: '/', path: "/", redirect: "/Home",}, 
		{ name:'Home', path: "/Home", component: Home,}, 
		{ name:'Login', path: "/Login", component: Login,}, 
	],
});

router.beforeEach((to, from, next) => {
	alert(`从${from.fullPath}跳转到${to.fullPath}`);
	next();
});

export default router;
