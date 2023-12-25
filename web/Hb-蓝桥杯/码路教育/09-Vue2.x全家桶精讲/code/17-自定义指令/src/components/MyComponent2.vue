<template>
  <div>
    <h2>MyComponent2组件</h2>
    <p v-upper="msg"></p>
    <input v-focus type="text" />
  </div>
</template>

<script>
export default {
  name: "MyComponent1",
  props: [],
  data() {
    return {
      msg: "hello malu",
    };
  },
  methods: {},
};
</script>

<style lang="less" scoped>
</style>