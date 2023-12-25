const Router = require("@koa/router");
const jwtAuth = require("koa-jwt")
const ArticleController = require("../controller/ArticleController")
const config = require("../config/index.js")
const upload = require("../middlewares/upload")

const router = new Router();

// 创建文章  jwtAuth({ secret: config.security.secretKey }),
router.post("/article", ArticleController.create)


// 获取文章 jwtAuth({ secret: config.security.secretKey }),
router.get("/article", ArticleController.getArticleList)


// 更新文章 jwtAuth({ secret: config.security.secretKey }),
router.put("/article/:_id", ArticleController.updateArticleById)

// 根据文章ID得到文章的详情 jwtAuth({ secret: config.security.secretKey }),
router.get("/article/:_id", ArticleController.getArticleDetailById)

// 根据文章ID删除文章 jwtAuth({ secret: config.security.secretKey }),
router.delete("/article/:_id", ArticleController.deleteArticleById)

// 文章封面上传 jwtAuth({ secret: config.security.secretKey }),
// upload.single("avatar"), 此中间件已经实现上传了，
// ArticleController.uploadCoverImg 此中间件只需要给出提示
router.post("/upload", upload.single("avatar"), ArticleController.uploadCoverImg)

module.exports = router;