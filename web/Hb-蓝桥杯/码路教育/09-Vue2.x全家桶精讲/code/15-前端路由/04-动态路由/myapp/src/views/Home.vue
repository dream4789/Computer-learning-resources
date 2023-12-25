<template>
	<div>
		<h2>Home</h2>
	</div>
</template>

<script>
	// 组件进入到出口就活了
	// 组件离开出口就死了
	// 计算属性：缓存数据
	// keep-alive: 缓存组件
	export default {
		name: "Home",
		props: [],
		beforeCreate() {
			console.log("home组件活了");
		},
		data() {
			return {};
		},
		destroyed() {
			console.log("home组件死了");
		},
		methods: {},
	};
</script>

<style lang="less" scoped>
</style>
