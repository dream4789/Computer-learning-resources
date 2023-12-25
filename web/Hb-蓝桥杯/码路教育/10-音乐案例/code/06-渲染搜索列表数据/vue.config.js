const { defineConfig } = require('@vue/cli-service')
const path = require("path")

function resolve(dir) {
  return path.join(__dirname, dir)
}

module.exports = defineConfig({
  transpileDependencies: true,
  // 只有浏览器的ajax才有跨域问题
  // script标签中src  img标签中的src... 是没有跨域问题   JSONP
  // 解决：1）通过浏览器插件解决（有时候不靠谱） 2）通过代理解决   3）后端解决

  // 使用代理解决跨域  代码不需要记，用的时候，直接能copy
  // devServer就是开发服务器
  // 如果你动了vue.vonfig.js，你需要重启开发服务器
  // 说白了，后面开发项目，以及在公司开发项目，在开发过程中，基本上都会使用代理解决跨域
  // 代理解决跨域仅仅是在开发期间使用，项目上线，使用其它跨域解决方案
  devServer: {
    // 配置代理解决跨域
    proxy: {
      "/api": {
        // 拦截下后，需要告诉代理，应该请求的服务器是谁
        target: "http://47.94.210.129:3001",
        changeOrigin: true,
        // http://47.94.210.129:3001/api/personalized?limit=6  这个地址我们是不能得到数据的
        // 多了一个api，接口是错的，所以数据还是回不来
        // http://47.94.210.129:3001/personalized?limit=6
        pathRewrite: {
          "^/api": ""
        }
      }
    }
  },
  chainWebpack: (config) => {
    // 第一参数@$代表别名，第二个参数代表替代的开始路径
    config.resolve.alias.set("@$", resolve('src'))
  }
})
