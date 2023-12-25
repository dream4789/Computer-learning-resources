<template>
	<div>
		<button @click="login">登录</button>
	</div>
</template>

<script>
	export default {
		name: "MyComponent2",
		props: [],
		data() {
			return {};
		},
		methods: {
			login() {
				// 点击登录给GO挂载isLogin是true
				window.isLogin1 = true;
				console.log('登陆成功！');
			},
		},
	};
</script>

<style lang="less" scoped>
</style>
