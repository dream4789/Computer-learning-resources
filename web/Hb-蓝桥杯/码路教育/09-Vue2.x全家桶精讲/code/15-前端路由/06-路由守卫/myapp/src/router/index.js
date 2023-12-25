import VueRouter from "vue-router";
import Vue from "vue";
Vue.use(VueRouter)

import Home from "../views/Home.vue"
import About from "../views/About.vue"
import Mine from "../views/Mine.vue"
import Login from "../views/Login.vue"
import NotFound from "../views/NotFound.vue"

let router = new VueRouter({
    mode: "hash",
    routes: [
        { path: "/", redirect: "/home" },
        { name: "home", path: "/home", component: Home },
        { name: "about", path: "/about", component: About },
        { name: "mine", path: "/mine", component: Mine },
        { name: "login", path: "/login", component: Login },
        { name: "notfound", path: "*", component: NotFound },
    ]
})

// 全局守卫
// 路由守卫
// 组件内守卫


// 全局路由守卫  
router.beforeEach((to, from, next) => {
    console.log(to.path);
    if (to.path !== "/login") {
        if (window.isLogin1) {
            // 说明已登录 
            next();
        } else {
            // 没有登录 
            return next("/login")
        }
    }
    next();
})

export default router;

