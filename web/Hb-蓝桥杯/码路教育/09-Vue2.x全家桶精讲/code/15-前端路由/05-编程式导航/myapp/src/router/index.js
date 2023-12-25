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
        { name: "home", path: "/home", component: Home },
        // { name: "about", path: "/about/:address", component: About },
        { name: "about", path: "/about", component: About },
        { name: "mine", path: "/mine", component: Mine },
        { name: "notfound", path: "*", component: NotFound },
    ]
})

export default router;

