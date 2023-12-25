<template>
  <div>
    <h2>MyComponent1</h2>
    <h3>{{ time }}</h3>
    <h3>{{ time | timeFormat }}</h3>
  </div>
</template>

<script>
// 如果想对时间进行一个格式化，此时可以使用过滤器
// 分两类：
// 1）局部过滤器
// 2）全局过滤器
// 要对时间进行过滤（格式化），可以使用moment，
// 现在还有一个比较新的依赖，叫dayjs
import moment from "moment";
export default {
  name: "MyComponent1",
  props: [],
  data() {
    return {
      time: Date.now(),
    };
  },
  methods: {},
  filters: {
    // 一个过滤器，也是一个函数
    timeFormat(params) {
      console.log(params);
      // format 是格式化的格式
      // return moment(params).format("YYYY-MM-DD");
      return moment(params).format("MM-DD");
    },
  },
};
</script>

<style lang="less" scoped>
</style>