<template>
	<div>
		<h2>Home</h2>
		<button @click="toAbout">去about页</button>
		<button @click="forward">前进</button>
		<button @click="()=>this.$destroy()">销毁</button>
	</div>
</template>

<script>
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
		methods: {
			toAbout() {
				// push里面跟了一个字符串
				// http://localhost:8080/#/about
				// {{$route.params.address}} ==> undefind
				// this.$router.push("/about");  // 1
				// this.$router.push({ path: "/about" });  // 2

				// 跳转并{{传参}}
				// http://localhost:8080/#/about
				// {{$route.params.address}} ==> bj1
				// this.$route.query.address ==> undefined
				// this.$router.push({
				// 	name: "about",
				// 	params: {
				// 		address: "bj1"
				// 	}
				// });

				// 跳转并传参
				// http://localhost:8080/#/about/bj2 未注册页面
				// this.$router.push({ path: "/about/bj2" });

				// 跳转并传参
				// http://localhost:8080/#/about?address=bj3
				// {{$route.params.address}} ==> undefined
				// this.$route.query.address ==> bj
				this.$router.push({
					name: "about",
					query: {
						address: "bj3"
					}
				});

				// 跳转并传参
				// http://localhost:8080/#/about?address=bj
				// {{$route.params.address}} ==> undefined
				// this.$route.query.address ==> bj4
				// this.$router.push({
				// 	path: "/about",
				// 	query: {
				// 		address: "bj4"
				// 	}
				// });
			},
			forward() {
				// this.$router.forward();  // 前进（在此之前有过前进动作）
				this.$router.go(1);  // 同上
			},
		},
	};
</script>

<style lang="less" scoped>
</style>
