// 返回条件为真的新数组
Array.prototype.myarray = function(cb) {
	// TODO：待补充代码
	// console.log('11', cb);
	// console.log(this.length);
	for (i = this.length - 1; i >= 0; i--) {
		if (this[i].category != "werewolf") {
			// console.log(this[i].category);
			this.splice(i, 1);
		}
		// console.log(i, this);
	}
	return this;
};
