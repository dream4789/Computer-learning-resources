<template>
  <div class="container" v-height="0">
    <audio v-if="songUrl" :src="songUrl" ref="myaudio"></audio>
    <div
      class="bg"
      :style="{ 'background-image': 'url(' + imgUrl + ')' }"
    ></div>

    <div class="player">
      <div class="song" @click="changPlay">
        <div class="audio">
          <b class="lock" v-if="!lock"></b>
          <img :src="imgUrl" class="pic" :class="{ start: lock }" alt="" />
          <div class="mask"></div>
        </div>
        <div class="song-name">
          <span class="name">{{ name }}</span
          >-<span class="nick">{{ nickName }}</span>
        </div>
      </div>
      <div class="need"></div>
    </div>

    <div class="footer">
      <van-button class="btn" color="#ff3a3a" plain round block type="primary"
        >打开</van-button
      >
      <van-button
        class="btn btn-download"
        color="#ff3a3a"
        plain
        round
        block
        type="info"
        >下载</van-button
      >
    </div>
  </div>
</template>

<script>
import Vue from "vue";
import { Button } from "vant";

Vue.use(Button);

export default {
  name: "Player",
  props: [],
  data() {
    return {
      songUrl: null,
      imgUrl: null,
      id: null,
      name: null,
      nickName: null,
      lock: false,
    };
  },
  created() {
    this.songUrl =
      "https://music.163.com/song/media/outer/url?id=" +
      this.$route.query.id +
      ".mp3";

    this.imgUrl = this.$route.query.picUrl;
    this.name = this.$route.query.name;
    this.nickName = this.$route.query.nickName;
  },
  methods: {
    changPlay() {
      this.lock = !this.lock;
      if (this.lock) {
        this.$refs.myaudio.play();
      } else {
        this.$refs.myaudio.pause();
      }
    },
  },
};
</script>

<style lang="less" scoped>
.bg {
  position: fixed;
  left: 0px;
  right: 0px;
  top: 0px;
  height: 100%;
  filter: blur(15px);
  overflow: hidden;
  background-size: auto 100%;
  background-position: 50% 50%;
  background-repeat: no-repeat;
  transform-origin: center top;
  transform: scale(1.3);
  &::before {
    position: absolute;
    left: 0px;
    right: 0px;
    top: 0px;
    bottom: 0px;
    content: "";
    background-color: rgba(0, 0, 0, 0.5);
    // z-index: 1000;
  }
}

.player {
  width: 100%;
  height: 100%;
  position: absolute;
  top: 0px;
  left: 0px;

  .song {
    padding-top: 70px;
    .audio {
      position: relative;
      width: 296px;
      height: 296px;
      margin: 0 auto;
      .lock {
        position: absolute;
        left: 50%;
        top: 50%;
        width: 56px;
        height: 56px;
        transform: translate(-50%, -50%);
        z-index: 10;
        background: url("@/assets/img/lock.png") no-repeat;
        background-size: 100% auto;
      }
      .pic {
        width: 190px;
        height: 190px;
        position: absolute;
        left: 50%;
        top: 50%;
        transform: translate(-50%, -50%);

        animation: donghua 10s linear infinite;

        // 默认让动画暂停
        animation-play-state: paused;

        &.start {
          animation-play-state: running;
        }

        @keyframes donghua {
          from {
            transform: translate(-50%, -50%) rotate(0deg);
          }
          to {
            transform: translate(-50%, -50%) rotate(360deg);
          }
        }
      }
      .mask {
        position: absolute;
        left: 0;
        top: 0;
        width: 100%;
        height: 100%;
        background: url("@/assets/img/disc-ip6.png") no-repeat;
        background-size: 100% auto;
      }
    }
    .song-name {
      color: #fff;
      text-align: center;
      padding-top: 15px;
      .name {
        font-size: 18px;
      }
      .nick {
        font-size: 16px;
        color: #ccc;
      }
    }
  }

  .need {
    width: 87px;
    height: 126px;
    position: absolute;
    top: 20px;
    left: 46%;
    background: url("@/assets/img/needle-ip6.png");
    background-size: 100% auto;
    background-repeat: no-repeat;
  }
}

.footer {
  width: 100%;
  position: absolute;
  bottom: 30px;
  left: 0;
  display: flex;
  justify-content: space-between;
  .btn {
    margin: 0 10px;
    font-weight: bold;
  }
  .btn-download {
    color: #fff !important;
    background-color: rgb(255, 58, 58);
  }
}
</style>