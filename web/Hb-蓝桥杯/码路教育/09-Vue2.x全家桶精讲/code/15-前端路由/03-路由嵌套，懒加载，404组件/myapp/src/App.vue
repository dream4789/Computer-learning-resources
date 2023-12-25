<template>
	<div id="app">
		<h1>App</h1>
		<router-link to="/home">首页</router-link>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<router-link to="/about">关于</router-link>
		<!-- 
      vue-router插件：
        帮我们提供了四个核心：
          1）router 路由器对象
          2）route 路由对象
          3）router-view  路由出口
          4）router-link  a标签
     -->
		<router-view></router-view>
	</div>
</template>

<script>
	export default {
		name: "App",
		components: {},
	};
</script>

<style lang="less">
	#app {
		font-family: Avenir, Helvetica, Arial, sans-serif;
		-webkit-font-smoothing: antialiased;
		-moz-osx-font-smoothing: grayscale;
		text-align: center;
		color: #2c3e50;
		margin-top: 60px;
	}
</style>
