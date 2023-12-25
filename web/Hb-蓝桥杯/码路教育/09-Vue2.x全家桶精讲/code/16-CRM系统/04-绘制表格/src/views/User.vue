<template>
  <div>
    <!-- 搜索头部 start -->
    <el-row class="tool-bar">
      <el-col :span="6">
        <el-input
          class="tool-input"
          v-model.trim="name"
          placeholder="请输入你要搜索的用户名"
        ></el-input>
      </el-col>
      <el-col :span="6">
        <el-button type="primary" @click="handleQuery">搜索</el-button>
        <el-button type="primary" @click="handleAdd">新增</el-button>
      </el-col>
    </el-row>
    <!-- 搜索头部 end -->

    <!-- 表格 start -->
    <!-- data是提供数据源的 -->
    <el-table
      :data="dataList"
      border
      :height="getHeight()"
      v-loading="isLoading"
    >
      <el-table-column type="selection" width="55" align="center">
      </el-table-column>
      <el-table-column type="index" label="#" width="80" align="center">
      </el-table-column>
      <el-table-column prop="name" label="姓名" width="120" align="center">
      </el-table-column>
      <el-table-column prop="sex" label="性别" width="120" align="center">
        <!-- scope.row 代表当前这一行数据 -->
        <template slot-scope="scope">{{
          scope.row.sex ? "女" : "男"
        }}</template>
      </el-table-column>
      <el-table-column
        prop="age"
        label="年龄"
        width="120"
        align="center"
      ></el-table-column>
      <el-table-column prop="birthday" label="生日" width="120" align="center">
      </el-table-column>
      <el-table-column prop="address" label="地址" align="center">
      </el-table-column>
      <el-table-column label="操作">
        <template slot-scope="scope">
          <el-button size="mini" @click="handleEdit(scope.$index, scope.row)"
            >编辑</el-button
          >
          <el-button
            size="mini"
            type="danger"
            @click="handleDelete(scope.$index, scope.row)"
            >删除</el-button
          >
        </template>
      </el-table-column>
    </el-table>
    <!-- 表格 end -->

    <!-- 批量删除和分页 start -->
    <!-- 批量删除和分页 end -->
  </div>
</template>

<script>
export default {
  name: "User",
  props: [],
  created() {
    this.getUserList();
  },
  data() {
    return {
      name: "", // 搜索框中的数据
      dataList: [], // 数据源
      pageno: 1, // 第几页数据
      pagesize: 20, // 一页显示几条数据
      total: 0, // 总记录数
      isLoading: false, // 表格的loading效果
    };
  },
  methods: {
    // 获取用户列表数据
    async getUserList() {
      this.isLoading = true;
      let res = await this.$http.post("/api/user/list", {
        name: "",
        pageno: this.pageno,
        pagesize: this.pagesize,
      });
      if (res.data.code == 1) {
        this.dataList = res.data.list;
        this.total = res.data.total;
        this.isLoading = false;
      }
    },
    // 搜索
    handleQuery() {},
    // 新增
    handleAdd() {},
    // 点击编辑
    handleEdit() {},
    // 点击删除
    handleDelete() {},
    // 计算表格的高度
    getHeight() {
      return window.innerHeight - 280;
    },
  },
};
</script>

<style lang="less" scoped>
.tool-bar {
  margin-bottom: 20px;
  .el-col {
    margin-right: 10px;
  }
}
</style>