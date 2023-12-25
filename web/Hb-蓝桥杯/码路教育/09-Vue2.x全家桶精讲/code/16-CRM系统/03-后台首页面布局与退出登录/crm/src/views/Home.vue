<template>
  <el-container>
    <el-header>
      <el-row>
        <el-col :span="6">
          <h1>码路CRM系统</h1>
        </el-col>
        <el-col :span="3" :offset="15">
          <el-dropdown>
            <span class="el-dropdown-link">
              欢迎:admin<i class="el-icon-arrow-down el-icon--right"></i>
            </span>
            <el-dropdown-menu slot="dropdown">
              <el-dropdown-item
                ><span @click="logout">退出</span></el-dropdown-item
              >
              <el-dropdown-item><span>设置</span></el-dropdown-item>
            </el-dropdown-menu>
          </el-dropdown>
        </el-col>
      </el-row>
    </el-header>
    <el-container>
      <el-aside width="200px">Aside</el-aside>
      <el-container>
        <el-main>Main</el-main>
        <el-footer>Footer</el-footer>
      </el-container>
    </el-container>
  </el-container>
</template>

<script>
export default {
  name: "HomeView",
  methods: {
    async logout() {
      let res = await this.$http.get("/api/user/logout");
      if (res.data.code == 1) {
        // 1)把sessionStorage中的数据清空
        sessionStorage.removeItem("username");
        // 2)提示一下
        this.$message.success(res.data.message);
        // 3)回到登录页面
        this.$router.replace("/login");
      }
    },
  },
  components: {},
};
</script>

<style scoped lang="less">
.el-container {
  height: 100%;
  .el-header,
  .el-footer {
    height: 60px;
    background-color: gold;
    line-height: 60px;
    color: #333;
  }
  h1 {
    font-size: 26px;
    font-weight: bold;
  }
}
</style>
