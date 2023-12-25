Page({

  /**
   * 页面的初始数据
   */
  data: {
    tabbarData:["电影","电视","音乐","体育","明星"]
  },

  // 定义一个方法，传递到组件中
  test(){
    console.log("test是父中的方法");
  },

  maluFn(data){
    // data.detail得到子传递给父的数据
    console.log("data:",data.detail);
  },

  indexChange(data){
    console.log(data.detail);
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    
  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {
    
  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {
    
  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {
    
  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {
    
  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {
    
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {
    
  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {
    
  }
})