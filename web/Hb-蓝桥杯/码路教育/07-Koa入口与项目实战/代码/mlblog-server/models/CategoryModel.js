
// 分类模型模块⽐较简单，只需要 name 和 keyword 字段即可

// 1.引入mongoose
const mongoose = require('mongoose')

// 2.字义Schema(描述文档结构)
const categorySchema = new mongoose.Schema({
  name: { type: String, require: true },//分类名称
  keyword: { type: String, required: true }, // 分类关键字
})

// 3.定义Model(与集合对应,可以操作集合)
const CategoryModel = mongoose.model('Category', categorySchema);

// 4.向外暴露model
module.exports = CategoryModel;