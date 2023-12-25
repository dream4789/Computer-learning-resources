// moduleB.js
export const moduleB = {
    state: {
        nameB: "moduleB",
        countB: 0
    },
    mutations: {
        incrementB(state, payload) {
            state.countB += payload.amount;
            console.log("mutations" + state.nameB)
        }
    },
    actions: {
        incrementAsyncB({ commit }, products) {
            setTimeout(() => {
                commit('incrementB', products)
                console.log("actions" + state.nameB)
            }, 1000)
        }
    },
    getters: {
        getCountB: (state, getters) => {
            console.log("getter" + state.nameB)
            return state.nameB + "被调用了" + state.countB + "次"
        }
    }
}
