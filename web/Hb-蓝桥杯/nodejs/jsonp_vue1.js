var querystring = require('querystring');
var http = require('http');
var server = http.createServer();
server.on('/request', function(req, res) {
    var params = querystring.parse(req.url.split('?')[1]);
    var fn = params.callback;

    // jsonp返回设置
    res.writeHead(200, { 'Content-Type': 'text/javascript' });
    res.write(fn + '(' + JSON.stringify(params) + ')');
    res.end();
});
server.listen('8080');
console.log('Server is running at port 8080...');