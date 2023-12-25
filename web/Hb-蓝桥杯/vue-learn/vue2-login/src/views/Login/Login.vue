<template>
	<!-- 登录 -->
	<div>
		<el-container>
			<el-main>
				<div class="box">
					<el-form :model="user" :rules="rules" ref="user" label-width="100px" class="demo-ruleForm">
						<el-form-item label="用户名" prop="email">
							<el-input v-model="user.email"></el-input>
						</el-form-item>
						<el-form-item label="密码" prop="pass">
							<el-input type="password" v-model="user.password"></el-input>
						</el-form-item>
						<el-form-item>
							<el-button type="primary" @click="login">登录</el-button>
						</el-form-item>
					</el-form>
				</div>
			</el-main>
		</el-container>
	</div>
</template>

<script>
	import {
		LoginPostData
	} from '../../../api/index' // 后端登录接口
	export default {
		data() {
			return {
				rules: {
					email: [{
							required: true,
							message: "请输入用户名",
							trigger: "blur"
						},
						{
							min: 3,
							max: 20,
							message: "长度在 3 到 20 个字符",
							trigger: "blur"
						},
					],
					password: [{
							required: true,
							message: "请输入密码",
							trigger: "blur"
						},
						{
							min: 3,
							max: 5,
							message: "长度在 3 到 5 个字符",
							trigger: "blur"
						},
					],
				},
				user: {
					email: '',
					password: ''
				},
				userToken: '', // 用于存储从后台获取的token
			};
		},
		methods: {
			login() {
				// 登录接口
				LoginPostData(this.user.email, this.user.password)
					.then((res) => {
						// 将token存到userToken中     
						this.userToken = res.data.data.token
						console.log('token--->', this.userToken)
						
						// 将token本地存储到回话中
						localStorage.setItem('token', this.userToken);
						
						// 如果code为200则跳转到NewReport页面
						if (res.data.code === 200) {
							this.$router.push({
								name: 'NewReport'
							})
							this.$message({
								message: '恭喜你，登录成功',
								type: 'success'
							});
						} else {
							this.$message.error(res.data.data);
						}
					})
					.catch(err => {
						console.log('err-->', err);
					})
			}
		},
	};
</script>
