const store = new Vuex.Store({
	state: {},
	modules: {
		// user: () => import('./user.js') // 引入带有命名空间的数据
		// user: () => import('./user.js') ,
		// getters: () => import('./user.js') ,
		
		user: state => state ,
		getters: state => getters ,
	}
})
