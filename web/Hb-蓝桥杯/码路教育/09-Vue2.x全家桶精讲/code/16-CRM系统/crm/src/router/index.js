import Vue from 'vue'
import VueRouter from 'vue-router'

import Home from '../views/Home.vue'
import Login from '../views/Login.vue'
import User from '../views/User.vue'
import Teacher from '../views/Teacher.vue'
import Role from '../views/Role.vue'

Vue.use(VueRouter)

const routes = [
  { path: '/', redirect: "/home" },
  { path: '/home', name: 'home', component: Home,
    children: [
      { path: "/home", redirect: "/home/user" },
      { path: "/home/user", component: User },
      { path: "/home/teacher", component: Teacher },
      { path: "/home/role", component: Role },
    ]},
  { path: '/login', name: 'login', component: Login},
]

const router = new VueRouter({
  routes
})

const VueRouterPush = VueRouter.prototype.push
VueRouter.prototype.push = function push (to) {
	return VueRouterPush.call(this, to).catch(err => err)
}

// 全局守卫
router.beforeEach((to, from, next) => {
  if (to.path == "/login") {
    if (sessionStorage.getItem("username")) {
      // 去登录,但是登录过了
      router.push("/home")
    } else {
      // 去登录,但是没有登录 
      next();
    }
  }
  // 去的不是登录页面
  if (sessionStorage.getItem("username")) {
    // 登录了,去/home
    next();
  } else {
    router.push("/login")
  }
})

export default router
