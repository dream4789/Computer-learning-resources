<template>
  <div class="container" v-height="126">
    <Loading v-if="isShowLoading"></Loading>
    <van-search
      v-model="searchValue"
      shape="round"
      background="#fff"
      placeholder="请输入歌曲，歌手，专辑"
      @input="subKey"
      @clear="clearKey"
      @blur="saveKey"
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
      <li
        @click="toPlayer(item)"
        v-for="(item, index) in keySonsList"
        :key="index"
      >
        <p class="name">{{ item.name }}</p>
        <div class="info">
          <i class="sq" v-if="item.fee == 0"></i>
          <span class="zj">{{ item.name }} - {{ item.ar[0].name }}</span>
        </div>
        <div class="play"></div>
      </li>
    </ul>
    <!-- 渲染历史记录 -->
    <ul v-if="isShowKey" class="show-key">
      <li v-for="(item, index) in historyList" :key="index">
        <van-icon class="icon1" name="clock-o" />
        <span>{{ item }}</span>
        <van-icon @click="removeKey(item)" class="icon2" name="cross" />
      </li>
    </ul>
  </div>
</template>

<script>
import Vue from "vue";
import _ from "lodash";

import Loading from "@/components/Loading/index.vue";
import { Toast, Search, Icon } from "vant";

Vue.use(Toast);
Vue.use(Search);
Vue.use(Icon);

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
      historyList: [], // 搜索的历史记录
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
    // subKey(val) {
    //   if (!val) {
    //     this.isShowKey = true;
    //     return;
    //   }
    //   this.searchValue = val;
    //   this.isShowKey = false;
    //   this.getKeyInfo();
    // },

    // 自己实现防抖后的
    subKey(val) {
      if (this.timer) clearTimeout(this.timer);
      this.timer = setTimeout(() => {
        if (!val) {
          this.isShowKey = true;
          return;
        }
        this.searchValue = val;
        this.isShowKey = false;
        this.getKeyInfo();
        this.timer = null;
      }, 500);
    },
    test() {
      console.log("test...");
    },
    // 点击输入框中的小x
    clearKey() {
      this.isShowKey = true;
    },
    // 当输入框失去焦点时
    saveKey() {
      if (this.searchValue && !this.historyList.includes(this.searchValue)) {
        this.historyList.push(this.searchValue);
      }
    },
    // 删除历史记录
    removeKey(val) {
      this.historyList = this.historyList.filter((item) => item != val);
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
    // 点击去播放
    toPlayer(data) {
      console.log("data=>", data);
      let obj = {
        path: "/player",
        query: {
          picUrl: data.al.picUrl,
          name: data.al.name,
          id: data.id,
          nickName: data.ar[0].name,
        },
      };
      this.$router.push(obj);
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

.show-key {
  padding: 0 10px;
  margin-top: 15px;

  li {
    line-height: 40px;
    position: relative;
    border-bottom: 0.5px solid rgba(0, 0, 0, 0.1);

    .icon1 {
      margin-right: 10px;
      vertical-align: middle;
    }

    span {
      vertical-align: middle;
    }

    .icon2 {
      vertical-align: middle;
      position: absolute;
      right: 10px;
      top: 50%;
      transform: translateY(-50%);
    }
  }
}
</style>