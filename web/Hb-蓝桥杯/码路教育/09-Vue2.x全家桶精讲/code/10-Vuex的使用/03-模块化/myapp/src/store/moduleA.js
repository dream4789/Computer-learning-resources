// moduleA.js
export const moduleA = {
    state: {
        nameA: "moduleA",
        countA: 0
    },
    mutations: {
        incrementA(state, payload) {
            state.countA += payload.amount;
            console.log("mutations" + state.nameA)
        }
    },
    actions: {
        incrementAsyncA({ commit }, products) {
            setTimeout(() => {
                commit('incrementA', products)
                console.log("actions" + state.nameA)
            }, 1000)
        }
    },
    getters: {
        getCountA: (state, getters) => {
            console.log("getter" + state.nameA)
            return state.nameA + "被调用了" + state.countA + "次"
        }
    }
}
