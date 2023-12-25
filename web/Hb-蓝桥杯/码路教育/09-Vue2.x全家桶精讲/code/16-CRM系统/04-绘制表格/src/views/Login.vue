<template>
  <div class="login-wrapper">
    <!-- ref写在组件上是为了获取vc -->
    <!-- 把class写在组件上,就意味把class写在了组件模板最外层的标签上 -->
    <!-- 除了我们添加的login-form之外,还添加了el-form这个class -->
    <el-form ref="ruleForm" :rules="rules" :model="user" class="login-form">
      <h1>码路CRM系统</h1>
      <el-form-item prop="username">
        <!-- v-model写在了组件上 -->
        <!-- v-model是 :value  和  @input语法糖 -->
        <!-- 在组件上写一个v-model等价于在组件上写一个自定义属性和自定义事件 -->
        <!-- <el-input :value="123" @input="fn">  -->
        <el-input
          v-model="user.username"
          placeholder="请输入用户名"
          type="text"
        ></el-input>
      </el-form-item>
      <el-form-item prop="password">
        <el-input
          v-model="user.password"
          placeholder="请输入密码"
          type="password"
        ></el-input>
      </el-form-item>
      <el-form-item>
        <el-checkbox v-model="user.checked">记住密码</el-checkbox>
      </el-form-item>
      <el-form-item>
        <!-- @click="" 叫自定义事件 -->
        <el-button type="primary" @click="handleLogin">登录</el-button>
      </el-form-item>
    </el-form>
  </div>
</template>

<script>
export default {
  data() {
    return {
      user: {
        username: "",
        password: "",
        checked: "",
      },
      rules: {
        username: [
          { required: true, message: "请输入用户名", trigger: "blur" },
          { min: 3, max: 5, message: "长度在 3 到 5 个字符", trigger: "blur" },
        ],
        password: [{ required: true, message: "请输入密码", trigger: "blur" }],
      },
    };
  },
  mounted() {
    this.user.checked = JSON.parse(localStorage.getItem("checked"));

    this.user.username = localStorage.getItem("username");
    this.user.password = localStorage.getItem("password");
  },
  methods: {
    handleLogin() {
      this.$refs.ruleForm.validate(async (valid) => {
        if (valid) {
          let res = await this.$http.post("/api/user/login", {
            username: this.user.username,
            password: this.user.password,
          });
          if (res.data.code === 1) {
            // 登录成功

            // 1)把用户名存储在sessStorage
            sessionStorage.setItem("username", this.user.username);

            // 2)是否记住密码
            if (this.user.checked) {
              localStorage.setItem("username", this.user.username);
              localStorage.setItem("password", this.user.password);
              localStorage.setItem("checked", this.user.checked);
            } else {
              localStorage.removeItem("username");
              localStorage.removeItem("password");
              localStorage.removeItem("checked");
            }

            // 3)给出成功提示
            // this.$message({
            //   message: "恭喜你，登录成功",
            //   type: "success",
            // });
            this.$message.success("恭喜你，登录成功");

            // 3)跳到后台首页
            this.$router.replace("/home");
          }
        } else {
          console.log("error submit!!");
          return false;
        }
      });
    },
  },
};
</script>

<style lang="less" scoped>
.login-wrapper {
  height: 100%;
  display: flex;
  justify-content: center;
  align-items: center;
  .login-form {
    width: 500px;
    height: 400px;
    // background-color: gold;
    box-sizing: border-box;
    box-shadow: 1px 1px 15px #eee;
    padding: 30px;
    border-radius: 8px;
    h1 {
      font-size: 32px;
      font-weight: bold;
      text-align: center;
      margin-bottom: 30px;
    }
    .el-button {
      width: 100%;
    }
  }
}
</style>