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
    <div class="hot-key" v-if="isShowKey">
      <h3>热门搜索</h3>
      <span
        @click="subKey(item.first)"
        class="hot-item"
        v-for="(item, index) in hotKeyList"
        :key="index"
        >{{ item.first }}</span
      >
    </div>
    <ul class="top-list" v-if="keySonsList.length && !isShowKey">
      <li v-for="(item, index) in keySonsList" :key="index">
        <p class="name">{{ item.name }}</p>
        <div class="info">
          <i class="sq" v-if="item.fee == 0"></i>
          <span class="zj">{{ item.name }} - {{ item.ar[0].name }}</span>
        </div>
        <div class="play"></div>
      </li>
    </ul>
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
      keySonsList: [], // 根据关键字获取对应的歌曲列表
      isShowKey: true, // 是否显示热词
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
    subKey(val) {
      if (!val) return;
      this.searchValue = val;

      this.isShowKey = false;
      this.getKeyInfo();
    },
    // 根据关键字发请求,获取相关的数据
    getKeyInfo() {
      this.isShowLoading = true;
      this.$http
        .get("/cloudsearch", {
          params: {
            keywords: this.searchValue,
          },
        })
        .then((res) => {
          console.log("res=>", res);
          if (res.data.code == 200) {
            this.keySonsList = res.data.result.songs;
          }
          this.isShowLoading = false;
        })
        .catch((err) => {
          Toast("网络出小差");
          this.isShowLoading = false;
        });
    },
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
.top-list {
  padding-left: 10px;

  li {
    padding: 5px 0;
    border-bottom: 0.5px solid rgba(0, 0, 0, 0.1);
    padding-right: 32px;
    position: relative;

    .play {
      position: absolute;
      right: 10px;
      top: 50%;
      transform: translateY(-50%);
      width: 22px;
      height: 22px;
      background: url("../../../assets/img/index_icon.jpg");
      background-repeat: no-repeat;
      background-position: -24px 0;
      background-size: 166px 97px;
    }

    .name {
      font-size: 17px;
    }

    .info {
      .zj {
        font-size: 12px;
        color: #888;
      }

      .sq {
        display: inline-block;
        width: 12px;
        height: 8px;
        margin-right: 4px;
        background: url("../../../assets/img/index_icon.jpg");
        background-size: 166px 97px;
      }
    }
  }
}
</style>