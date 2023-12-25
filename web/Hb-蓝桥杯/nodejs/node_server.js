const http = require('http');

var server = http.createServer(function(req, res) {
	if (req.url == "/") {
		res.writeHead(200, {
			'Content-type': 'text/html'
		});
		res.write('<h1>Node.js</h1>');
		res.end('<p>Hello World</p>');
	}
});
server.listen('8080', function() {
	console.log((new Date()) + ' Server is listening on port 8080', 8080);
});
