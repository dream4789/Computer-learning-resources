import Vue from 'vue'
import App from './App.vue'
import store from '../store';
 
new Vue({
    el: '#app',
    i18n,
    router,
    store, // 挂载
    render: h => h(App),
    template: '<App/>'
});

Vue.config.productionTip = false

// new Vue({
// 	store,
// 	render: h => h(App),
// }).$mount('#app')
