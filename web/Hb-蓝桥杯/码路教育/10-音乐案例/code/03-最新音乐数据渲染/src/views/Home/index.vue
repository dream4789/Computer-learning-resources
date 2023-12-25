<template>
  <div>
    <div class="header">
      <img src="@/assets/img/01.gif" alt="" />
      <img src="@/assets/img/02.gif" alt="" />
    </div>
    <van-tabs v-model="active" title-active-color="#dd001b" line-width="60px">
      <van-tab title="推荐音乐">
        <Recommend></Recommend>
      </van-tab>
      <van-tab title="热歌榜">热歌榜</van-tab>
      <van-tab title="搜索">搜索</van-tab>
    </van-tabs>
  </div>
</template>

<script>
// 已经配置好了按需引入
import Vue from "vue";
import { Tab, Tabs } from "vant";
Vue.use(Tab);
Vue.use(Tabs);

import Recommend from "./Recommend/index.vue";

export default {
  name: "index",
  props: [],
  data() {
    return {
      active: 0,
    };
  },
  methods: {},
  components: {
    Recommend,
  },
};
</script>

<style lang="less" scoped>
.header {
  padding: 20px 5px;
  display: flex;
  justify-content: space-between;
  align-items: center;
  background: #d43c33;
}
</style>