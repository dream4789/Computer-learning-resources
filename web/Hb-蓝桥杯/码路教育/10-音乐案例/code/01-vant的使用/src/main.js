import Vue from 'vue'
import App from './App.vue'
import router from './router/index.js'

// 引入vant  引入全部组件
// import Vant from 'vant';
// import 'vant/lib/index.css';
// Vue.use(Vant);

import axios from 'axios'
Vue.prototype.$http = axios



new Vue({
  render: h => h(App),
  router
}).$mount('#app')
