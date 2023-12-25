
const BaseModule = {
	// namespaced: true,
    state: () => ({
        welcome: '请输入用户名登录系统'
    }),
    getters: {
        welcome(state) {
            return state.welcome
        },
    },
    mutations: {
        say(state, content) {
            state.welcome = content
        },
    },
    actions: {}
}