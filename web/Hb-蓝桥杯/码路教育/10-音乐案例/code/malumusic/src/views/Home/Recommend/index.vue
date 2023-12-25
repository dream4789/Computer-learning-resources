<template>
  <div>
    <Loading v-if="isShowLoading"></Loading>
    <!-- 126 v-height="126"  v-height-->
    <div class="container" v-height="126">
      <h2 class="title">推荐歌单</h2>
      <div class="song-container">
        <div class="list" v-for="(item, index) in songList" :key="index">
          <div class="pic">
            <img :src="item.picUrl" alt="" />
            <span>{{ item.playCount | formatCount }} 万</span>
          </div>
          <div class="content">{{ item.name }}</div>
        </div>
      </div>
      <h2 class="title">最新音乐</h2>
      <ul class="top-list">
        <li
          @click="toPlayer(item)"
          v-for="(item, index) in topList"
          :key="index"
        >
          <p class="name">{{ item.name }}</p>
          <div class="info">
            <i class="sq" v-if="item.song.sqMusic != null"></i>
            <span class="zj"
              >{{ item.song.artists[0].name }} -
              {{ item.song.album.name }}</span
            >
          </div>
          <div class="play"></div>
        </li>
      </ul>
      <div class="footer">
        <div class="openapp" @click="openUrl">打开APP，发现更好音乐</div>
      </div>
    </div>
  </div>
</template>

<script>
import Loading from "@/components/Loading/index.vue";

import Vue from "vue";
import { Toast } from "vant";
Vue.use(Toast);

export default {
  name: "Recommend",
  props: [],
  created() {
    this.getSongList();
    this.getTopList();
  },
  data() {
    return {
      songList: [], // 推荐歌单
      topList: [], // 最新音乐
      isShowLoading: false, // loading是否显示
    };
  },
  components: {
    Loading,
  },
  methods: {
    // 获取推荐歌单
    getSongList() {
      this.isShowLoading = true;

      // 没有写域名和端口默认是向自己当有服务器发请求
      // 当前服务器是：http://localhost:8081/
      this.$http
        .post("/personalized?limit=6")
        .then((res) => {
          // console.log("res:", res);
          if (res.statusText === "OK" && res.status === 200) {
            this.songList = res.data.result;
          }
          this.isShowLoading = false;
        })
        .catch((err) => {
          Toast("网络出小差");
          this.isShowLoading = false;
        });
    },
    // 获取最新音乐
    getTopList() {
      this.isShowLoading = true;

      this.$http
        .post("/personalized/newsong")
        .then((res) => {
          console.log("res=>:", res);
          if (res.statusText === "OK" && res.status === 200) {
            this.topList = res.data.result;
          }
          this.isShowLoading = false;
        })
        .catch((err) => {
          Toast("网络出小差");
          this.isShowLoading = false;
        });
    },

    // 打开一个URL
    openUrl() {
      window.location =
        "https://m.music.163.com/m/applink/?scheme=orpheus%3A%2F%2Fopenurl";
    },
    // 点击去播放
    toPlayer(data) {
      let obj = {
        path: "/player",
        query: {
          picUrl: data.picUrl,
          name: data.name,
          id: data.id,
          nickName: data.song.artists[0].name,
        },
      };
      this.$router.push(obj);
    },
  },
  filters: {
    formatCount(val) {
      return (val / 10000).toFixed(1);
    },
  },
};
</script>

