<template>
  <div id="app">
    <MyHeader
      background="skyblue"
      fontColor="red"
      title="TabBar练习"
    ></MyHeader>
    <div class="main">
      <component :is="comName"></component>
    </div>
    <MyTabBar :arr="tabList" @changeCom="changeComFn"></MyTabBar>
  </div>
</template>

<script>
import MyHeader from "./components/MyHeader.vue";
import MyTabBar from "./components/MyTabBar.vue";

import MyGoodsList from "./views/MyGoodsList.vue";
import MyGoodsSearch from "./views/MyGoodsSearch.vue";
import MyUserInfo from "./views/MyUserInfo.vue";
export default {
  name: "App",
  data() {
    return {
      comName: "MyGoodsList",
      tabList: [
        {
          iconText: "icon-shangpinliebiao",
          text: "商品列表",
          componentName: "MyGoodsList",
        },
        {
          iconText: "icon-sousuo",
          text: "商品搜索",
          componentName: "MyGoodsSearch",
        },
        {
          iconText: "icon-user",
          text: "我的信息",
          componentName: "MyUserInfo",
        },
      ],
    };
  },
  methods: {
    changeComFn(comName) {
      this.comName = comName;
    },
  },
  components: {
    MyHeader,
    MyTabBar,
    MyGoodsList,
    MyGoodsSearch,
    MyUserInfo,
  },
};
</script>

<style lang="less">
.main {
  padding-top: 45px;
  padding-bottom: 50px;
}
</style>
