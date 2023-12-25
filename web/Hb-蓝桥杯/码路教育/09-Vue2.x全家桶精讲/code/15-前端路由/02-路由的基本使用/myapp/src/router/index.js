import VueRouter from "vue-router";
import Vue from "vue";

// 只要是插件，都是use
// vue插件的原理  
Vue.use(VueRouter)

import Home from "../components/Home.vue"
import About from "../components/About.vue"

// router表示路由器对象
let router = new VueRouter({
    // mode指定使用什么样的路由模式
    // hash  history
    mode: "hash",

    // route 表示路由  一个路由器中可以管理N个路由
    // 一个路由，就是一个配置对象
    routes: [
        // name表示路由对象的名字，独一无二的
        // path表示路由，不需要加#
        // component表示匹配到的组件，匹配的组件，需要放到路由出口中
        { name:"home", path: "/home", component: Home },
        { name:"about",path: "/about", component: About },
    ]
})

// 导出路由器对象
export default router;


// 路由的使用：
//   1）安装  vue-router@3.5.3
//   2）在src下，创建一个router文件   下面创建index.js
//   3）new出来一个路由器对象并导出
//   4）路由器中可以配置很多路由规则
//   5）在main.js中，引入路由器对象，并挂载到根上
//      vue-router帮我们提供了四个核心： 两个组件 两个对象
//        A）router   B）route   C）router-view  D）router-link
//   6）路由对象中的匹配的规则中匹配到的组件需要放到路由出口中
//   7）需要提供路由跳转的连接