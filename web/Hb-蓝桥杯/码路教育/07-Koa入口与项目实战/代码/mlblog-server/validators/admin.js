function registerValidator(ctx) {
	console.log('开始校验!')//,ctx);
	ctx
		.validateBody("nickname")
		.required("用户名是必须的") //只是要求有uname字段
		.isString() //确保输入的字段是字符串或者可以转换成字符串
		.trim()
		.isLength(3, 16, "用户名长度必须是3~16位");
	console.log('校验密码');
	ctx
		.validateBody("password")
		.required("密码是必填项")
		.isLength(6, 16, "密码必须是6~16位字符")
		.match(
			/^(?![0-9]+$)(?![a-zA-Z]+$)[0-9A-Za-z]/,
			"密码长度必须在6~22位之间，包含字符、数字和 _ "
		);
	console.log('再次校验密码2');
	ctx
		.validateBody("password2")
		.required("确认密码是必填项")
		.eq(ctx.vals.password, "两次密码不一致");

	console.log('校验结束');
}

function loginValidator(ctx) {
	console.log('登陆验证中....')
	ctx
		.validateBody("password")
		.required("密码是必须的")
		.trim()
		.isLength(6, 16, "密码至少6个字符，最多16个字符")
		.match(
			/^(?![0-9]+$)(?![a-zA-Z]+$)[0-9A-Za-z]/,
			"密码长度必须在6~22位之间，包含字符、数字和 _ "
		);
	console.log('登录验证通过....');
}
module.exports = {
	registerValidator,
	loginValidator
};
