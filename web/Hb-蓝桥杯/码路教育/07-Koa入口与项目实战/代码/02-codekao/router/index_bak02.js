const Router = require("@koa/router");
const Multer = require("koa-multer")
const router = new Router();

// 配置
let storage = Multer.diskStorage({
    destination: function (req, file, cb) {
        cb(null, "public/upload")
    },
    filename: function (req, file, cb) {
        var fileFormat = (file.originalname).split(".");
        cb(null, Date.now() + "." + fileFormat[fileFormat.length - 1]);
    }
})
let upload = Multer({ storage: storage })

router.get("/xxx", (ctx, next) => {
    ctx.body = "欢迎访问首页面"
})


router.post("/upload", upload.single("touxiang"), (ctx, next) => {
    ctx.body = {
        ok: 1,
        message: "上传成功"
    }
})

module.exports = router;