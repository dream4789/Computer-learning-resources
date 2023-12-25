<template>
  <div>
    <div>
      <span>用户名:</span>
      <input type="text" />
    </div>
    <div>
      <span>密码:</span>
      <input type="password" />
    </div>
  </div>
</template>

<script>
export default {
  created() {
    console.log("UserName created");
  },
  destroyed() {
    console.log("UserName destroyed");
  },
  // 组件如果被缓存了，多了两个钩子函数
  activated() {
    console.log("UserName activated");
  },
  deactivated() {
    console.log("UserName deactivated");
  },
};
</script>

<style>
</style>