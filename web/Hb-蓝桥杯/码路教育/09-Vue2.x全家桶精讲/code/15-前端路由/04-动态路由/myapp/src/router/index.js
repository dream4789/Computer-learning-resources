import VueRouter from "vue-router";
import Vue from "vue";
Vue.use(VueRouter)

import Home from "../views/Home.vue"
import About from "../views/About.vue"
import Mine from "../views/Mine.vue"
import NotFound from "../views/NotFound.vue"

let router = new VueRouter({
    mode: "hash",
    routes: [
        { path: "/", redirect: "/home" },
        { path: "/home", component: Home },
        { path: "/about", component: About },
        // :name表示动态参数  需要在组件中获取动态参数
        // { path: "/mine", component: Mine },
        // "/mine/:name?/:age?" 动态参数可传可不传
        { path: "/mine/:name?/:age?", component: Mine },
        { path: "*", component: NotFound },
    ]
})

export default router;

