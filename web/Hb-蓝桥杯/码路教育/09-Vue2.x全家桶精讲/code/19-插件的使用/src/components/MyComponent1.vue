<template>
  <div>
    <h2>MyComponent1</h2>
    <p v-upper="msg"></p>
    <ml-count></ml-count>
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