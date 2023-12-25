const Router = require("@koa/router");
const jwtAuth = require("koa-jwt")
const CategoryController = require("../controller/CategoryController")
const config = require("../config/index.js")

const router = new Router();


// 创建分类
router.post("/category", jwtAuth({ secret: config.security.secretKey }), CategoryController.create)

// 获取所有分类  jwtAuth({ secret: config.security.secretKey }),
router.get("/category", CategoryController.getCategoryList)

// 根据ID获取某个分类  jwtAuth({ secret: config.security.secretKey }), 
router.get("/category/:_id", CategoryController.getCategoryDetailById)

// 更新分类  jwtAuth({ secret: config.security.secretKey }),
router.put("/category/:_id", CategoryController.updateCategoryById)

// 删除分类  jwtAuth({ secret: config.security.secretKey }),
router.delete("/category/:_id", CategoryController.deleteCategoryById)

module.exports = router;