const {
	replyValidator
} = require("../validators/reply");
const ReplyModel = require("../models/ReplyModel")
const CommentModel = require("../models/CommentModel")
const res = require("../core/helper.js")

class ReplyController {
	// 创建评论
	static async createReply(ctx, next) {
		replyValidator(ctx)

		const {
			comment_id
		} = ctx.request.body;

		let comment = await CommentModel.findById({
			_id: comment_id
		})

		if (!comment) {
			throw new global.errs.NotFound("没有找相关评论")
		}

		let reply = await ReplyModel.create(ctx.request.body)


		ctx.body = res.json(reply)
	}

	// 获取所有回复
	static async getReplyList(ctx, next) {
		const comment_id = ctx.query.comment_id;
		let replyList = null;
		if (comment_id) {
			replyList = await ReplyModel.find({
				comment_id
			})
		} else {
			replyList = await ReplyModel.find().sort({
				_id: -1
			})
		}

		ctx.body = res.json(replyList)
	}

	// 获取某条回复的详情
	static async getReplyDetailById(ctx, next) {
		const _id = ctx.params._id;
		let replyDetail = await ReplyModel.findById(_id);
		if (!replyDetail) {
			throw new global.errs.NotFound("没有相关的回复")
		}
		ctx.body = res.json(replyDetail)
	}

	// 修改，编辑，更新回复
	static async updateReplyById(ctx, next) {
		const _id = ctx.params._id;
		let reply = await ReplyModel.findByIdAndUpdate(_id, ctx.request.body);
		if (!reply) {
			throw new global.errs.NotFound("没有相关的回复")
		}
		ctx.body = res.success("修改回复成功")
	}

	// 删除评论
	static async deleteReplyById(ctx, next) {
		const _id = ctx.params._id;
		let reply = await ReplyModel.findByIdAndDelete(_id);
		if (!reply) {
			throw new global.errs.NotFound("没有相关的回复")
		}
		ctx.body = res.success("删除回复成功")
	}
}
// 导出去一个类
module.exports = ReplyController;
