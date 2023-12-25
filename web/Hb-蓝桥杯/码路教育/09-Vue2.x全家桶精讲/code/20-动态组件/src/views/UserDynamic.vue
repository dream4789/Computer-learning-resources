<template>
  <div>
    <h1>UserDynamic</h1>
    <button @click="comName = 'UserName'">UserName</button>
    <button @click="comName = 'UserInfo'">UserInfo</button>
    <!-- 
        动态组件：
            也可以实现组件之间的切换，之前是通过路由实现组件切换。
            在vue中，内置了一个组件，叫component，通过is选项来确定到底显示哪一个组件
     -->
    <p>实现组件的切换，通过动态组件</p>
    <!-- <div style="border: 1px solid red">
      <component :is="comName"></component>
    </div> -->

    <!-- 在vue中，提供了一个组件，叫keep-alive，可以缓存组件 -->
    <div style="border: 1px solid red">
      <keep-alive>
        <component :is="comName"></component>
      </keep-alive>
    </div>
  </div>
</template>

<script>
import UserName from "../components/UserName.vue";
import UserInfo from "../components/UserInfo.vue";
export default {
  name: "UserDynamic",
  props: [],
  data() {
    return {
      comName: "UserName",
    };
  },
  methods: {},
  components: {
    UserName,
    UserInfo,
  },
};
</script>

<style lang="less" scoped>
</style>