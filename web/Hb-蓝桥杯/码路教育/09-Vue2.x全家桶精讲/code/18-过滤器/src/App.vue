<template>
  <div id="app">
    <h1>App组件</h1>
    <MyComponent1></MyComponent1>
    <hr />
    <MyComponent2></MyComponent2>
  </div>
</template>

<script>
import MyComponent1 from "./components/MyComponent1.vue";
import MyComponent2 from "./components/MyComponent2.vue";
export default {
  name: "App",
  components: {
    MyComponent1,
    MyComponent2,
  },
};
</script>

<style lang="less">
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
