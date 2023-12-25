const Koa = require("koa");
const cors = require('koa2-cors');
const app = new Koa();

app.use(cors());

// 新联列表接口
app.use(async ctx => {
	ctx.body = {
		ok: 1,
		data: [{
				title: "中国特色强军之路的时代答卷",
				content: "学习koa,so easy~"
			},
			{
				title: "习近平阐释中国式现代化的五个重要特征",
				content: "学习koa,so easy~"
			},
		]
	}
})

app.listen(3000, () => {
	console.log("server is running on 3000");
})
