import Vue from 'vue'
import App from './App.vue'

// 导入路由器对象
import router from "./router/index.js"

Vue.config.productionTip = false

new Vue({
  router, // 挂载到根上，就意味着子子孙孙都可以使用路由器对象的 
  render: h => h(App),
}).$mount('#app')
