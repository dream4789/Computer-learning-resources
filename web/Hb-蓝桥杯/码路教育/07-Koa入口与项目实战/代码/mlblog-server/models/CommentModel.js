// 1.引入mongoose
const mongoose = require("mongoose");

// 2.字义Schema(描述文档结构)
const CommentSchema = new mongoose.Schema({
  nickname: { type: String, require: true }, //评论人昵称
  content: { type: String, require: true }, //评论内容
  target_id: { type: String, require: true }, //评论目标文章的id
});

// 3.定义Model(与集合对应,可以操作集合)
const CommentModel = mongoose.model("Comment", CommentSchema);

// 4.向外暴露model
module.exports = CommentModel;
