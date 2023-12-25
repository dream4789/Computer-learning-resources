<template>
  <div id="app">
    APP
    <van-button type="primary">主要按钮</van-button>
    <van-button type="info">信息按钮</van-button>
    <van-button type="default">默认按钮</van-button>
    <van-button type="warning">警告按钮</van-button>
    <van-button type="danger">危险按钮</van-button>
    <router-view></router-view>
  </div>
</template>

<script>
// 手动按需引入
// import Vue from "vue";
// import Button from "vant/lib/button";
// import "vant/lib/button/style";
// Vue.use(Button);

// 自动按需引入
import Vue from "vue";
import { Button } from "vant";
Vue.use(Button);

export default {
  name: "App",
  data() {
    return {};
  },
  methods: {},
  components: {},
};
</script>

<style lang="less">
.main {
  padding-top: 45px;
  padding-bottom: 50px;
}
</style>
