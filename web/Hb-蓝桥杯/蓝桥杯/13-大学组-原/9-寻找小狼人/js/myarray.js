// 返回条件为真的新数组
Array.prototype.myarray = function(cb) {
	// TODO：待补充代码
	let newarr = []
	this.forEach(item => {
		if (cb(item)) {
			newarr.push(item)
		}
	})
	return newarr
};
