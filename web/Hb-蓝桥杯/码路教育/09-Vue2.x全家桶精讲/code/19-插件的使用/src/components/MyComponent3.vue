<template>
  <div>
    <h2>MyComponent3</h2>
    <button @click="fn">点我</button>
  </div>
</template>

<script>
export default {
  name: "MyComponent3",
  props: [],
  data() {
    return {};
  },
  methods: {
    fn() {
      this.$ml();
    },
  },
};
</script>

<style lang="less" scoped>
</style>