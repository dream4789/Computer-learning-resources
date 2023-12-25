import Vue from 'vue'
import App from './App.vue'
import "./assets/fonts/iconfont.css"
import "bootstrap/dist/css/bootstrap.css"

Vue.config.productionTip = false

Vue.directive("focus", {
  inserted(el) {
    el.focus()
  }
})


new Vue({
  render: h => h(App),
}).$mount('#app')
