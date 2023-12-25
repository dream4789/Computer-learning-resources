import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)

const routes = [
	// 登录页
	{
		path: '/',
		name: 'Login',
		component: () => import('../views/Login/Login.vue'),
	},
	// 首页
	{
		path: '/Home',
		name: 'Home',
		component: () => import('../views/Home/Home.vue'),
		// children: [
		// 	// 新建报表
		// 	{
		// 		path: '/Home/NewReport',
		// 		name: 'NewReport',
		// 		component: () => import('../views/Home/NewReport.vue')
		// 	},
		// ]
	},
]


// router.post('/Login', () => {
	
// })

const router = new VueRouter({
	routes
})

// 导航守卫
// 使用 router.beforeEach 注册一个全局前置守卫，判断用户是否登陆
router.beforeEach((to, from, next) => {
	//如果去往登录页则放行 
	if (to.path === '/') {
		next();
	} else {
		// 从本地存储里获取token
		let token = localStorage.getItem('token');
		// 判断token是否为空如果为空则跳转到登录页 如果有则放行
		if (token === null || token === '') {
			next({
				path: '/'
			});
		} else {
			next();
		}
	}
});

export default router
