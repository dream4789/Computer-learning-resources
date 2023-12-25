const sectionsCount = $("section").length;
let activeIndex = 0;

// 监听用户按下空格和方向键的事件
$(document).on("keydown", (e) => {
	e.preventDefault();
	if (e.key === " " || e.key === "ArrowRight") {
		goRight();
	}
	if (e.key === "ArrowLeft") {
		goLeft();
	}
});

// 监听按钮点击事件
$(".btn.left").click(goLeft);
$(".btn.right").click(goRight);

// 切换下一张的函数
function goLeft() {
	if (activeIndex === 0) {
		return;
	}
	activeIndex -= 1;
	console.log("11", activeIndex)
	switchPage();
}

// 切换上一张的函数
function goRight() {
	if (activeIndex === sectionsCount - 1) {
		return;
	}
	activeIndex += 1;
	console.log("22", activeIndex)
	switchPage();
}

function switchPage() {
	// TODO: 请补充该函数，实现根据activeIndex切换页面的功能，并且在到达最后一页或第一页时给相应的按钮添加disable类
	// console.log(Array.from(document.querySelectorAll('section')).slice(4));

	// Array.from(document.querySelectorAll('section')).slice(0,4).forEach(e => e.style.display = 'flex')

	// console.log(document.querySelectorAll('section'))  // object
	// document.write(document.querySelectorAll('section')[0]);
	// console.log(Array.from(document.querySelectorAll('section')).slice(activeIndex, activeIndex + 1)[0])

	// ------------------------------  方法1：
	// Array.from(document.querySelectorAll('section')).slice(activeIndex, activeIndex + 1).forEach(e => e.style.display = 'flex');
	// 或
	// Array.from(document.querySelectorAll('section')).slice(activeIndex, activeIndex + 1)[0].style.display = 'flex';
	// Array.from(document.querySelectorAll('section')).slice(activeIndex - 1, activeIndex).forEach(e => e.style.display = 'none');
	// Array.from(document.querySelectorAll('section')).slice(activeIndex + 1, activeIndex + 2).forEach(e => e.style.display = 'none');
	
	// if (activeIndex == 0) {
	// 	$(".left").addClass("disable");
	// } else {
	// 	$(".left").removeClass("disable");
	// }
	// if (activeIndex == 4) {
	// 	$(".right").addClass("disable");
	// } else {
	// 	$(".right").removeClass("disable");
	// }

	// ------------------------------  方法2：
	Array.from(document.querySelectorAll('section')).forEach((e, index) => {
		e.style.display = 'none'
		$(".left").removeClass("disable");
		$(".right").removeClass("disable");
		
		if (index == activeIndex) e.style.display = 'flex'
		if (activeIndex == 0) $(".left").addClass("disable");
		if (activeIndex == 4) $(".right").addClass("disable");
	});

	// <div class="page">1 / 5</div>
	// console.log(document.querySelector('.page'))
	document.getElementsByClassName("page")[0].innerHTML = activeIndex + 1 + ' / 5'
}
