/*
 * 本题示例登录界面，非作答区域
 */
const LoginTemplate = `
<div class="wrapper login-wrapper" style="width: 539px;">
    <div class="newsletter">
        <div>
            <h2> <slot /> </h2>
            <p>（例如: admin）</p>
        </div>
        <form>
            <div class="c-input-group">
                <label for="newsletter" class="c-label sr-only"></label>
                <input v-model="name" type="text" class="c-input" id="newsletter" placeholder="请输入用户名">
            </div>
            <button @click="login" class="c-button">确认</button>
        </form>
    </div>
</div>
`
Vue.component('Login', {
	name: 'Login',
	template: LoginTemplate,
	props: {},
	data() {
		return {
			name: '',
		}
	},
	watch: {},
	mounted() {},
	methods: {
		login(e) {
			this.$emit('confirm', this.name)
			e.preventDefault()
		},
	},
})
