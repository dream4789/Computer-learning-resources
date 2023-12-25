<template>
  <div class="container" v-height="126">
    <Loading v-if="isShowLoading"></Loading>
    <div class="pic">
      <div class="hot"></div>
      <span>更新时间：{{ updateTime | formatTime }}</span>
    </div>

    <ul class="top-list">
      <li @click="toPlayer(item)" v-for="(item, index) in hotList" :key="index">
        <p class="name">{{ item.name }}</p>
        <div class="info">
          <i class="sq"></i>
          <span class="zj"> {{ item.ar[0].name }} </span>
        </div>
        <i class="play"></i>
      </li>
    </ul>
  </div>
</template>

<script>
import moment from "moment";
import Loading from "@/components/Loading/index.vue";

import Vue from "vue";
import { Toast } from "vant";
Vue.use(Toast);

export default {
  name: "Hot",
  props: [],
  data() {
    return {
      hotList: [],
      isShowLoading: false, // loading是否显示
      updateTime: {}, // 更新时间
    };
  },
  created() {
    this.getHotList();
  },
  components: {
    Loading,
  },
  methods: {
    getHotList() {
      this.isShowLoading = true;
      this.$http
        .post("/playlist/detail?id=3778678")
        .then((res) => {
          if (res.statusText === "OK" && res.status === 200) {
            this.hotList = res.data.playlist.tracks;
            this.updateTime = res.data.playlist.updateTime;
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
  filters: {
    formatTime(val) {
      if (val) {
        return moment(val).format("MM月DD日");
      }
    },
  },
};
</script>

<style lang="less" scoped>
.container {
  height: 500px;
  overflow: auto;
}

.pic {
  position: relative;
  height: 146px;
  padding-left: 20px;
  padding-top: 20px;
  overflow: hidden;
  background: url("../../../assets/img/hot_music_bg.jpg") no-repeat;
  background-size: contain;

  .hot {
    width: 142px;
    height: 67px;
    background: url("../../../assets/img/index_icon.jpg") no-repeat;
    background-size: 166px 97px;
    background-position: -24px -30px;
  }

  span {
    display: inline-block;
    margin-top: 15px;
    font-size: 12px;
    color: #fff;
    line-height: 24px;
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
