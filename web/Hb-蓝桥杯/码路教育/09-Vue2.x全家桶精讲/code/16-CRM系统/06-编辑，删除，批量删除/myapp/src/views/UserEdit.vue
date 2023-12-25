<template>
  <el-dialog title="编辑用户" :visible.sync="dialogFormVisible" @close="close">
    <el-form :model="user" ref="userForm" :rules="rules">
      <el-form-item label="姓名" label-width="80px" prop="name">
        <el-input v-model="user.name"></el-input>
      </el-form-item>
      <el-form-item label="性别" label-width="80px">
        <el-radio v-model="user.sex" :label="0">男</el-radio>
        <el-radio v-model="user.sex" :label="1">女</el-radio>
      </el-form-item>
      <el-form-item label="年龄" label-width="80px">
        <el-input-number
          v-model="user.age"
          :min="1"
          :max="100"
        ></el-input-number>
      </el-form-item>
      <el-form-item label="生日" label-width="80px">
        <el-date-picker
          v-model="user.birthday"
          type="date"
          placeholder="选择日期"
        ></el-date-picker>
      </el-form-item>
      <el-form-item label="地址" label-width="80px">
        <el-input v-model="user.address"></el-input>
      </el-form-item>
    </el-form>
    <div slot="footer" class="dialog-footer">
      <el-button @click="handleCancel">取 消</el-button>
      <el-button type="primary" @click="handleSubmit">确 定</el-button>
    </div>
  </el-dialog>
</template>

<script>
export default {
  name: "UserAdd",
  props: ["currentUser"],
  mounted() {
    // 实现数据回显
    this.user = Object.assign({}, this.currentUser);
  },
  data() {
    return {
      dialogFormVisible: true,
      user: {
        name: "",
        sex: 1,
        age: 0,
        birthday: "",
        address: "",
      },
      rules: {
        name: [
          { required: true, message: "请输入用户名", trigger: "blur" },
          { min: 3, max: 5, message: "长度在 3 到 5 个字符", trigger: "blur" },
        ],
      },
    };
  },
  methods: {
    // 点击取消
    handleCancel() {
      this.$emit("close", false);
    },
    // 点击确定
    handleSubmit() {
      this.$refs.userForm.validate(async (valid) => {
        if (valid) {
          let res = await this.$http.post("/api/user/update", {
            ...this.user,
          });
          if (res.data.code === 1) {
            this.$emit("handleEditSuccess", { msg: "success", done: false });
          }
        } else {
          console.log("error submit!!");
          return false;
        }
      });
    },
    close() {
      this.$emit("close", false);
    },
  },
};
</script>

<style lang="less" scoped>
</style>