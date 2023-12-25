import Vue from 'vue'
import vueRouter from 'vue-router'

Vue.use(vueRouter)

// 阻止重复点击报错
// const originalPush = vueRouter.prototype.push;
// vueRouter.prototype.push = function push(location) {
//     return originalPush.call(this, location).catch(err => err);
// }


const router = new vueRouter({
    routes: [
        {
            path: "/",
            redirect: "/home"
        },
        {
            path: '/home',
            name: 'home',
            component: () =>
                import('@/views/Home/index.vue')
        },
        {
            path: '/player',
            name: 'player',
            component: () =>
                import ('@/views/Player')
        },
        {
            path: '*',
            redirect: '/home'
        }
    ]
})

export default router