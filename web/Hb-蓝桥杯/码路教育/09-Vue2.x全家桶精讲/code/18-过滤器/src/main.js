import Vue from 'vue'
import App from './App.vue'

Vue.config.productionTip = false

// 定义一个全局的过滤器
Vue.filter("moneyFormat", (params) => {
  return "￥" + params;
})

new Vue({
  render: h => h(App),
}).$mount('#app')
