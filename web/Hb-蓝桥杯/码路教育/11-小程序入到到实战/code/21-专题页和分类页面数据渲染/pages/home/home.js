import {GetHomeDataApi} from "../../api/api"
Page({
  data: {
    banner:[],
    channel:[],
    brandList:[],
    newGoodsList:[],
    hotGoodsList:[],
    topicList:[],
    categoryList:[]
  },
  async onLoad(options) {
    let res = await GetHomeDataApi();
    let {banner,channel,brandList,newGoodsList,hotGoodsList,topicList,categoryList} = res.data
    this.setData({
      banner,
      channel,
      brandList,
      newGoodsList,
      hotGoodsList,
      topicList,
      categoryList
    })
  },

  gotoPopup(){
    wx.navigateTo({
      url: '/pages/popup/popup',
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
    // this.getTabBar 得到Tabbar组件实例
    this.getTabBar().setData({
      active:0
    })
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