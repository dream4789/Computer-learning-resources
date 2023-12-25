<template>
	<div>
		<hr>
		<h5>个人中心</h5>
		<router-link to="/home/person/cart">购物车</router-link>
		&nbsp;&nbsp;&nbsp;&nbsp;
		<router-link to="/home/person/address">地址管理</router-link>
		<router-view></router-view>
	</div>
</template>

<script>
	export default {
		name: "Person",
		props: [],
		data() {
			return {};
		},
		methods: {},
	};
</script>

<style lang="less" scoped>
</style>
