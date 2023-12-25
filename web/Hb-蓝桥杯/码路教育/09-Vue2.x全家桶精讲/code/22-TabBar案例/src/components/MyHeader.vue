<template>
  <div
    class="my-header"
    :style="{ backgroundColor: background, color: fontColor }"
  >
    {{ title }}
  </div>
</template>

<script>
export default {
  name: "MyHeader",
  props: ["background", "fontColor", "title"],
  data() {
    return {};
  },
  methods: {},
};
</script>

<style lang="less" scoped>
.my-header {
  height: 45px;
  line-height: 45px;
  text-align: center;
  position: fixed;
  font-weight: bold;
  top: 0;
  left: 0;
  width: 100%;
  z-index: 10;
}
</style>