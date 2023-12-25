const UserModule = {
    namespaced: true,
    state: () => ({
        username: '11',
        token: null,
    }),
    getters: {
        username(state) {
            return state.username
        },
        token(state) {
            return state.token
        }
    },
    mutations: {
        login(state, { username, token }) {
            state.username = username
            state.token = token
        },
    },
}