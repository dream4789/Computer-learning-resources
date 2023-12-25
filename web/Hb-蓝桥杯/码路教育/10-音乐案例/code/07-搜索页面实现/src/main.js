import Vue from 'vue'
import App from './App.vue'
import router from './router/index.js'

import axios from 'axios'
// axios.defaults.baseURL = "http://47.94.210.129:3001"
// 前面没有写IP（域名）和端口，就表示向当前服务器发请求
axios.defaults.baseURL = "/api"

Vue.prototype.$http = axios

Vue.directive("height", {
  inserted(el, options) {
    if (typeof options.value == "number") {
      return el.style.height = (window.innerHeight - options.value) + "px";
    } else {
      return el.style.height = (window.innerHeight) + "px";
    }
  }
})


new Vue({
  render: h => h(App),
  router
}).$mount('#app')
