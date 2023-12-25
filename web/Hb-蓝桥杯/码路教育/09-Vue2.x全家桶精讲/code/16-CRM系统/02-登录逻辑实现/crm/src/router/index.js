import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from '../views/Home.vue'
import Login from '../views/Login.vue'

Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    redirect: "/home"
  },
  {
    path: '/home',
    name: 'home',
    component: Home
  },
  {
    path: '/login',
    name: 'login',
    component: Login
  },
]

const router = new VueRouter({
  routes
})

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
