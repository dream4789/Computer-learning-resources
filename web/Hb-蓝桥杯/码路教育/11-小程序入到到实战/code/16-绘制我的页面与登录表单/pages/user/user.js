import { LoginByWebApi } from "../../api/api"

Page({

  /**
   * 页面的初始数据
   */
  data: {
    avatar:"../../assets/images/default_avatar.png",
    username:"点击登录",
    iconArr: [{
      icon: "label-o",
      text: "我的订单"
    },
    {
      icon: "bill-o",
      text: "优惠劵"
    },
    {
      icon: "goods-collect-o",
      text: "礼品卡"
    },
    {
      icon: "location-o",
      text: "我的收藏"
    },
    {
      icon: "flag-o",
      text: "我的足迹"
    },
    {
      icon: "contact",
      text: "会员福利"
    },
    {
      icon: "aim",
      text: "地址管理"
    },
    {
      icon: "warn-o",
      text: "账号安全"
    },
    {
      icon: "service-o",
      text: "联系客服"
    },
    {
      icon: "question-o",
      text: "帮助中心"
    },
    {
      icon: "smile-comment-o",
      text: "意见反馈"
    },
    ],
    isShowLoginWindow:false, // 控制弹出层

    username_err:false,  // true 提示请输入用户名
    password_err:false,  // true 提示请输入密码
    login_username:"",  // 用户名
    login_password:""   // 密码
  },
  gotoLogin(){
    this.showLoginWindow();
  },
  showLoginWindow(){
    this.setData({isShowLoginWindow:true})
  },
  onClose(){
    this.setData({isShowLoginWindow:false})
  },
  updateUsername(e){
    this.setData({
      username_err:e.detail.trim() === "",
      login_username:e.detail
    })
  },
  updatePassword(e){
    this.setData({
      password_err:e.detail.trim() === "",
      login_password:e.detail
    })
  },
  // 实现登录 
  goToLogin(){
    if(!this.data.login_username.trim()){
      this.setData({
        username_err:true
      })
    }
    if(!this.data.login_password.trim()){
      this.setData({
        password_err:true
      })
    }
  },
  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {

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
    this.getTabBar().setData({
      active:4
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