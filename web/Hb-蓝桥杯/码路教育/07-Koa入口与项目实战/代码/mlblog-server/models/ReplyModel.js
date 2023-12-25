// 1.引入mongoose
const mongoose = require('mongoose')
const moment = require('moment')

// 2.字义Schema(描述文档结构)
const ReplySchema = new mongoose.Schema({
  nickname: { type: String, require: true },//评论人昵称
  content: { type: String, require: true }, //评论内容
  createAt: {
    type: Date,
    require: true,
    default: Date.now,
    // 处理时间 
    get(val) {
      return moment(val).format('YYYY-MM-DD HH:mm:ss')
    }
  },
  comment_id: {
    type: mongoose.Schema.Types.ObjectId,
    // 引用
    ref: 'Comment'
  }
})
//只有将Schema设置如下配置，才能调用get方法
ReplySchema.set('toJSON', { getters: true });
// 3.定义Model(与集合对应,可以操作集合)
const ReplyModel = mongoose.model('Reply', ReplySchema);

// 4.向外暴露model
module.exports = ReplyModel;