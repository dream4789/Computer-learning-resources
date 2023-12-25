// TODO：完善此函数 显示黑猫
function blackcat() {
	let btns = document.getElementsByTagName('img');
	setTimeout(() => {
		btns[0].style.display = 'none';
		btns[1].style.display = 'inline-block';
	}, 5000)
}

// TODO：完善此函数  显示白猫
function whitecat() {
	let btns = document.getElementsByTagName('img');
	setTimeout(() => {
		console.log(btns[0]);
		btns[1].style.display = 'none';
		btns[2].style.display = 'inline-block';
	}, 10000)
}

// TODO：完善此函数
function shift() {
	blackcat();
	whitecat();
}

shift();
