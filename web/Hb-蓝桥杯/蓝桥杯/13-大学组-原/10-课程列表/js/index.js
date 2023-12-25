let pageNum = 1; // 当前页码，默认页码1
let maxPage; // 最大页数

// TODO：待补充代码

// 点击上一页
// let prev = document.getElementById("prev");
// prev.onclick = function () {
//   // TODO：待补充代码
// };
// // 点击下一页
// let next = document.getElementById("next");
// next.onclick = function () {
//   // TODO：待补充代码
// };



// TODO：待补充代码
let pagination = document.getElementById("pagination")
let list = document.getElementById('list')
let arr = []
axios.get('./js/carlist.json').then(res => {
	arr = res.data
	//利用ceil向上取整，获取最大页数
	maxPage = Math.ceil(res.data.length / 5)
	showDom(pageNum)
	pagination.textContent = `共${maxPage}页，当前${pageNum}页`
})
// 将number类型转换成题目给定的货币类型
function fmoney(num) {
	if (!num) return NaN
	num = num.toString()
	let l = num.split('');
	let i = l.length
	l.splice(i - 2, 0, '.')
	return l.join('')
}
// 更新DOM的函数
function showDom(index) {
	// 深拷贝
	let Dom = JSON.parse(JSON.stringify(arr))
	// 截取需要展示的5条数据
	let newDom = Dom.splice((index - 1) * 5, 5)
	list.innerHTML = ''

	for (let i = 0; i < newDom.length; i++) {
		const element = newDom[i];
		list.innerHTML += `  <div class="list-group">
        <a href="#" class="list-group-item list-group-item-action">
          <div class="d-flex w-100 justify-content-between">
            <h5 class="mb-1">${element.name}</h5>
            <small>${fmoney(element.price)}元</small>
          </div>
          <p class="mb-1">
          ${element.description}
          </p>
        </a>
      </div>`;
	}
}
let prev = document.getElementById("prev");
let next = document.getElementById("next");
// 给按钮添加禁用类disabled的函数
function isDisabled() {
	if (pageNum === 1) {
		prev.classList.add('disabled')
	} else {
		prev.classList.remove('disabled')
	}
	if (pageNum === maxPage) {
		next.classList.add('disabled')
	} else {
		next.classList.remove('disabled')
	}
}
isDisabled()
// 点击上一页
prev.onclick = function() {
	// TODO：待补充代码
	if (pageNum > 1) {
		pageNum--
		showDom(pageNum)
	}
	isDisabled()
	pagination.textContent = `共${maxPage}页，当前${pageNum}页`

};
// 点击下一页
next.onclick = function() {
	// TODO：待补充代码
	if (pageNum !== maxPage) {
		pageNum++
		showDom(pageNum)
	}
	isDisabled()
	pagination.textContent = `共${maxPage}页，当前${pageNum}页`
};
