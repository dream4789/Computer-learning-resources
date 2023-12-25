// 我们要开很多接口，每一次都要给响应体，都需要ctx.body = {...}
// 所以我们封装返回结果帮助模块

class Resolve {
	success(msg = "success", errorCode = 1, code = 200) {
		return {
			msg,
			errorCode,
			code,
		};
	}
	json(data, msg = "success", errorCode = 1, code = 200) {
		return {
			msg,
			errorCode,
			code,
			data,
		};
	}
	error(msg = "error", errorCode = 0, code = 404) {
		return {
			msg,
			errorCode,
			code,
		};
	}
}
const res = new Resolve();
module.exports = res;
