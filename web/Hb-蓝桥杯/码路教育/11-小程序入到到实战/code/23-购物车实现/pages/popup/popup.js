import { HistoryHotApi,ClearHistoryApi,GoodsSearchApi,TipsListApi } from "../../api/api"

let timer = null; 

Page({

  /**
   * 页面的初始数据
   */
  data: {
    searchVal:"",
    blockShow:1, // 1表示历史热门  2表示提示列表  3表示商品列表
    historyKeywordList:[], // 历史记录
    hotKeywordList:[], // 热门搜索
    defaultKeyword:[], // 提示数据
    keyword:"", // 子传递过来的热门搜索的tag
    goodsList:[], // 商品列表
    filterCategory:[], // 分类下拉菜单数据
    filterCategoryCurrentID:null, // 选中的下拉菜单选项
    // categoryId:0, // 分类ID

    page:1, // 显示页数
    size:20, // 一页显示个数
    order:"desc", // 排列顺序，desc价格高到底，asc价格低到高
    categoryId:"0", // 分类选项的id
    sort:"id", // 按什么排序 id或者price

    tipsList:[], // 提示数据
  },
  // 确定搜索时触发
  onSearch(e){
    // console.log(e);
    this.setData({
      keyword:e.detail,
      blockShow:3
    })
    this.goodsSearchFn(); // 重新发请求
  },  
  // 输入框输入内容时触发
  onChange(e){
    // setData是异步的，setData可以传递第2个参数
    // 当状态发生了变化，会自动执行第2个函数
    // 需求：当blockShow状态变了，再发ajax请求
    this.setData({
      blockShow:2
    },async ()=>{
     if(timer){
       clearTimeout(timer)
     }
     timer = setTimeout(async ()=>{
      let res = await TipsListApi({
        data:{
          keyword:e.detail
        }
      })
      this.setData({
        tipsList:res.data
      })
     },500)
    })
  },
  // 子切换分类，得到分类ID
  categoryChange(e){
    // console.log(e.detail);
    this.setData({
      keyword:this.data.keyword,
      categoryId:e.detail
    })
    // 点击不同的分类，分类ID变了，重新调用接口
    this.goodsSearchFn();
  },
  // 子切换价格排序
  priceChange(e){
    this.setData({
      keyword:this.data.keyword,
      sort:"price",
      order:e.detail
    })
    this.goodsSearchFn();
  },
  // 取消搜索搜索时触发
  onCancel(){
    wx.navigateBack();
  },
  // 清空历史记录
  async clearHistory(){
    // console.log("clearHistory...");
    await ClearHistoryApi({type:"POST"});
    this.setData({
      historyKeywordList:[]
    })
    wx.showToast({
      title: '清除成功',
      icon:"success"
    })
  },
  changeBlockShow(val){
    // console.log(val);
    this.setData({
      blockShow:val.detail.num,
      keyword:val.detail.keyword || this.data.keyword
    })
    // 调用方法，获取商品数据
    this.goodsSearchFn();
  },
  async onLoad(options) {
    let res = await HistoryHotApi();
    console.log(res);
    let { defaultKeyword,historyKeywordList,hotKeywordList } = res.data;
    this.setData({
      defaultKeyword,
      historyKeywordList,
      hotKeywordList
    })

    
  },
  // 根据关键字，获取商品数据
  async goodsSearchFn(){
    let res = await GoodsSearchApi({
      data:{
        // 之前获取商品列表数据，只传递了一个关键字
        // 现在需要把其它参数都传递过去
        keyword:this.data.keyword,

        page:this.data.page,
        size:this.data.size,
        order:this.data.order,
        categoryId:this.data.categoryId,
        sort:this.data.sort
      }
    })
    // console.log("res:",res);
    let { goodsList,filterCategory } = res.data;
    // 对后端响应的数据进行加工
    filterCategory = filterCategory.map(item=>{
      return {text:item.name,value:item.id}
    })
    // 遍历后面响应的数据，找到checked为true一项
    let currentId = res.data.filterCategory.filter(item=>{
      return item.checked;
    })[0].id;
    // console.log("currentId:",currentId);
    this.setData({
      goodsList,
      filterCategory,
      filterCategoryCurrentID:currentId
    })
  },
})