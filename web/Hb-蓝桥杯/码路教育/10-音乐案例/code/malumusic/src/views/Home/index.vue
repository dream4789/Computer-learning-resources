<template>
  <div>
    <div class="header">
      <img src="@/assets/img/01.gif" alt="" />
      <img src="@/assets/img/02.gif" alt="" />
    </div>
    <van-tabs
      @change="changeTab"
      v-model="active"
      title-active-color="#dd001b"
      line-width="60px"
    >
      <van-tab title="推荐音乐">
        <!-- <Recommend></Recommend> -->
      </van-tab>
      <van-tab title="热歌榜">
        <!-- <Hot></Hot> -->
      </van-tab>
      <van-tab title="搜索"></van-tab>
    </van-tabs>
    <div>
      <component :is="compoentType"></component>
    </div>
  </div>
</template>

<script>
// 已经配置好了按需引入
import Vue from "vue";
import { Tab, Tabs } from "vant";
Vue.use(Tab);
Vue.use(Tabs);

import Recommend from "./Recommend/index.vue";
import Hot from "./Hot/index.vue";
import Search from "./Search/index.vue";

export default {
  name: "index",
  props: [],
  data() {
    return {
      active: 0,
      compoentType: "Recommend",
    };
  },
  methods: {
    changeTab(val) {
      if (val === 0) {
        this.compoentType = "Recommend";
      } else if (val === 1) {
        this.compoentType = "Hot";
      } else if (val === 2) {
        this.compoentType = "Search";
      }
    },
  },
  components: {
    Recommend,
    Hot,
    Search,
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