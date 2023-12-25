<template>
  <div>
    <MyTable :data="list">
      <template #header>
        <th>#</th>
        <th>商品名称</th>
        <th>价格</th>
        <th>标签</th>
        <th>操作</th>
      </template>
      <template #body="scope">
        <td>{{ scope.row.id }}</td>
        <td>{{ scope.row.goods_name }}</td>
        <td>{{ scope.row.goods_price }}</td>
        <td>
          <input
            type="text"
            class="form-control"
            style="width: 100px"
            v-if="scope.row.inputVisible"
            v-focus
            @blur="blurFn(scope.row)"
            v-model="scope.row.inputValue"
            @keydown.enter="enterFn(scope.row)"
            @keydown.esc="scope.row.inputValue = ''"
          />
          <button
            v-else
            class="btn btn-primary btn-sm add-tag"
            @click="scope.row.inputVisible = true"
          >
            +Tag
          </button>
          <span
            class="badge badge-warning"
            v-for="(str, idx) in scope.row.tags"
            :key="idx"
          >
            {{ str }}
          </span>
        </td>
        <td>
          <button class="btn btn-danger btn-sm" @click="remove(scope.row.id)">
            删除
          </button>
        </td>
      </template>
    </MyTable>
  </div>
</template>

<script>
import MyTable from "../components/MyTable.vue";
import data from "../assets/data.json";
export default {
  name: "MyGoodsList",
  props: [],
  data() {
    return {
      list: data.data,
    };
  },
  methods: {
    remove(id) {
      let index = this.list.findIndex((obj) => obj.id === id);
      this.list.splice(index, 1);
    },
    enterFn(obj) {
      if (obj.inputValue.trim() == "") {
        alert("请输入数据");
        return;
      }
      obj.tags.push(obj.inputValue);
      obj.inputValue = "";
    },
    blurFn(obj) {
      obj.inputVisible = false;
      obj.inputValue = "";
    },
  },
  components: {
    MyTable,
  },
};
</script>

<style lang="less" scoped>
</style>