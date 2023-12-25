/**
 * @description 得到分页数组 indexArr，如[1,2,3,4,10],[1,3,4,5,10],[1,7,8,9,10]
 * @param {number} currentPage 当前页数,默认为第一页    
 * @param {number} totalPages 总的页码数
 * @param {number} pagerCount 设置最大页码按钮数。 页码按钮的数量，当总页数超过该值时会折叠
 * @return {Array} 分页数组 indexArr
 */
/**
 * @description 得到分页数组 indexArr，如[1,2,3,4,10],[1,3,4,5,10],[1,7,8,9,10]
 * @param {number} currentPage 当前页数,默认为第一页	
 * @param {number} totalPages 总的页码数
 * @param {number} pagerCount 设置最大页码按钮数。 页码按钮的数量，当总页数超过该值时会折叠
 * @return {Array} 分页数组 indexArr
 */
const createPaginationIndexArr = (currentPage, totalPages, pagerCount) => {
	let indexArr = [];
	// TODO：根据传参生成分页数组 indexArr
	indexArr[0] = 1 //第1个永远是1
	if (totalPages <= pagerCount) {
		for (let i = 1; i < totalPages; i++) {
			indexArr.push(i + 1)
		}
	} else {
		indexArr[pagerCount - 1] = totalPages //最后1个永远是totalPages
		if (currentPage <= pagerCount - 2) {
			for (let i = 1; i < pagerCount - 1; i++) {
				indexArr[i] = i + 1
			}
		} else if (currentPage <= totalPages - pagerCount + 2) {
			let j = 1; //用于计算下标的
			for (let i = -Math.ceil((pagerCount - 3) / 2); i <= Math.floor((pagerCount - 3) / 2); i++) {
				indexArr[j++] = currentPage + i
			}
		} else {
			let j = 1; //用于计算下标的
			for (let i = totalPages - pagerCount + 2; i < totalPages; i++) {
				indexArr[j++] = i
			}
		}
	}

	return indexArr;
}

module.exports = {
	createPaginationIndexArr
}
