const {
	categoryValidator
} = require("../validators/category");
const CategoryModel = require("../models/CategoryModel")
const ArticleModel = require("../models/ArticleModel")
const res = require("../core/helper.js")

class CategoryController {
	// 创建分类
	static async create(ctx, next) {
		categoryValidator(ctx)

		const {
			name,
			keyword
		} = ctx.request.body;
		const hasCategory = await CategoryModel.findOne({
			name
		});
		if (hasCategory) {
			throw new global.errs.Existing("分类名已存在")
		}

		await CategoryModel.create({
			name,
			keyword
		});

		ctx.body = res.success("创建分类成功")
	}

	// 获取所有分类  
	// static async getCategoryList(ctx, next) {
	//     const { pageIndex = 1, pageSize = 10 } = ctx.query
	//     const totalSize = await CategoryModel.find().countDocuments();

	//     CategoryModel.find()

	//     const categoryList = await CategoryModel
	//         .find()
	//         .skip(parseInt(pageIndex - 1) * parseInt(pageSize))
	//         .limit(+pageSize)
	//         .sort({ _id: -1 });

	//     ctx.body = res.json({
	//         data: categoryList,
	//         totalSize,
	//         pageIndex: parseInt(pageIndex),
	//         pageSize: parseInt(pageSize)
	//     })
	// }

	// 获取所有分类   获取某个分类下的文章数
	static async getCategoryList(ctx, next) {
		// 抽取query传参，若没有则是默认值
		const {
			pageIndex = 1, pageSize = 10
		} = ctx.query;
		// 获取整个分类的总数
		const totalSize = await CategoryModel.find().countDocuments();
		const categoryList = await CategoryModel.find()
			.skip(parseInt(pageIndex - 1) * parseInt(pageSize))
			.limit(parseInt(pageSize))
			.sort({
				_id: -1,
			});
		//每个下面的文章数
		let artList = [];
		let listnum = 0;
		for (let i = 0; i < totalSize; i++) {
			listnum = await ArticleModel.find({
				category_id: categoryList[i]._id,
			}).countDocuments();
			artList.push(listnum);
			// console.log(listnum);
		}
		//循环将数组中的数据加到大树组的每一个对象属性上
		for (let i = 0; i < totalSize; i++) {
			categoryList[i]._doc.article_nums = artList[i];
		}
		ctx.body = res.json({
			data: categoryList,
			totalSize,
			pageIndex: parseInt(pageIndex),
			pageSize: parseInt(pageSize),
			artList,
		});
	}

	// 根据ID获取某个分类
	static async getCategoryDetailById(ctx, next) {
		const _id = ctx.params._id;
		const categoryDetail = await CategoryModel.findById({
			_id
		});

		if (!categoryDetail) {
			throw new global.errs.NotFound("没有找到相关的分类信息")
		}
		ctx.body = res.json({
			categoryDetail,
		})
	}

	// 更新分类
	static async updateCategoryById(ctx, next) {
		const _id = ctx.params._id;
		// console.log(_id);

		// 校验name和keyword
		categoryValidator(ctx)
		const {
			name,
			keyword
		} = ctx.request.body;

		// category是更新前的category
		const category = await CategoryModel.findByIdAndUpdate({
			_id
		}, {
			name,
			keyword
		});

		if (!category) {
			throw new global.errs.NotFound("没有找到相关分类")
		}

		ctx.body = res.json("更新成功")
	}

	// 删除分类
	static async deleteCategoryById(ctx, next) {
		const _id = ctx.params._id;

		// category是删除前的category
		const category = await CategoryModel.findByIdAndDelete({
			_id
		});

		if (!category) {
			throw new global.errs.NotFound("没有找到相关分类")
		}

		ctx.body = res.json("删除成功")
	}


}

// 导出去一个类
module.exports = CategoryController;
