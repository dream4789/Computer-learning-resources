<template>
  <div class="mask">
    <van-loading type="spinner" size="34px" />
  </div>
</template>

<script>
import Vue from "vue";
import { Loading } from "vant";
Vue.use(Loading);

export default {
  name: "Loading",
  props: [],
  data() {
    return {};
  },
  methods: {},
};
</script>

<style lang="less" scoped>
.mask {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  z-index: 999;
  height: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  background: rgba(0, 0, 0, 0.5);
}
</style>