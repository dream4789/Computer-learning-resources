import Vue from 'vue'
import App from './App.vue'

Vue.config.productionTip = false

import myplugins from "./plugins/myplugins"
// 当你去use时，字会自动调用插件中的install方法
Vue.use(myplugins, { name: "upper" })


new Vue({
  render: h => h(App),
}).$mount('#app')
