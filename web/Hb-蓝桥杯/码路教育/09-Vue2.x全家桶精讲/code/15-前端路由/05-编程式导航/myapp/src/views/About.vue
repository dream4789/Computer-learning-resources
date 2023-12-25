<template>
	<div>
		<h2>About</h2>
		<p>{{ $route.params.address }}</p>
		<button @click="back">返回</button>
	</div>
</template>

<script>
	export default {
		name: "About",
		props: [],
		created() {
			// console.log(this.$route.params.address);
			console.log(this.$route.query.address);
		},
		data() {
			return {};
		},
		methods: {
			back() {
				// this.$router.back();
				this.$router.go(-1);
			},
		},
	};
</script>

<style lang="less" scoped>
</style>
