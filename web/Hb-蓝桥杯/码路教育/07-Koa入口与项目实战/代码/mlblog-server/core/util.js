const jwt = require('jsonwebtoken');

// 在后端登录接口中，如果密码验证成功，则使用jwt模块生成token
// 颁布令牌  generateToken生成令牌
const generateToken = function(_id) {
	const secretKey = global.config.security.secretKey
	const expiresIn = global.config.security.expiresIn
	const token = jwt.sign({
		data: _id, // 由于签名不是加密,令牌不要存放敏感数据
		exp: expiresIn // 过期时间 24小时
	}, secretKey)
	return token
}
module.exports = {
	generateToken
}
