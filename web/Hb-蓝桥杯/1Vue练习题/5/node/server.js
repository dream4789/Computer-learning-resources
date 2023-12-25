const http = require("http");
const url = require("url");
const querystring = require("querystring");

var config = {
	port: 1145
};

const server = http.createServer((req, res) => {
	res.writeHead(200, {
		"Content-Type": "application/json;charset=utf8",
		"access-control-allow-origin": "*",
	});
	let urlParse = url.parse(req.url);
	let path = urlParse.pathname;
	if (path === "/api/list") {
		let query = querystring.parse(urlParse.query);
		if (query?.page == 1 && query?.limit > 0) {
			let ret = [];
			for (let i = 1; i <= query.limit; i++) ret.push(i);
			res.end(JSON.stringify(ret));
			return;
		}
		res.end("参数错误");
		return;
	}
	res.end();
});

server.listen(config.port, () => {
	console.log(`server start, listen on port: ${config.port}.`);
});
