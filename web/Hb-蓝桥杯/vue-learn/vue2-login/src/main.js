import Vue from 'vue'
import App from './App.vue'

import ElementUI from 'element-ui'; // 2.1引入结构
import 'element-ui/lib/theme-chalk/index.css'; // 2.2引入样式

// 导入路由器对象
import router from "./router/index.js"


Vue.config.productionTip = false

Vue.use(ElementUI); // 3.安装

new Vue({
	router,
	render: h => h(App),
}).$mount('#app')