<style lang="less" scoped>
.container {
  .title {
    padding-left: 5px;
    margin: 15px 0;
    font-size: 17px;
    border-left: 2px solid red;
  }
  height: 200px;
  overflow: auto;

  .song-container {
    display: flex;
    flex-wrap: wrap;
    .list {
      margin: 2px;
      flex-basis: calc(33% - 4px);
      .pic {
        position: relative;
        span {
          position: absolute;
          right: 3px;
          top: 3px;
          color: #fff;
          font-size: 12px;
          background: url(data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyMiAyMCI+PHBhdGggZmlsbC1ydWxlPSJldmVub2RkIiBmaWxsPSIjMDQwMDAwIiBkPSJNMjIgMTYuNzc3YzAgMS4yMzMtMS4xMjEgMi4yMzMtMi41MDYgMi4yMzMtMS4zODQgMC0yLjUwNi0xLTIuNTA2LTIuMjMzdi0yLjU1M2MwLTEuMjM0IDEuMTIyLTIuMjMzIDIuNTA2LTIuMjMzLjE3NCAwIC4zNDMuMDE3LjUwNi4wNDZ2LTEuMzdoLS4wMzNjLjAxNy0uMjIuMDMzLS40NDEuMDMzLS42NjZhOCA4IDAgMCAwLTE2IDBjMCAuMjI1LjAxNi40NDYuMDM0LjY2Nkg0djEuMzdjLjE2My0uMDI5LjMzMy0uMDQ2LjUwNS0uMDQ2IDEuMzg0IDAgMi41MDYuOTk5IDIuNTA2IDIuMjMzdjIuNTUzYzAgMS4yMzMtMS4xMjIgMi4yMzMtMi41MDYgMi4yMzNTMiAxOC4wMTEgMiAxNi43Nzd2LTIuNTUzYzAtLjI1OC4wNTktLjUwMS4xNDgtLjczQS45ODIuOTgyIDAgMCAxIDIgMTMuMDAxdi0yLjY2N2MwLS4wMjMuMDEyLS4wNDMuMDEzLS4wNjctLjAwNC0uMDg4LS4wMTMtLjE3Ni0uMDEzLS4yNjYgMC01LjUyMyA0LjQ3Ny0xMCAxMC0xMHMxMCA0LjQ3NyAxMCAxMGMwIC4wOS0uMDA5LjE3OC0uMDE0LjI2Ni4wMDIuMDI0LjAxNC4wNDQuMDE0LjA2N3YyYS45ODguOTg4IDAgMCAxLS4zNi43NTNjLjIyNC4zMzQuMzYuNzIuMzYgMS4xMzh2Mi41NTIiIG9wYWNpdHk9Ii4xNSIvPjxwYXRoIGZpbGwtcnVsZT0iZXZlbm9kZCIgZmlsbD0iI2ZmZiIgZD0iTTIwIDE2Ljc3N2MwIDEuMjMzLTEuMTIxIDIuMjMzLTIuNTA2IDIuMjMzLTEuMzg0IDAtMi41MDYtMS0yLjUwNi0yLjIzM3YtMi41NTNjMC0xLjIzNCAxLjEyMi0yLjIzMyAyLjUwNi0yLjIzMy4xNzQgMCAuMzQzLjAxNy41MDYuMDQ2di0xLjM3aC0uMDMzYy4wMTctLjIyLjAzMy0uNDQxLjAzMy0uNjY2YTggOCAwIDAgMC0xNiAwYzAgLjIyNS4wMTYuNDQ2LjAzNC42NjZIMnYxLjM3Yy4xNjMtLjAyOS4zMzMtLjA0Ni41MDUtLjA0NiAxLjM4NCAwIDIuNTA2Ljk5OSAyLjUwNiAyLjIzM3YyLjU1M2MwIDEuMjMzLTEuMTIyIDIuMjMzLTIuNTA2IDIuMjMzUzAgMTguMDExIDAgMTYuNzc3di0yLjU1M2MwLS4yNTguMDU5LS41MDEuMTQ4LS43M0EuOTgyLjk4MiAwIDAgMSAwIDEzLjAwMXYtMi42NjdjMC0uMDIzLjAxMi0uMDQzLjAxMy0uMDY3LS4wMDQtLjA4OC0uMDEzLS4xNzYtLjAxMy0uMjY2IDAtNS41MjMgNC40NzctMTAgMTAtMTBzMTAgNC40NzcgMTAgMTBjMCAuMDktLjAwOS4xNzgtLjAxNC4yNjYuMDAyLjAyNC4wMTQuMDQ0LjAxNC4wNjd2MmEuOTg4Ljk4OCAwIDAgMS0uMzYuNzUzYy4yMjQuMzM0LjM2LjcyLjM2IDEuMTM4djIuNTUyIi8+PC9zdmc+);
          background-position: center left;
          padding-left: 28px;
          background-repeat: no-repeat;
          background-size: 60% 60%;
        }
        img {
          width: 100%;
        }
      }
      .content {
        padding: 0px 3px;
        font-size: 13px;
      }
    }
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
.footer {
  background: url("../../../assets/img/recommand_bg_2x.png") no-repeat;
  background-size: 100% 100%;
  position: relative;
  padding: 30px 0;
  .openapp {
    line-height: 38px;
    border: 1px solid #d33a31;
    border-radius: 38px;
    font-size: 16px;
    color: #d33a31;
    margin: 15px 37px 5px;
    text-align: center;
  }
}
</style>