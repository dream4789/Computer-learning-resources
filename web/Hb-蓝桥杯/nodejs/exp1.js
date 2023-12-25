var app = {
	name: 'app_name',
	version: '1.0.0',
	sayName: function(name){
		console.log(this.name);
	}
}
// module.exports = app;

export default {
	app,
}