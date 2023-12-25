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
    <Pannel> ok </Pannel>
    <Pannel>
      <img src="../assets/01.png" alt="" />
    </Pannel>
    <Pannel>
      <p>春眠不觉晓</p>
      <p>处处闻啼鸟</p>
      <p>夜来风雨声</p>
      <p>花落知多少</p>
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