/**
 * 封装函数，函数名 getRandomNum(min,max,countNum)
 * 生成 min~max 范围的 countNum 个不重复的随机数，存入数组并返回
 */
//生成指定数目和范围的随机数
 const getRandomNum = function(min, max, countNum) {
    var arr = [];      
     // 在此处补全代码
	 /*提示： Math.random():随机生成一个 0 ~ 1 之间的数：
	    生成向下取整的随机整数：
       使用 Math下的 floor 方法进行舍弃小数向下取整*/ 

	 for(var i=0;i<countNum;i++){
		 arr[i] = Math.floor(Math.random() * max + min);
	 }
	 
     return arr;
 };
module.exports = getRandomNum; //请勿删除