import VueRouter from "vue-router";
import Vue from "vue";
Vue.use(VueRouter)

// 直接加载两个组件，不管是否匹配到，组件都加载了
// import Home from "../components/Home.vue"
// import About from "../components/About.vue"

// 懒加载：当路径匹配到了，再去加载组件
// 一上来，并不会加载所有组件，首页面是直接加载的
// 对于Aobut组件来说，当点击about连接，匹配到对应的路径时，再进行加载About组件
// 通过imput函数实现懒加载
// import Home from "../components/Home.vue"

// let router = new VueRouter({
//     mode: "hash",
//     routes: [
//         // 在路由中配置的组件，叫路由组件
//         // 对于路由组件来说，通常在项目中并不是放在components文件夹
//         // 路由组件通常会放在views或pages文件下
//         // 在components文件夹下，通常放一些可以复用的，没有配置路由的组件
//         { path: "/", redirect: "/home" },
//         { name: "home", path: "/home", component: Home },
//         { name: "about", path: "/about", component: () => import("../components/About.vue") },
//         { name: "notfount", path: "*", component: () => import("../components/NotFount.vue") },
//     ]
// })

// ----------------------------------------------------------

// import Home from "../views/Home.vue"

// let router = new VueRouter({
//     mode: "hash",
//     routes: [
//         // 在路由中配置的组件，叫路由组件
//         // 对于路由组件来说，通常在项目中并不是放在components文件夹
//         // 路由组件通常会放在views或pages文件下
//         // 在components文件夹下，通常放一些可以复用的，没有配置路由的组件
//         { path: "/", redirect: "/home" },
//         { name: "home", path: "/home", component: Home,
//             children: [
//                 { path: "/home", redirect: "/home/person" },
//                 { path: "/home/person", component: () => import("../views/Person.vue"),
//                     children: [
//                         { path: "/home/peron", redirect: "/home/person/cart" },
//                         { path: "/home/person/cart", component: () => import("../views/Cart.vue") },
//                         { path: "/home/person/address", component: () => import("../views/Address.vue") },
//                     ]
//                 },
//                 { path: "/home/setting", component: () => import("../views/Setting.vue") },
//             ]
//         },
//         { name: "about", path: "/about", component: () => import("../views/About.vue") },
//         { name: "notfount", path: "*", component: () => import("../views/NotFount.vue") },
//     ]
// })


// ----------------------------------------------------------


import Home from "../views/Home.vue"

let router = new VueRouter({
    mode: "hash",
	
	
    routes: [
        // 在路由中配置的组件，叫路由组件
        // 对于路由组件来说，通常在项目中并不是放在components文件夹
        // 路由组件通常会放在views或pages文件下
        // 在components文件夹下，通常放一些可以复用的，没有配置路由的组件
		{ path: "/", redirect: "/home" },  // 1
		{ name: "home", path: "/home",  component: Home,  // 1 --> 2 自动定向此页
			children: [
				// { path: "/home", redirect: "/home/person" },  // 2 --> 3 自动定向此页
                { path: "home", redirect: "/home/person" },
                { path: "person", component: () => import("../views/Person.vue"),
                    children: [
                        { path: "person", redirect: "/home/person/cart" },
                        { path: "cart", component: () => import("../views/Cart.vue") },
                        { path: "address", component: () => import("../views/Address.vue") },
                    ]
                },
                { path: "setting", component: () => import("../views/Setting.vue") },
            ]
        },
        { name: "about", path: "/about", component: () => import("../views/About.vue") },
        { name: "notfount", path: "*", component: () => import("../views/NotFount.vue") },
    ],
	
	
	// 自第一级以下的每一级都要设置 redirect，如果本级 redirect 和下一级 path 对应，则页面会定向到下一级的 redirect
	// routes: [
	//   { path: "/", redirect: "/home" },  // 1
	//   { name: "home", path: "/home",  component: Home,  // 1 --> 2 
	//     children: [
	// 			{ path: "/home", redirect: "/home/person" },  // 2 --> 3 
	//       { path: "person", component: () => import("../views/Person.vue"),
	//         children: [
	// 					{ path: "/home/person", redirect: "/home/person/cart" },  // 进入/person自动定向到/cart
	//           { path: "cart", component: () => import("../views/Cart.vue") },
	//         ]
	//       }
	//     ]
	//   }
	// ]
})

export default router;

