<template>
	<div class="todo-header">
		<input type="text" placeholder="请输入你的任务名称，按回车键确认" @keyup.enter="enterHandler" />
	</div>
</template>

<script>
	export default {
		name: "TodoHeader",
		// props: ["addTodo"],
		data() {
			return {};
		},
		methods: {
			enterHandler(e) {
				if (e.target.value.trim() === "") {
					alert("输入的内容不能为空！！！")
					return;
				}

				let newTodo = {
					id: Date.now(),
					title: e.target.value,
					done: false
				};
				// 下面的代码是调用父传递过来的方法
				// this.addTodo(newTodo);

				this.$emit("addTodo", newTodo)

				e.target.value = ""; // 清空输入框
			}
		},
	};
</script>

<style lang="less" scoped>
</style>
