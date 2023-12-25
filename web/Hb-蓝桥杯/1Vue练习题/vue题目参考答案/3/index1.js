import "../js/vue-router.js";
import Home from "../page/Home.js";
import Login from "../page/Login.js";

var router = new VueRouter({
	routes: [
		{
			path: "/",
			redirect: "/Home",
		},
		{
			path: "/Home",
			component: Home,
		},
		{
			path: "/Login",
			component: Login,
		},
	],
});

export default router;
