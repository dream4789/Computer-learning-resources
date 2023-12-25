<template>
  <div id="app">
    <h1>App组件</h1>
    <hr />
    <UserDynamic></UserDynamic>
  </div>
</template>

<script>
import UserDynamic from "./views/UserDynamic.vue";
export default {
  name: "App",
  components: {
    UserDynamic,
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
