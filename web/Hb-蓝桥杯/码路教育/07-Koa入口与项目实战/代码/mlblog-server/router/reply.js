const Router = require("@koa/router");
const jwtAuth = require("koa-jwt")
const ReplyController = require("../controller/ReplyController")
const config = require("../config/index.js")

const router = new Router();


// 添加回复  jwtAuth({ secret: config.security.secretKey }), 
router.post("/reply", ReplyController.createReply)

// 获取所有回复  jwtAuth({ secret: config.security.secretKey }), 
router.get("/reply", ReplyController.getReplyList)

// 获取回复详情  jwtAuth({ secret: config.security.secretKey }), 
router.get("/reply/:_id", ReplyController.getReplyDetailById)

// 获取回复详情  jwtAuth({ secret: config.security.secretKey }), 
router.put("/reply/:_id", ReplyController.updateReplyById)

// 获取回复详情  jwtAuth({ secret: config.security.secretKey }), 
router.delete("/reply/:_id", ReplyController.deleteReplyById)


module.exports = router;