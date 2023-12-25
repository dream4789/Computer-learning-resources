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
        <template slot-scope="scope">{{ scope.row.birthday | formatData }}</template>
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
    <el-row class="footer">
      <el-col :span="4" align="left">
        <el-button
          type="danger"
          size="small"
          :disabled="isBatchDel"
          @click="bandleBatchDel"
        >
          批量删除
        </el-button>
      </el-col>
      <el-col :span="20" align="right">
        <el-pagination
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
          :page-sizes="[5, 10, 15, 20]"
          :page-size="pagesize"
          layout="total, sizes, prev, pager, next"
          :total="total"
        >
        </el-pagination>
      </el-col>
    </el-row>
    <!-- 批量删除和分页 end -->

    <!-- 添加用户弹框 start -->
    <UserAdd
      v-if="showAdd"
      @close="handleAddClose"
      @handleAddSuccess="handleAddSuccess"
    ></UserAdd>
    <!-- 添加用户弹框 end -->
  </div>
</template>

<script>
import UserAdd from "./UserAdd.vue";
import moment from "moment";
export default {
  name: "User",
  components: {
    UserAdd,
  },
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
      isBatchDel: true, // 批量删除按钮是否可以点击，默认不能点击
      showAdd: false, // 控制UserAdd组件是否显示
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
    handleAdd() {
      this.showAdd = true;
    },
    // 点击编辑
    handleEdit() {},
    // 点击删除
    handleDelete() {},
    // 计算表格的高度
    getHeight() {
      return window.innerHeight - 280;
    },
    // 点击批量删除
    bandleBatchDel() {},
    // 改变一页显示多少条
    handleSizeChange(val) {
      // 选中的一页显示多少条
      this.pagesize = val;
      this.getUserList();
    },
    // handleCurrentChange
    handleCurrentChange(val) {
      // 代表点击的是第几页
      // console.log(val);
      this.pageno = val;
      // 页码变了，重新发送ajax
      this.getUserList();
    },
    handleAddClose(flag) {
      this.showAdd = flag;
    },
    // 添加成功回调
    handleAddSuccess(obj) {
      this.showAdd = obj.done;
      if (obj.msg === "success") {
        this.$message.success("新增用户成功！");
        // 需要重新发送ajax请求，获取最新数据
        this.getUserList();
      }
    },
  },
  filters:{
    formatData(val){
      return moment(val).format("YYYY-MM-DD")
    }
  }
};
</script>

<style lang="less" scoped>
.tool-bar {
  margin-bottom: 20px;
  .el-col {
    margin-right: 10px;
  }
}
.footer {
  margin-top: 20px;
}
</style>