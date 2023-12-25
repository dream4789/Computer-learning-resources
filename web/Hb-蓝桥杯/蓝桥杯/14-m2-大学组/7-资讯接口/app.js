// TODO: 待补充代码

const http = require('http')
const server = http.createServer()

server.on('request', (req, res) => {
	res.setHeader("Content-type", "text/html;charset=utf8");
	let data = [{
			"channelId": "5572a108b3cdc86cf39001cd",
			"name": "国内焦点"
		},
		{
			"channelId": "5572a108b3cdc86cf39001ce",
			"name": "国际焦点"
		}
	]
	if (req.url == '/news') {
		res.end(JSON.stringify(data))
	} else {
		res.end('404')
	}
})

server.listen(8080, () => {})

// http://localhost:8080/news