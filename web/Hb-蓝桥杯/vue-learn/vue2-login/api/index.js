import instance from './request'

// get接口
export function SelectableGetData() {
	return instance({
		url: '/field/selectAll',
		method: 'get',
	})
}

// post接口  普通传参
export function LoginPostData(email, password) {
	return instance({
		url: '/Login',
		method: 'post',
		data: {
			email,
			password
		}
	})
}

// 当后端是query的时候前端就要使用params进行传参
export function DelTablePostData(id) {
	return instance({
		url: '/delTable',
		method: 'post',
		params: {
			id
		}
	})
}
