const Router = require("@koa/router");
const jwtAuth = require("koa-jwt")
const CommentController = require("../controller/CommentController")
const config = require("../config/index.js")

const router = new Router();


// 添加评论  jwtAuth({ secret: config.security.secretKey }), 
router.post("/comment", CommentController.createComment)

// 获取所有评论  jwtAuth({ secret: config.security.secretKey }), 
router.get("/comment", CommentController.getCommentList)

// 获取评论详情  jwtAuth({ secret: config.security.secretKey }), 
router.get("/comment/:_id", CommentController.getCommentDetailById)

// 更新评论  jwtAuth({ secret: config.security.secretKey }), 
router.put("/comment/:_id", CommentController.updateCommentById)

// 删除评论  jwtAuth({ secret: config.security.secretKey }), 
router.delete("/comment/:_id", CommentController.deleteCommentById)

// 获取文章目标的评论接口(带回复和分页)
router.get("/comment/target/list", CommentController.getTargetComment);

module.exports = router;