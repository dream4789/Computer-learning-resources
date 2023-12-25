const regions1 = [
	{
		id: "51",
		name: "四川省",
		pid: "0",
	},
	{
		id: "5101",
		name: "成都市",
		pid: "51",
	},
	{
		id: "5103",
		name: "自贡市",
		pid: "51",
	},
	{
		id: "5104",
		name: "攀枝花市",
		pid: "51",
	},
	{
		id: "5105",
		name: "泸州市",
		pid: "51",
	},

	{
		id: "5107",
		name: "绵阳市",
		pid: "51",
	},
	{
		id: "510101",
		name: "市辖区",
		pid: "5101",
	},
	{
		id: "510104",
		name: "锦江区",
		pid: "5101",
	},
	{
		id: "510105",
		name: "青羊区",
		pid: "5101",
	},
	{
		id: "510106",
		name: "金牛区",
		pid: "5101",
	},
	{
		id: "510107",
		name: "武侯区",
		pid: "5101",
	},
	{
		id: "510108",
		name: "成华区",
		pid: "5101",
	},
	{
		id: "510112",
		name: "龙泉驿区",
		pid: "5101",
	},
	{
		id: "510113",
		name: "青白江区",
		pid: "5101",
	},
	{
		id: "510114",
		name: "新都区",
		pid: "5101",
	},
	{
		id: "510115",
		name: "温江区",
		pid: "5101",
	},
	{
		id: "510116",
		name: "双流区",
		pid: "5101",
	},
	{
		id: "510117",
		name: "郫都区",
		pid: "5101",
	},
	{
		id: "510118",
		name: "新津区",
		pid: "5101",
	},
	{
		id: "510121",
		name: "金堂县",
		pid: "5101",
	},
	{
		id: "510129",
		name: "大邑县",
		pid: "5101",
	},
	{
		id: "510131",
		name: "蒲江县",
		pid: "5101",
	},
	{
		id: "510181",
		name: "都江堰市",
		pid: "5101",
	},
	{
		id: "510182",
		name: "彭州市",
		pid: "5101",
	},
	{
		id: "510183",
		name: "邛崃市",
		pid: "5101",
	},
	{
		id: "510184",
		name: "崇州市",
		pid: "5101",
	},
	{
		id: "510185",
		name: "简阳市",
		pid: "5101",
	},
	{
		id: "510301",
		name: "市辖区",
		pid: "5103",
	},
	{
		id: "510302",
		name: "自流井区",
		pid: "5103",
	},
	{
		id: "510303",
		name: "贡井区",
		pid: "5103",
	},
	{
		id: "510304",
		name: "大安区",
		pid: "5103",
	},
	{
		id: "510311",
		name: "沿滩区",
		pid: "5103",
	},
	{
		id: "510321",
		name: "荣县",
		pid: "5103",
	},
	{
		id: "510322",
		name: "富顺县",
		pid: "5103",
	},
	{
		id: "510401",
		name: "市辖区",
		pid: "5104",
	},
	{
		id: "510402",
		name: "东区",
		pid: "5104",
	},
	{
		id: "510403",
		name: "西区",
		pid: "5104",
	},
	{
		id: "510411",
		name: "仁和区",
		pid: "5104",
	},
	{
		id: "510421",
		name: "米易县",
		pid: "5104",
	},
	{
		id: "510422",
		name: "盐边县",
		pid: "5104",
	},
	{
		id: "510501",
		name: "市辖区",
		pid: "5105",
	},
	{
		id: "510502",
		name: "江阳区",
		pid: "5105",
	},
	{
		id: "510503",
		name: "纳溪区",
		pid: "5105",
	},
	{
		id: "510504",
		name: "龙马潭区",
		pid: "5105",
	},
	{
		id: "510521",
		name: "泸县",
		pid: "5105",
	},
	{
		id: "510522",
		name: "合江县",
		pid: "5105",
	},
	{
		id: "510524",
		name: "叙永县",
		pid: "5105",
	},
	{
		id: "510525",
		name: "古蔺县",
		pid: "5105",
	},
	{
		id: "510701",
		name: "市辖区",
		pid: "5107",
	},
	{
		id: "510703",
		name: "涪城区",
		pid: "5107",
	},
	{
		id: "510704",
		name: "游仙区",
		pid: "5107",
	},
	{
		id: "510705",
		name: "安州区",
		pid: "5107",
	},
	{
		id: "510722",
		name: "三台县",
		pid: "5107",
	},
	{
		id: "510723",
		name: "盐亭县",
		pid: "5107",
	},
	{
		id: "510725",
		name: "梓潼县",
		pid: "5107",
	},
	{
		id: "510726",
		name: "北川羌族自治县",
		pid: "5107",
	},
	{
		id: "510727",
		name: "平武县",
		pid: "5107",
	},
	{
		id: "510781",
		name: "江油市",
		pid: "5107",
	},
];


function convertToTree(regions, rootId = "0") {
	// TODO: 在这里写入具体的实现逻辑
	// 将平铺的结构转化为树状结构，并将 rootId 下的所有子节点数组返回
	// 如果不存在 rootId 下的子节点，则返回一个空数组

	let a = []
	let b = []

	regions.forEach((item, index) => {
		if (item.id.length == 2) {
			a = [{
				id: item.id, // 地址 id
				name: item.name, // 地址名
				pid: item.pid, // 该地址的父节点 id
				children: []
			}];
		}

		b = [{
			id: item.id, // 地址 id
			name: item.name, // 地址名
			pid: item.pid, // 该地址的父节点 id
			children: []
		}];

		if (item.id.length == 4) {
			a.forEach((it, index) => {
				if (it.id == item.pid)
					a[0].children.push(b[0])
			})
		}
		if (item.id.length == 6) {
			a[0].children.forEach((it, index) => {
				if (it.id == item.pid) {
					a[0].children[index].children.push(b[0])
				}
			})
		}
	})
	return a;
}

convertToTree(regions1)

module.exports = convertToTree; // 检测需要，请勿删除
