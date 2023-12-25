<template>
  <ul class="todo-main">
    <li
      v-for="(todo, index) in todos"
      :key="todo.id"
      @mouseenter="enterHander(index)"
      :class="{ active: currentIndex === index }"
    >
      <label>
        <input type="checkbox" :checked="todo.done" @change="changeHandler(todo,$event)" />
        <span>{{ todo.title }}</span>
      </label>
      <button
        class="btn btn-danger"
        v-show="todo.done"
        @click="delHandler(todo.id)"
      >
        删除
      </button>
    </li>
  </ul>
</template>

<script>
export default {
  name: "TodoMain",
  props: ["todos", "deleteTodo", "updateDone"],
  data() {
    return {
      currentIndex: -1,
    };
  },
  methods: {
    // 鼠标移入
    enterHander(index) {
      this.currentIndex = index;
    },
    // 点击删除按钮
    delHandler(id) {
      this.deleteTodo(id);
    },
    // 点击todo的checkbox
    changeHandler(todo,e){
      this.updateDone(todo.id, e.target.checked)
    }
  },
};
</script>

<style lang="less" scoped>
.active {
  color: yellowgreen;
  background-color: #eee;
}
</style>