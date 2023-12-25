//models/ArticleModel.js
// 1.引入mongoose
const mongoose = require('mongoose')

// 2.字义Schema(描述文档结构)
const ArticleSchema = new mongoose.Schema({
  title: { type: String, require: true },//文章标题
  author: { type: String, required: true }, // 作者
  description: { type: String, required: true }, // 文章简介
  keyword: { type: String, required: true }, // 文章内容
  content: { type: String, required: true }, // 文章关键字
  cover: { type: String, required: true }, // 文章封面
  browse: { type: Number, default: 0 }, //文章浏览数

  // 一个分类下有多篇文章文章 属于1对多关系
  //分类表：主表 文章表：从表
  //关联分类
  category_id: {
    type: mongoose.Schema.Types.ObjectId,
    //ref属性表示引用 可以直接引用Category模型
    ref: 'Category'
  }
  // 为表添加 创建的时间和更新的时间
}, { timestamps: { createdAt: 'created', updatedAt: 'updated' } })

// 3.定义Model(与集合对应,可以操作集合)
const ArticleModel = mongoose.model('Article', ArticleSchema);

// 4.向外暴露model
module.exports = ArticleModel;