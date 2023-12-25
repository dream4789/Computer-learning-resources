const AdvertiseModel = require("../models/AdvertiseModel");
const {
	advertiseValidator
} = require("../validators/advertise");
const res = require("../core/helper");
class ReplyController {
	// 创建广告
	static async createAdvertise(ctx, next) {
		advertiseValidator(ctx);
		const {
			title
		} = ctx.request.body;
		let hasAdvertise = await AdvertiseModel.findOne({
			title
		});
		if (hasAdvertise) {
			throw new global.errs.Existing("广告已存在");
		}
		let advertise = await AdvertiseModel.create(ctx.request.body);
		ctx.body = res.json(advertise);
	}

	// 获取广告列表
	static async getAdvertiseList(ctx, next) {
		let advertiseList = await AdvertiseModel.find();
		ctx.status = 200;
		ctx.body = res.json(advertiseList);
	}

	// 获取广告详情
	static async getAdvertiseDetailById(ctx, next) {
		const _id = ctx.params._id;
		const advertiseDetail = await AdvertiseModel.findById({
			_id
		});
		if (!advertiseDetail) {
			throw new global.errs.NotFound("此广告不存在");
		}
		ctx.status = 200;
		ctx.body = res.json(advertiseDetail);
	}

	// 更新广告
	static async updateAdvertiseById(ctx, next) {
		const _id = ctx.params._id;
		const advertiseDetail = await AdvertiseModel.findByIdAndUpdate({
				_id
			},
			ctx.request.body
		);
		if (!advertiseDetail) {
			throw new global.errs.NotFound("此广告不存在");
		}
		ctx.status = 200;
		ctx.body = res.success("更新广告成功");
	}

	// 删除广告
	static async deleteAdvertiseById(ctx, next) {
		const _id = ctx.params._id;
		const advertiseDetail = await AdvertiseModel.findByIdAndDelete({
			_id
		});
		if (!advertiseDetail) {
			throw new global.errs.NotFound("此广告不存在");
		}
		ctx.status = 200;
		ctx.body = res.success("删除广告成功");
	}
}
module.exports = ReplyController;
