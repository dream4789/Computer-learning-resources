<template>
	<div>
		<el-link icon="el-icon-switch-button" @click="tuichu">退出登录</el-link>
	</div>
</template>

<script>
	export default {
		methods: {
			// 退出
			tuichu() {
				//退出登录，清空token
				localStorage.removeItem('token');
				this.$router.push({
					name: "Login"
				});
			},
		},
	};
</script>


<style>
</style>
