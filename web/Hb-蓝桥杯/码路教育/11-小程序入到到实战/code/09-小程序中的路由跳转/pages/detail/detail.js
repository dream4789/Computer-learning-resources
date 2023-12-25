// pages/detail/detail.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    uname:"",
    age:0
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    // options中就保存路由跳转传递的参数
    // console.log(options);
    let {uname,age} = options;
    // console.log(uname,age);
    this.setData({
      uname,age
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