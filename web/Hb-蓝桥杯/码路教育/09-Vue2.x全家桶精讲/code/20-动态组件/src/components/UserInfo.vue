<template>
  <div>
    <div>
      <span>学习目标:</span>
      <input type="text" />
    </div>
    <div>
      <span>个人简介:</span>
      <textarea></textarea>
    </div>
  </div>
</template>

<script>
export default {
  created() {
    console.log("UserInfo created");
  },
  destroyed() {
    console.log("UserInfo destroyed");
  },
  // 组件如果被缓存了，多了两个钩子函数
  activated() {
    console.log("UserInfo activated");
  },
  deactivated() {
    console.log("UserInfo deactivated");
  },
};
</script>

<style>
</style>