const Router = require("@koa/router");
const AdvertiseController = require("../controller/AdvertiseController.js");
const jwtAuth = require("koa-jwt");
const config = require("../config/index.js");

const router = new Router();

// 创建广告
router.post("/advertise", jwtAuth({
    secret: config.security.secretKey
}), AdvertiseController.createAdvertise);

// 获取广告列表
router.get("/advertise", AdvertiseController.getAdvertiseList);

// 获取广告详情
router.get("/advertise/:_id", AdvertiseController.getAdvertiseDetailById);

// 更新广告
router.put("/advertise/:_id", AdvertiseController.updateAdvertiseById);

// 删除
router.delete("/advertise/:_id", AdvertiseController.deleteAdvertiseById);

module.exports = router;