const inputs = document.querySelectorAll(".controls input");

/**
 * 上面已经选取了两个取色器
 * 请添加相应的 JS 事件处理函数并绑定到合适的事件监听器上（提示：change 事件）
 * 这样我们就可以用取色器选取颜色来生成下方的渐变色背景啦
 *  */

// console.log(inputs);


// 直接修改 :root
inputs[0].onchange = function() {
	console.log(this.value);
	document.documentElement.style.setProperty(
		"--color1", this.value
	);
}


inputs[1].onchange = function() {
	console.log(this.value);
	document.documentElement.style.setProperty(
		"--color2", this.value
	);
}

//  从 class 属性修改
// let gra = document.querySelector('.gradient');
// inputs[0].onchange = function() {
// 	gra.style.setProperty("--color1", inputs[0].value);
// }
// inputs[1].onchange = function() {
// 	gra.style.setProperty("--color2", inputs[1].value);
// }
