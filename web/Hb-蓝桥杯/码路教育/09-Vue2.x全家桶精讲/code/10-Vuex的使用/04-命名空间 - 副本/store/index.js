const store = new Vuex.Store({
    modules: {
        base: BaseModule,
        user: UserModule,
    },
})
window.$store = store