// 请求
import axios from 'axios'

// create an axios instance   创建axios实例
const instance = axios.create({
	baseURL: 'http://localhost:8080', // api 的 base_url
	withCredentials: false //跨域时使用凭证，默认带上cookies
	// timeout: 2000, // request timeout  设置请求超时时间
})

// 添加请求拦截器，在请求头中加token
instance.interceptors.request.use(
	config => {
		//判断token是否存在
		if (localStorage.getItem('token')) {
			// 在请求头中添加token
			config.headers.token = localStorage.getItem('token');
		}
		return config;
	},
	error => {
		return Promise.reject(error);
	});

export default instance
