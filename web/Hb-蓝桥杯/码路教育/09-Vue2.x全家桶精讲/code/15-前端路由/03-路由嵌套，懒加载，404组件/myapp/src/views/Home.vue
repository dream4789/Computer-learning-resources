<template>
	<div>
		<hr>
		<h1>Home组件</h1>
		<router-link to="/home/person">个人中心</router-link>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<router-link to="/home/setting">设置中心</router-link>
		<router-view></router-view>
	</div>
</template>

<script>
	export default {
		name: "Home",
		props: [],
		data() {
			return {};
		},
		methods: {},
	};
</script>

<style lang="less" scoped>
</style>
