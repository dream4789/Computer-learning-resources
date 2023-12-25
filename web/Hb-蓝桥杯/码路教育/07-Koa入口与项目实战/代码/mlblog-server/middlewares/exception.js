// 错误处理中间件
// 捕获到错误，判断是什么类型的错误，然后给出对应的响应体

const {
	HttpException
} = require("../core/http-exception");
const bouncer = require("koa-bouncer");

// 当出现任何的错误时，我们需要错误处理中间件来处理
const catchError = async (ctx, next) => {
	try {
		await next();
	} catch (error) {
		console.log(error instanceof bouncer.ValidationError)
		// 判断校验类型错误
		if (error instanceof bouncer.ValidationError) {
			ctx.body = {
				name: error.name,
				message: error.message,
				request: `${ctx.method} ${ctx.path}`,
			};
			return;
		}
		// 401权限错误处理
		if (error.status === 401) {
			ctx.status = 401;
			ctx.body = {
				error_code: error.status,
				errorMessage: '请先登录',
				msg: error.originalError ? error.originalError.message : error.message,
				request: `${ctx.method} ${ctx.path}`,
			};
			return;
		}
		// 判断当前错误是否为Http请求错误
		const isHttpException = error instanceof HttpException;
		console.log(error)
		if (isHttpException) {
			// 设置状态码
			ctx.status = error.code;
			// 设置错误响应数据
			ctx.body = {
				errorMessage: error.errorMessage,
				error_code: error.errorCode,
				request: `${ctx.method} ${ctx.path}`,
			};
		} else {
			// 未知错误
			ctx.response.status = 500;
			ctx.body = {
				msg: "未知错误！",
				error_code: 9999,
				request: `${ctx.method} ${ctx.path}`,
			};
		}
	}
};
module.exports = catchError;
