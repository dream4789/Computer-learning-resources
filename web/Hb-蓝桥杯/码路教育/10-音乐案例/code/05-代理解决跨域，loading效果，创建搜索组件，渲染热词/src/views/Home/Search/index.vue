<template>
  <div class="container" v-height="126">
    <Loading v-if="isShowLoading"></Loading>
    <van-search
      v-model="searchValue"
      shape="round"
      background="#fff"
      placeholder="请输入歌曲，歌手，专辑"
      @input="subKey"
    />
    <!-- 热门搜索 -->
    <div class="hot-key">
      <h3>热门搜索</h3>
      <span class="hot-item" v-for="(item, index) in hotKeyList" :key="index">{{
        item.first
      }}</span>
    </div>
  </div>
</template>

<script>
import Loading from "@/components/Loading/index.vue";

import Vue from "vue";
import { Toast, Search } from "vant";

Vue.use(Toast);
Vue.use(Search);

export default {
  name: "Search",
  props: [],
  data() {
    return {
      searchValue: "", // 搜索框中输入的数据
      hotKeyList: [], // 热词
      isShowLoading: false, // loading是否显示
    };
  },
  components: {
    Loading,
  },
  created() {
    this.getHotKey();
  },
  methods: {
    // 获取热词
    getHotKey() {
      this.isShowLoading = true;
      this.$http
        .post("/search/hot")
        .then((res) => {
          if (res.data.code == 200) {
            this.hotKeyList = res.data.result.hots;
          }
          this.isShowLoading = false;
        })
        .catch((err) => {
          Toast("网络出小差");
          this.isShowLoading = false;
        });
    },
    // 当输入框中的数据发生了变化，就需要ajax请求，获取数据
    subKey() {},
  },
};
</script>

<style lang="less" scoped>
.container {
  overflow: auto;
}
.hot-key {
  padding: 0 10px;

  h3 {
    line-height: 45px;
    font-size: 12px;
  }

  .hot-item {
    display: inline-block;
    border: 1px solid #d3d4da;
    border-radius: 32px;
    height: 32px;
    margin-right: 8px;
    margin-bottom: 8px;
    padding: 0 14px;
    font-size: 14px;
    line-height: 32px;
    color: #333;
  }
}
</style>