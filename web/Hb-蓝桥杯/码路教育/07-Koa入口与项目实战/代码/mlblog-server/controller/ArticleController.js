const {
	articleValidator
} = require("../validators/article");
const ArticleModel = require("../models/ArticleModel")
const CommentController = require("./CommentController");
const res = require("../core/helper.js")
const config = require("../config/index.js")

class ArticleController {
	// 创建文章
	static async create(ctx, next) {
		articleValidator(ctx)

		const {
			title
		} = ctx.request.body;

		const hasArticle = await ArticleModel.findOne({
			title
		})
		if (hasArticle) {
			throw new global.errs.Existing("文章标题已存在，换个吧~")
		}

		await ArticleModel.create(ctx.request.body)
		ctx.body = res.success("创建成功")
	}

	// 获取文章列表
	//   1）获取所有文章
	//   2）根据某个分类，获取某个分类下的所有的文章
	//   3）根据关键字，获取含有此关键字的文章
	static async getArticleList(ctx, next) {
		const {
			category_id = null,
				pageIndex = 1,
				pageSize = 10,
				keyword
		} = ctx.query
		let filter = {};
		if (category_id) {
			filter = {
				category_id,
			};
		}
		// 得到数据库中总的文章数
		const totalSize = await ArticleModel.find().countDocuments();

		const articleList = await ArticleModel
			.find(filter)
			.skip(parseInt(pageIndex - 1) * parseInt(pageSize))
			.limit(+pageSize)
			.or([
				//   模糊搜索查询    正则  RegExp是正则类   node   new EegExp("node", "i")
				{
					// 匹配匹配
					keyword: {
						$regex: new RegExp(keyword, "i"),
					},
				},
			])
			.sort({
				_id: -1
			})
			.populate("category_id"); // //连表查询

		ctx.body = res.json({
			content: articleList,
			pageIndex: parseInt(pageIndex),
			pageSize: parseInt(pageSize),
			totalSize,
		});
	}

	// 更新文章
	static async updateArticleById(ctx, next) {
		const _id = ctx.params._id;

		const article = await ArticleModel.findByIdAndUpdate({
			_id
		}, ctx.request.body);

		if (!article) {
			throw new global.errs.NotFound("没有找到相关文章")
		}
		ctx.body = res.json("文章更新成功")
	}

	// 根据ID获取文章详情
	// static async getArticleDetailById(ctx, next) {
	//     const _id = ctx.params._id;
	//     const articleDetail = await ArticleModel.findById({ _id }).populate("category_id");  //连表查询
	//     if (!articleDetail) {
	//         throw new global.errs.NotFound("没有找到相关文章")
	//     }
	//     await ArticleModel.findByIdAndUpdate({ _id }, { browse: ++articleDetail.browse })
	//     // ==============> todo:
	//     //   获取文章下的所有的评论
	//     const commentList = []; // 现在评论内容是空
	//     ctx.body = res.json({
	//         articleDetail,
	//         commentList
	//     })
	// }

	// 根据ID删除文章
	static async deleteArticleById(ctx, next) {
		const _id = ctx.params._id;

		const article = await ArticleModel.findByIdAndDelete({
			_id
		})

		if (!article) {
			throw new global.errs.NotFound("没有找到相关文章")
		}
		ctx.body = res.json("文章删除成功")
	}

	// 上传文章封面
	static async uploadCoverImg(ctx, next) {
		let imgPath = config.host + ":" + config.port + "/" + "images/" + ctx.req.file.filename;
		// ctx.body = res.json(imgPath)
		ctx.body = res.json(ctx.req.file.filename)
	}

	// 根据ID获取文章详情 
	static async getArticleDetailById(ctx, next) {
		const _id = ctx.params._id;
		//   文章详情的内容
		const articleDetail = await ArticleModel.findById({
			_id
		}).populate(
			"category_id"
		);
		if (!articleDetail) throw new global.errs.NotFound("没有找到相关分类");
		// 更新文章浏览器数 browse
		await ArticleModel.findByIdAndUpdate({
			_id
		}, {
			browse: ++articleDetail.browse
		});
		const {
			data,
			pageIndex,
			pageSize,
			totalSize
		} =
		await CommentController.targetComment({
			target_id: articleDetail._id
		});

		ctx.body = res.json({
			articleDetail,
			commentList: data,
			pageIndex,
			pageSize,
			commentCount: totalSize,
			totalSize,
		});
	}
}

// 导出去一个类
module.exports = ArticleController;
