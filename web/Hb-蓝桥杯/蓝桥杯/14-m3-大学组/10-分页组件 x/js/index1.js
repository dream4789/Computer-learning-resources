/**
 * @description ajax 请求，通过传递的 currentPage, pageSize 获取到当前页和总页数的数据
 * @param {string} url 请求地址，必填
 * @param {string} method 请求方式，可选参数，默认为 get
 * @param {string} data 请求体数据，可选参数
 * @param {number} currentPage 当前页数，必填
 * @param {number} pageSize 每页显示条目个数，必填
 * @return {object} {data,total} data为data.json中data数组的部分数据，total为data.json中total的值
 * */
async function ajax({
	url,
	method = "get",
	data,
	query: {
		currentPage,
		pageSize
	}
}) {
	// TODO:根据函数参数 `query` 对象  `currentPage, pageSize` 获得当前页的数据

	let resdata = []
	/*调接口存数据*/
	let res = await axios[method](url, data)
	if (res.status === 200) {
		resdata = res.data.data
		result.total = res.data.total
	}
	/*当前页要展示的页面数据*/
	result.data = resdata.slice((currentPage - 1) * pageSize, currentPage * pageSize)

	return result;
}

class Pagination {
	/**
	 * @param {Element} root
	 * @param {number} pageSize 每页显示条目个数
	 * @param {number} total 总条目数
	 * @param {number} pagerCount 设置最大页码按钮数。 页码按钮的数量，当总页数超过该值时会折叠
	 * @param {number} currentPage 当前页数,默认为第一页	
	 * @param {function} currentChange current-page 改变时触发
	 */
	constructor(root, {
		pageSize,
		total,
		pagerCount,
		currentPage
	}, {
		currentChange
	}) {
		if (pagerCount % 2 == 0) {
			pagerCount--;
		}
		this.root = root;
		this.pageSize = pageSize || 10;
		this.total = total;
		this.pagerCount = pagerCount || 7;
		this.currentPage = currentPage || 1;
		this.currentChange = currentChange;

		this.totalPages = Math.ceil(total / pageSize);
		this.initPagination();
	}
	/**
	 * @description 初始化分页组件，首次创建和 this.currentPage 改变时调用
	 * */
	initPagination() {
		const indexArr = createPaginationIndexArr(this.currentPage, this.totalPages, this.pagerCount);
		document.querySelector("#index-arr").innerText = JSON.stringify(indexArr);
		this.renderPagination(indexArr);
		this.initEvents();
		this.currentChange(this.currentPage);
	}

	/**
	 * @description 根据序号数组生成分页组件的字符串模板通过 innerHTML 挂载在 root 元素内
	 * @param {Array} indexArr 分页数组 indexArr
	 * @return {String} 分页组件的字符串模板
	 */
	renderPagination(indexArr) {
		let template = '';
		// TODO：根据 indexArr 数组生成分页组件的字符串模板 template
		template = indexArr.reduce((prev, next, index) => {
			if (indexArr[index] - indexArr[index - 1] > 1) {
				prev += `<li class="number more">...</li>`
				prev += `<li class="number ${this.currentPage==next?'active' :''}">${next}</li>`
			} else {
				prev += `<li class="number ${this.currentPage==next?'active' :''}">${next}</li>`
			}
			return prev;
		}, '')


		this.root.innerHTML = `
        <div class="pagination">
            <div class="btn btn-left" id="btn-prev">&lt;</div>
            <ul class="pager">${template} </ul>
            <div class="btn btn-right" id="btn-next">&gt;</div>
        </div>`;
	}
	/** 
	 * @description 事件绑定，改变 this.currentPage 的值,值在 1 到 this.totalPages 之间
	 **/
	initEvents() {
		this.root.querySelector("#btn-prev").addEventListener('click', () => {
			// TODO:"<" 按钮的点击事件， 点击时 this.currentPage - 1
			if (this.currentPage > 1) {
				this.currentPage--;
				this.initPagination();
			}
		})
		this.root.querySelector("#btn-next").addEventListener('click', () => {
			// TODO:">" 按钮的点击事件， 点击时 this.currentPage + 1
			if (this.currentPage < this.totalPages) {
				this.currentPage++;
				this.initPagination();
			}
		})
		this.root.querySelector(".pager").addEventListener('click', (e) => {
			if (e.target.nodeName.toLowerCase() === 'li') {
				if (this.currentPage === e.target.innerText) return;
				if (e.target.classList.contains('more')) return;
				this.currentPage = Number(e.target.innerText)
			}
			this.initPagination();
		});
	}
}

const paginationConfigObj = {
	pageSize: 10,
	total: 100,
	pagerCount: 5
};
const root = document.querySelector(".pagination-container");
async function renderContent(currentPage) {
	document.querySelector("#current-page").innerText = currentPage;
	const {
		data,
		total
	} = await ajax({
		url: "./js/data.json",
		method: "get",
		query: {
			currentPage,
			...paginationConfigObj
		}
	});
	document.querySelector("#ajax-data").innerText = JSON.stringify(data);
	document.querySelector("#ajax-total").innerText = JSON.stringify(total);
	const contentEle = document.querySelector('.content');
	let template = data.reduce((prev, cur) =>
		prev + `                
        <li class="item" data-index="${cur.id}">
            <h4 class="title">${cur.title}</h4>
            <div class="item-right">
                评论数：<span class="replay-count">${cur.replayCount}</span>
                /
                点击数：<span class="click-count">${cur.clickCount}</span>
            </div>
        </li>`, "");
	contentEle.innerHTML = template;
}

new Pagination(root, paginationConfigObj, {
	currentChange: renderContent
});
