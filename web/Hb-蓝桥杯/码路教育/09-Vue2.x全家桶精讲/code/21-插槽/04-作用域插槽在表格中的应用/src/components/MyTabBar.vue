<template>
  <div class="tab-bar">
    <div
      :class="{ current: index === selIndex }"
      @click="btn(index, obj)"
      v-for="(obj, index) in arr"
      :key="index"
      class="tab-item"
    >
      <span class="iconfont" :class="obj.iconText"></span>
      <span>{{ obj.text }}</span>
    </div>
  </div>
</template>

<script>
export default {
  name: "MyTabBar",
  props: ["arr"],
  data() {
    return {
      selIndex: 0, // 默认让第1个变亮
    };
  },

  methods: {
    btn(index, obj) {
      this.selIndex = index;
      this.$emit("changeCom", obj.componentName);
    },
  },
};
</script>

<style lang="less" scoped>
.tab-bar {
  position: fixed;
  left: 0;
  bottom: 0;
  width: 100%;
  height: 50px;
  border-top: 1px solid red;
  display: flex;
  justify-content: space-around;
  background-color: #fff;
  .tab-item {
    display: flex;
    flex-direction: column;
    align-items: center;
  }
}
.current {
  color: red;
}
</style>