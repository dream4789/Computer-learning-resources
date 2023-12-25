<template>
	<div>
		<el-menu default-active="1-1" class="el-menu-vertical-demo">
			<el-submenu index="1">
				<template slot="title">
					<i class="el-icon-location"></i>
					<span>管理</span>
				</template>
				<el-menu-item index="1-1"><span @click="handleClick('/home/user')">用户管理</span></el-menu-item>
				<el-menu-item index="1-2"><span @click="handleClick('/home/teacher')">老师管理</span></el-menu-item>
				<el-menu-item index="1-3"><span @click="handleClick('/home/role')">角色管理</span></el-menu-item>
			</el-submenu>
		</el-menu>
	</div>
</template>

<script>
	export default {
		name: "MenuBar",
		props: [],
		data() {
			return {};
		},
		methods: {
			handleClick(path) {
				this.$router.push(path);
			},
		},
	};
</script>

<style lang="less" scoped>
</style>
