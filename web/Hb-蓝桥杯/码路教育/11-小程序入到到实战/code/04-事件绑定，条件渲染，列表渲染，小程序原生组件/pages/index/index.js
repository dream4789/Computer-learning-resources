Page({

  /**
   * 页面的初始数据
   */
  data: {
    msg:"hello malu",
    site:"http://www.baidu.com",
    age:100,
    showColor:true,
    isShow:true,
    score:50,
    singers:["陈明","辛晓琪","齐秦","羽泉","林志炫","杨宗纬"],
    imgPath:""
  },

  onToggle(){
    // 这一行代码仅仅是让数据发生变化了，界面并没有刷新
    // this.data.showColor = !this.data.showColor;
    // console.log(this.data.showColor);

    // 通过setData可以改变数据，并让界面重新渲染
    this.setData({
      showColor:!this.data.showColor
    })
  },
  onToggle2(){
    this.setData({
      isShow:!this.data.isShow
    })
  },
  handleChooseAlbum(){
    wx.chooseImage({
      count: 1,
      sourceType:["album","camera"],
      success:res=>{
        let file = res.tempFilePaths;
        this.setData({
          imgPath:file
        })
      }
    })
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