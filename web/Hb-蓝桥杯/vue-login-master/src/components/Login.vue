<template>
  <div class="hello">
    <el-form :model="ruleForm" status-icon :rules="rules" ref="ruleForm" label-width="100px" class="demo-ruleForm">
      <el-form-item label="账号" prop="username">
        <el-input v-model.number="ruleForm.username"></el-input>
      </el-form-item>
      <el-form-item label="密码" prop="password">
        <el-input type="password" v-model="ruleForm.password" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="submitForm('ruleForm')">提交</el-button>
        <el-button @click="resetForm('ruleForm')">重置</el-button>
      </el-form-item>
    </el-form>
  </div>
</template>>

<script>
import axios from 'axios'
export default {
  data () {
    var checkUserName = (rule, value, callback) => {
      if (value === '') {
        callback(new Error('请输入账号'))
      } else {
        callback()
      }
    }
    var validatePassWord = (rule, value, callback) => {
      if (value === '') {
        callback(new Error('请输入密码'))
      } else {
        callback()
      }
    }
    return {
      ruleForm: {
        username: '',
        password: ''
      },
      rules: {
        username: [
          { validator: checkUserName, trigger: 'blur' }
        ],
        password: [
          { validator: validatePassWord, trigger: 'blur' }
        ]
      }
    }
  },
  methods: {
    submitForm (formName) {
      this.$refs[formName].validate((valid) => {
        var self = this
        axios.get('/user/login', {
          params: {
            username: self.ruleForm.username,
            password: self.ruleForm.password
          }
        }).then(function (response) {
          if (response.data.code === 1) {
            alert(response.data.data.dispaly_name)
          } else {
            alert(response.data.msg)
          }
        }).catch(function (error) {
          console.log(error.message)
        })
      })
    },
    resetForm (formName) {
      this.$refs[formName].resetFields()
    }
  }
}
</script>
