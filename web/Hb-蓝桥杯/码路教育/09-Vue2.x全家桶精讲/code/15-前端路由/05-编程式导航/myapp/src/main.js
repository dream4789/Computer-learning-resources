import Vue from 'vue'
import App from './App.vue'

import router from "./router/index.js"

Vue.config.productionTip = false

// vue-router四个核心：
//    两个组件
//       router-view
//       router-link
//    两个对象
//       router   有很多的方法
//           go  back  push
//       route    有很多属性
//          .....
new Vue({
  router,
  render: h => h(App),
}).$mount('#app')
