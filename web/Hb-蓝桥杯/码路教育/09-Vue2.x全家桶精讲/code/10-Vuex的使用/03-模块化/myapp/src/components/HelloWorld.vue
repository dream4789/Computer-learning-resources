<template>
	<div class="hello">
		<div>
			{{name}}
			<button @click="incrementFun">{{count}}</button>
			{{getCount}}
		</div>
		<div>
			{{nameA}}
			<button @click="incrementFunA">{{countA}}</button>
			{{getCountA}}
		</div>
		<div>
			{{nameB}}
			<button @click="incrementFunB">{{countB}}</button>
			{{getCountB}}
		</div>
	</div>
</template>

<script>
	import {
		mapState,
		mapMutations,
		mapActions,
		mapGetters
	} from 'vuex'

	export default {
		name: 'HelloWorld',
		data() {
			return {
				msg: 'Welcome to Your Vue.js App'
			}
		},
		computed: {
			...mapState({
				count: state => state.count,
				name: state => state.name,
				countA: state => state.moduleA.countA,
				nameA: state => state.moduleA.nameA,
				countB: state => state.moduleB.countB,
				nameB: state => state.moduleB.nameB
			}),
			...mapGetters([
				'getCount',
				'getCountA',
				'getCountB'
			])
		},
		methods: {
			...mapMutations([
				'increment',
				'incrementA',
				'incrementB'
			]),
			...mapActions([
				'incrementAsync',
				'incrementAsyncB',
				'incrementAsyncB'
			]),
			incrementFun() {
				this.increment({
					amount: 1
				})
				console.log(this.$store.state);
			},
			incrementFunA() {
				this.incrementA({
					amount: 1
				})
			},
			incrementFunB() {
				this.incrementB({
					amount: 1
				})
			}
		}
	}
</script>

<style scoped>
</style>
