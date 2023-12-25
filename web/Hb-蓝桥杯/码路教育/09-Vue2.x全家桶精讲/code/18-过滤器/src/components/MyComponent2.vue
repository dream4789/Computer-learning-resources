<template>
  <div>
    <h2>MyComponent2</h2>
    <p>{{ money }}</p>
    <p>{{ money | moneyFormat }}</p>
  </div>
</template>

<script>
export default {
  name: "MyComponent2",
  props: [],
  data() {
    return {
      money: 100,
    };
  },
  methods: {},
};
</script>

<style lang="less" scoped>
</style>