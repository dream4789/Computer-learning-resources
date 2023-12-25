<template>
  <div>
    <!-- 按钮标题 -->
    <div class="title">
      <h4>欢迎来到码路学习</h4>
      <span class="btn" @click="isShow = !isShow">
        {{ isShow ? "收起" : "展开" }}
      </span>
    </div>
    <!-- 下拉内容 -->
    <div class="container" v-show="isShow">
      <!-- slot 就是插槽，没有给slot起名字，这个插槽叫匿名插槽 -->
      <!-- 如果没有向插槽中插入内容，默认显示slot组件中的内容 -->
      <slot>默认显示的内容</slot>

      <!-- 插槽可以有多个，如果多个插槽都没有名字，插入内容分别都分向多个插槽中插入 -->
      <!-- <slot>默认显示的内容</slot>
      <slot>默认显示的内容</slot> -->
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      isShow: false,
    };
  },
};
</script>

<style scoped>
h3 {
  text-align: center;
}

.title {
  display: flex;
  justify-content: space-between;
  align-items: center;
  border: 1px solid #ccc;
  padding: 0 1em;
}

.title h4 {
  line-height: 2;
  margin: 0;
}

.container {
  border: 1px solid #ccc;
  padding: 0 1em;
}

.btn {
  /* 鼠标改成手的形状 */
  cursor: pointer;
}

img {
  width: 50%;
}
</style>