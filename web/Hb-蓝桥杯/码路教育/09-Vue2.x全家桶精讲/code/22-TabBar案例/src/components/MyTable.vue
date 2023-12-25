<template>
  <table class="table table-bordered table-striped">
    <thead>
      <tr>
        <!-- <th>#</th>
        <th>商品名称</th>
        <th>价格</th>
        <th>标签</th>
        <th>操作</th> -->
        <slot name="header"></slot>
      </tr>
    </thead>
    <tbody>
      <tr v-for="obj in data" :key="obj.id">
        <!-- 定义一个插槽，使用表格时，需要把数据传递过来 -->
        <!-- 这里插入的数据来自于子，使用作用域插槽 -->
        <slot name="body" :row="obj"></slot>
      </tr>
    </tbody>
  </table>
</template>

<script>
export default {
  name: "MyTable",
  props: ["data"],
  data() {
    return {};
  },
  methods: {},
};
</script>

<style lang="less" scoped>
</style>