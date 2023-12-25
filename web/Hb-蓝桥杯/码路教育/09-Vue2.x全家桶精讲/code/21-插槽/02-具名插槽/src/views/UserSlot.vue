<template>
  <div>
    <h2>UserSlot</h2>
    <!-- 
      插槽：
        作用：让组件更加灵活，更加强大。
        说白了，插槽也是组件通信的方案之一。
        非常重要，分三类：
          1）匿名插槽，表示插槽没有名字
          2）具名插槽，说明插槽有名字
          3）作用域插槽
    -->
    <!-- 使用组件，就是把组件当成标签来用，在标签之间写的内容，就会插入到插槽中 -->
    <Pannel>
      <!-- 下面的写法不行，v-slot需要配合template标签 -->
      <!-- <h4 v-slot:title>欢迎来到码路学习</h4> -->

      <template v-slot:title>
        <h4>欢迎来到码路学习</h4>
      </template>
      <template v-slot:content>
        <img src="../assets/01.png" />
      </template>
      <template v-slot:footer>
        <p>我是一个底部</p>
      </template>
    </Pannel>
    <Pannel>
      <template #title>
        <h4>欢迎来到码路学习</h4>
      </template>
      <template #content>
        <img src="../assets/01.png" />
      </template>
      <template #footer>
        <p>我是一个底部</p>
      </template>
    </Pannel>
  </div>
</template>

<script>
import Pannel from "../components/Pannel.vue";
export default {
  name: "UserSlot",
  props: [],
  data() {
    return {};
  },
  methods: {},
  components: {
    Pannel,
  },
};
</script>

<style lang="less" scoped>
</style>