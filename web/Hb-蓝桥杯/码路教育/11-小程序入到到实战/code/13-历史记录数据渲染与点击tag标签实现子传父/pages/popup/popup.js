import { HistoryHotApi,ClearHistoryApi } from "../../api/api"

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
  },
  // 确定搜索时触发
  onSearch(){
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
      keyword:val.detail.keyword
    })
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

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady() {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow() {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide() {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload() {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh() {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom() {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage() {

  }
})