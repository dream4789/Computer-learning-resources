<template>
	<div>
		<h2>Mine</h2>
		<p>{{ $route.params.name }}</p>
		<p>{{ $route.params.age }}</p>
	</div>
</template>

<script>
	export default {
		name: "Mine",
		props: [],
		created() {
			// 四个核心：
			//    两个组件
			//    两个对象  router  route
			console.log(this.$route.params.name);
			console.log(this.$route.params.age);
		},
		data() {
			return {};
		},
		methods: {},
	};
</script>

<style lang="less" scoped>
</style>
