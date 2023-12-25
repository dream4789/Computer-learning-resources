import Vue from 'vue'
import App from './App.vue'

Vue.config.productionTip = false

// 自定义全局指令
// 全局指令，那意味着在所有的组件中都可以使用
Vue.directive("upper", (element, options) => {
  element.innerHTML = options.value.toUpperCase();
})

Vue.directive("focus", {
  // 这里，也是有一些生命周期函数
  // 当绑定的元素挂载到DOM树上时，会自动调用
  inserted(element) {
    // console.log("inserted");
    element.focus();  // 自动获取焦点
  }
})

new Vue({
  render: h => h(App),
}).$mount('#app')
