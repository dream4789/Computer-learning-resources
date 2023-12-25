import Vue from 'vue'
import App from './App.vue'
import router from './router'

// 导入模拟数据
import "../mock/index"

// 导入elementui  全部引入
import ElementUI from "element-ui";
import "element-ui/lib/theme-chalk/index.css"

// 引入重置样式   reset.css和common.css是直接copy过来的
import "./assets/css/reset.css"
import "./assets/css/common.css"

// 引入axios
import axios from "axios";
// 没有对axios进行二次封装
// vm  vc 直接使用$http
Vue.prototype.$http = axios;
// this.$http

// 只是插件，都需要use
Vue.use(ElementUI)

Vue.config.productionTip = false

new Vue({
	router,
	render: h => h(App)
}).$mount('#app')
