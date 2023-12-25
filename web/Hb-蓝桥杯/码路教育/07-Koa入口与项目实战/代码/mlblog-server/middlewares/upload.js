// 文件上传
const multer = require('koa-multer');
//配置 磁盘存储
const storage = multer.diskStorage({
	//文件保存路径
	destination: function(req, file, cb) {
		cb(null, 'public/images/')
	},
	//修改文件名称
	filename: function(req, file, cb) {
		var fileFormat = (file.originalname).split("."); //以点分割成数组，数组的最后一项就是后缀名
		cb(null, Date.now() + "." + fileFormat[fileFormat.length - 1]);
	}
})
//加载配置
const upload = multer({
	storage: storage
});
module.exports = upload;
