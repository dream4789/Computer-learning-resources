<template>
  <div class="main">
    <!-- <el-table ref="singleTable" highlight-current-row :data="tableData" stripe border style="width: 100%"> -->
    <el-table
      ref="singleTable"
      highlight-current-row
      @current-change="setCurrent"
      :data="tableData"
      stripe
      border
      style="width: 100%"
    >
      <el-table-column label="单选" width="80">
        <!-- TODO：完善单选按钮组件，实现需求（DOM 结构不能修改） -->
        <template slot-scope="scope">
          <el-radio
            :label="scope.row.date"
            v-model="currentRow"
            >&nbsp;
          </el-radio>
          <!-- <el-radio v-model="currentRow">&nbsp;</el-radio> -->
        </template>
      </el-table-column>

      <el-table-column label="日期" width="180">
        <template slot-scope="scope">
          📅<span style="margin-left: 10px">{{ scope.row.date }}</span>
        </template>
      </el-table-column>

      <el-table-column prop="name" label="姓名" width="180"> </el-table-column>
      <el-table-column prop="address" label="地址"> </el-table-column>
    </el-table>
    <div class="tools">
      <el-button @click="setCurrent(tableData[1])">选中第二行</el-button>
      <el-button @click="setCurrent()">取消选择</el-button>
    </div>
  </div>
</template>

<script>
module.exports = {
  props: {
    tableData: {
      type: Array,
      default: () => [],
    },
  },
  data() {
    return {
      currentRow: null,
    };
  },
  methods: {
    // setCurrent(row) {
    // 	this.$refs.singleTable.setCurrentRow(row); // 设置当前选中行
    // },
    // 问题：按钮不能随鼠标点击某一行而一起变化  -- 解决
    setCurrent(row) {
      if (row) {
        this.$refs.singleTable.setCurrentRow(row); // 设置当前选中行
        // console.log('111',row)
        this.currentRow = row.date;
      } else {
        this.$refs.singleTable.setCurrentRow();
        this.currentRow = null;
      }
    },
  },
};
</script>
<style scoped>
.main {
  width: 60%;
  margin: 0 auto;
}

.tools {
  margin-top: 20px;
  text-align: center;
}
</style>
