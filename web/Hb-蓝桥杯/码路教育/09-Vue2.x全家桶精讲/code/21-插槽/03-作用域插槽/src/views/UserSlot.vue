<template>
  <div>
    <h2>UserSlot</h2>
    <!-- 
      作用域插槽：
        场景：使用插槽，使用组件内定义的数据
        在插槽中插入的数据，自来于子组件。

      使用步骤：
        1）slot标签上，自定义属性和组件内数据进行关联
        2）使用组件，在template标签上使用v-slot="scope"
     -->
    <!--  -->
    <Pannel>
      <template v-slot="scope">
        <p>{{ scope.row.name2 }}</p>
      </template>
    </Pannel>
  </div>
</template>

<script>
import Pannel from "../components/Pannel.vue";
export default {
  name: "UserSlot",
  props: [],
  data() {
    return {};
  },
  methods: {},
  components: {
    Pannel,
  },
};
</script>

<style lang="less" scoped>
</style>