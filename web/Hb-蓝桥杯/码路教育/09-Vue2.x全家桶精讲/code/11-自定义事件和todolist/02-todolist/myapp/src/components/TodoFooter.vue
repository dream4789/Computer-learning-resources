<template>
	<div class="todo-footer">
		<label>
			<!-- <input type="checkbox" :checked="isAllDone" @change="changeHandler" /> -->
			<input type="checkbox" :checked="todoIsDone.length === todos.length" 
				@change="changeHandler" />
		</label>
		<span>
			<span>已完成{{ todoIsDone.length }}</span> / 全部{{ todos.length }}
		</span>
		<button class="btn btn-danger" @click="clickHandler">清除已完成任务</button>
	</div>
</template>

<script>
	export default {
		name: "TodoFooter",
		props: [
			"updateAllDone",
			"todoIsDone",
			"todos",
			"isAllDone",
			"deleteDoneTodo",
		],
		data() {
			return {};
		},
		methods: {
			// 点击单个todo的checkbox
			changeHandler(e) {
				this.updateAllDone(e.target.checked);
			},
			// 点击清除所有已完成
			clickHandler() {
				this.deleteDoneTodo();
			},
		},
	};
</script>

<style lang="less" scoped>
</style>
