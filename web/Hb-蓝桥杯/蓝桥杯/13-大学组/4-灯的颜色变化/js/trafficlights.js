// TODO：完善此函数 显示红色颜色的灯
function red() {
	return new Promise(resolve => {
		setTimeout(() => {
			let lig = document.getElementById('defaultlight')
			let green = document.getElementById('greenlight')
			let red = document.getElementById('redlight')
			lig.style.display = 'none'
			green.style.display = 'none'
			red.style.display = 'inline-block'
			resolve();
		}, 3000)
	})
}

// TODO：完善此函数  显示绿色颜色的灯
function green() {
	return new Promise(resolve => {
		setTimeout(() => {
			let lig = document.getElementById('defaultlight')
			let green = document.getElementById('greenlight')
			let red = document.getElementById('redlight')
			lig.style.display = 'none'
			red.style.display = 'none'
			green.style.display = 'inline-block'
			resolve();
		}, 3000)
	})
}

// TODO：完善此函数
async function trafficlights() {
	await red()
	await green()
}

trafficlights();
