<template>
	<div id="app">
		<h1>App</h1>
		<!-- 下面的三个router-link叫声明式导航 -->
		<router-link to="/home">home</router-link> &nbsp; &nbsp; &nbsp;
		<router-link to="/about">about</router-link> &nbsp; &nbsp; &nbsp;
		<router-link to="/mine">mine</router-link> &nbsp; &nbsp; &nbsp;
		<!-- keep-alive本身也是一个组件 -->
		<!-- 是vue内置好的 -->
		<hr>
		<keep-alive>
			<router-view></router-view>
		</keep-alive>
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
