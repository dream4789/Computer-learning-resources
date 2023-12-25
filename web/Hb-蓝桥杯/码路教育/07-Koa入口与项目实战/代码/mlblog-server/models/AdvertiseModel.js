const mongoose = require('mongoose');
const moment = require('moment')

const AdvertiseSchema = new mongoose.Schema({
	title: {
		type: String,
		require: true, //广告标题
	},
	link: {
		type: String,
		require: true,
	},
	createAt: {
		type: Date,
		require: true,
		default: Date.now,
		// 处理时间 
		get(val) {
			return moment(val).format('YYYY-MM-DD HH:mm:ss')
		}
	},
})
AdvertiseSchema.set('toJSON', {
	getters: true
});
const AdvertiseModel = mongoose.model('Advertise', AdvertiseSchema);
// 4.向外暴露model
module.exports = AdvertiseModel;
