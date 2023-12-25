<template>
  <div class="todo-container">
    <div class="todo-wrap">
      <!-- <todo-header :addTodo="addTodo1"></todo-header> -->
      
      <!-- :addTodo="addTodo" 自定义属性 -->
      <!-- @addTodo="addTodo" 自定义事件 -->
      <!-- 当addTodo这个事件发生了，就会调用后面的addTodo -->
      <!-- 通过$emit让addTodo事件发生了 -->
      <todo-header @addTodo="addTodo1"></todo-header>
      <todo-main
        :todos="todos"
        :deleteTodo="deleteTodo"
        :updateDone="updateDone"
      ></todo-main>
      <todo-footer
        :updateAllDone="updateAllDone"
        :todoIsDone="todoIsDone"
        :todos="todos"
        :isAllDone="isAllDone"
        :deleteDoneTodo="deleteDoneTodo"
      ></todo-footer>
    </div>
  </div>
</template>

<script>
import TodoHeader from "./components/TodoHeader.vue";
import TodoMain from "./components/TodoMain.vue";
import TodoFooter from "./components/TodoFooter.vue";
export default {
  name: "App",
  props: [],
  data() {
    return {
      // todos: [
      //   { id: "01", title: "学习vue", done: true },
      //   { id: "02", title: "学习小程序", done: false },
      //   { id: "03", title: "学习react", done: false },
      // ],
      todos: JSON.parse(localStorage.getItem("TODO")) || [],
    };
  },
  methods: {
    // 删除todo
    deleteTodo(id) {
      this.todos = this.todos.filter((item) => (item.id == id ? false : true));
    },

    // 添加todo
    addTodo1(todo) {
		console.log(todo);
      let repeat = this.todos.find((item) => item.title === todo.title);
      !repeat && this.todos.push(todo);
    },

    // 更新todo的done
    updateDone(id, done) {
      this.todos = this.todos.map((todo) =>
        todo.id == id ? { ...todo, done } : todo
      );
    },

    // 全选或反选
    updateAllDone(done) {
      this.todos = this.todos.map((todo) => ({ ...todo, done }));
    },

    // 清除所有已完成
    deleteDoneTodo() {
      this.todos = this.todos.filter((todo) => !todo.done);
    },
  },
  computed: {
    // 统计已完成的数据
    todoIsDone() {
      return this.todos.filter((todo) => todo.done);
    },
    // 所有的todo是否已完成
    isAllDone() {
      return this.todos.every((todo) => todo.done);
    },
  },
  watch: {
    todos() {
      localStorage.setItem("TODO", JSON.stringify(this.todos));
    },
  },
  components: {
    TodoHeader,
    TodoMain,
    TodoFooter,
  },
};
</script>

<style lang="less" scoped>
</style>