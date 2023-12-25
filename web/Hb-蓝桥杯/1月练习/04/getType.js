function getType (target) {
	//在此处补充代码
	if(typeof target === "object")
		return 'object';
		
	// 可能会用到prototype来判断，但还不太会用它
}

module.exports = getType