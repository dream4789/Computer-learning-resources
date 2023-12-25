let rollTime; // 定义定时器变量用来清除定时器
let time = 0; // 转动次数
let speed = 300; // 转动时间间隔
let times; // 总转动次数

// 开始按钮点击事件后开始抽奖
$("#start").on("click", function() {
	$("#p1").text(""); //清空中奖信息
	times = parseInt(Math.random() * (20 - 30 + 1) + 20, 10); // 定义总转动次数，随机20-30次
	rolling();
});

// TODO：请完善此函数
function rolling() {
	time++; // 转动次数加1
	// clearTimeout(rollTime);
	let t = `li${time%9==0?++time%9:time%9}`;
	// console.log('--', t);
	$(`.${t}`).addClass("active");
	
	// 宏任务
	rollTime = setTimeout(() => {
		window.requestAnimationFrame(rolling); // 进行递归动画
		$('li').removeClass("active");
	}, speed);
	
	
	// time > times 转动停止
	if (time > times) {
		// console.log($(`.${t}`).text());
		$('#p1').text('恭喜您获得了' + $(`.${t}`).text() + '！！！');
		clearInterval(rollTime);
		time = 0;
		return;
	}
}
