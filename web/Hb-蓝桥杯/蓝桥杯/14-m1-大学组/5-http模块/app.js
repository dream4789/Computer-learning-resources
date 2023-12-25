// TODO: 待补充代码
const http = require('http')
const server = http.createServer()

server.on('request', function(req, res) {
	res.end("hello world")
})

server.listen(8080, function() {
	console.log('8080启动成功');
})
