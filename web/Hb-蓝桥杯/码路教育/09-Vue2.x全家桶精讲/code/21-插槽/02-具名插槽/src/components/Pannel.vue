<template>
  <div>
    <!-- 按钮标题 -->
    <div class="title">
      <!-- <h4>欢迎来到码路学习</h4> -->
      <slot name="title"></slot>
      <span class="btn" @click="isShow = !isShow">
        {{ isShow ? "收起" : "展开" }}
      </span>
    </div>
    <!-- 下拉内容 -->
    <div class="container" v-show="isShow">
      <!-- 通过name可以给插槽起一个名字 -->
      <!-- 在使用组件时，向插槽中插入内容时，就需要指定名字 -->
      <slot name="content">默认显示的内容</slot>
      <slot name="footer">默认显示的内容</slot>
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