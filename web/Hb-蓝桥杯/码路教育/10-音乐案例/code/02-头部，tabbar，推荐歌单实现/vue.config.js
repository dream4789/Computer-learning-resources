const { defineConfig } = require('@vue/cli-service')
const path = require("path")

function resolve(dir) {
  return path.join(__dirname, dir)
}

module.exports = defineConfig({
  transpileDependencies: true,
  chainWebpack: (config) => {
    // 第一参数@$代表别名，第二个参数代表替代的开始路径
    config.resolve.alias.set("@$", resolve('src'))
  }
})
