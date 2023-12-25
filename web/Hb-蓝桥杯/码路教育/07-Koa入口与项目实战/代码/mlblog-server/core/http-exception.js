// 如果有对应的错误，直接抛出错误
// 当出现任何的错误时，我们需要错误处理中间件来处理

// msg为异常信息，errorCode为错误码(开发人员内部约定),code为HTTP状态码
class HttpException extends Error {
	constructor(msg = "服务器异常", errorCode = 10000, code = 400) {
		super();
		this.errorCode = errorCode;
		this.code = code;
		this.errorMessage = msg;
	}
}
//参数错误
class ParameterException extends HttpException {
	constructor(msg, errorCode) {
		super();
		this.code = 400;
		this.errorMessage = msg || "参数错误";
		this.errorCode = errorCode || 10000;
	}
}
//认证失败
class AuthFailed extends HttpException {
	constructor(msg, errorCode) {
		super();
		this.code = 401;
		this.errorMessage = msg || "授权失败";
		this.errorCode = errorCode || 10004;
	}
}
//404
class NotFound extends HttpException {
	constructor(msg, errorCode) {
		super();
		this.code = 404;
		this.errorMessage = msg || "404找不到";
		this.errorCode = errorCode || 10005;
	}
}
//禁止访问
class Forbidden extends HttpException {
	constructor(msg, errorCode) {
		super();
		this.code = 403;
		this.errorMessage = msg || "禁止访问";
		this.errorCode = errorCode || 10006;
	}
}
//xxx已存在   Existing翻译过来就是存在的意思
class Existing extends HttpException {
	constructor(msg, errorCode) {
		super();
		this.code = 412; // 412表示xxx已存在
		this.errorMessage = msg || "已存在";
		this.errorCode = errorCode || 10006;
	}
}

module.exports = {
	HttpException,
	ParameterException,
	AuthFailed,
	NotFound,
	Forbidden,
	Existing,
};
