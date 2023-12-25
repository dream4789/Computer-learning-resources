<template>
  <div class="container">
    <div class="pic">
      <div class="hot"></div>
      <span>更新时间：</span>
    </div>

    <ul class="top-list">
      <li>
        <p class="name">音乐名字</p>
        <div class="info">
          <i class="sq"></i>
          <span class="zj"> 音乐专辑 </span>
        </div>
        <i class="play"></i>
      </li>
    </ul>
  </div>
</template>

<script>
import moment from "moment";

export default {
  name: "Hot",
  props: [],
  data() {
    return {
      hotList: [],
    };
  },
  created() {
    this.getHotList();
  },
  methods: {
    getHotList() {
      this.$http.post("/playlist/detail?id=3778678").then((res) => {
        console.log("res:", res);
      });
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
