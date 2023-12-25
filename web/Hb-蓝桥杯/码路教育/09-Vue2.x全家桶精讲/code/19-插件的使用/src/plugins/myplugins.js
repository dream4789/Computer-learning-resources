
// 开发一个插件，就是一个JS文件
// 插件：给项目提供全局功能
// 如：vue-router
//     安插了插件，就提供四个核心：
//     1）view-router  view-link
//     2）$router  $route
// 如：vuex
//    安装了插件，就提供了$store

// Vue规定，你要定义一个插件，必须要有install方法
// 当使用插件时，要调用use方法，use时，它内部就会调用install方法
let plugins = {
    // 参数一：Vue构造器
    // 参数二：就是use时传递的参数
    install(Vue, options) {
        // console.log("install...");
        console.log("options:", options);

        // 封装一个自定义指令到插件中
        Vue.directive("upper", (element, options) => {
            element.innerHTML = options.value.toUpperCase();
        })

        // 封装一个过滤器指令到插件中
        Vue.filter("moneyFormat", (params) => {
            return "￥" + params;
        })

        // 可以给Vue原型对象上，添加公共的方法
        Vue.prototype.$ml = function () {
            alert("欢迎来到码路学习~")
        }

        // 注册全局的组件
        Vue.component("ml-count", {
            data() {
                return {
                    count: 0
                }
            },
            methods: {
                add() {
                    this.count++
                },
                sub() {
                    this.count--
                }
            },
            render(createElement) {
                return createElement('h1', {}, '我是Count组件')
            }
        })
    }
}

// 对外需要暴露插件，为了让别人使用
export default plugins;



