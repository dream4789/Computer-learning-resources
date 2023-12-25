<template>
  <div>
    <!-- 
        前面学习了很多指令：
            v-html
            v-text
            v-model
            v-if
            v-show
            v-elseif
            v-else
            v-for
            v-bind
            v-on
            v-clock
            v-pre
            v-once
            ...

        组件：
            代码复用

        自定义指令：
            程序员自己发生的指令，通常是对DOM进行底层操作。

        自定义指令：
            1）自定义局部指令：只能在当前组件中使用
            2）自定义全局指令：在任意组件中都可以
       -->
    <h2>MyComponent1组件</h2>
    <p>{{ msg }}</p>
    <!-- 使用时，必须加v- -->
    <p v-upper="msg"></p>
    <p v-upper="name"></p>
  </div>
</template>

<script>
export default {
  name: "MyComponent1",
  props: [],
  data() {
    return {
      msg: "hello malu",
      name: "hello nihao",
    };
  },
  methods: {},
  //自定义局部指令
  directives: {
    // 自定义指令，也是一个函数
    // 定义时，不需要加v-
    // 参数一：表示你这个指令所有的DOM元素
    // 参数二：当前指令的配置项参数（对象）
    upper(element, options) {
      console.log(element);
      console.log(options.value);

      element.innerHTML = options.value.toUpperCase();
    },
  },
};
</script>

<style lang="less" scoped>
</style>