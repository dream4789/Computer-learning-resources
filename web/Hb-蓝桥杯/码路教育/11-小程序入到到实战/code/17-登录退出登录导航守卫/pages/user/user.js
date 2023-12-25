import { LoginByWebApi } from "../../api/api"

Page({

  /**
   * 页面的初始数据
   */
  data: {
    // avatar:"../../assets/images/default_avatar.png",
    // username:"点击登录",

    avatar:wx.getStorageSync('token') ? JSON.parse(wx.getStorageSync('userInfo'))?.avatar : "../../assets/images/default_avatar.png",
    
    username:wx.getStorageSync('token') ? JSON.parse(wx.getStorageSync('userInfo'))?.nickname : "点击登录",

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
    login_password:"",   // 密码

    // isLogin: false,  // 登录是否登录 
    // 如果没有登录，得到不token，isLgoin就是false
    // 如果登录了，得到token，isLogin的值是token的字符串
    isLogin:wx.getStorageSync('token'),

    isShowLogoutWindow:false
  },
  gotoLogin(){
    this.showLoginWindow();
  },
  showLoginWindow(){
    if(this.data.isLogin){
      // 如果isLogin是true，表示登录成功了
      return; // 结束调用函数
    }
    this.setData({isShowLoginWindow:true})
  },
  onClose(){
    this.setData({isShowLoginWindow:false})
    this.setData({isShowLogoutWindow:false})
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
  async goToLogin(){
    if(!this.data.login_username.trim()){
      this.setData({
        username_err:true
      })
      return; // 必须要加
    }
    if(!this.data.login_password.trim()){
      this.setData({
        password_err:true
      })
      return;  // 必须要加
    }
    // 说明用户名输入框和密码输入框是有值
    let res = await LoginByWebApi({
      method:"POST",
      data:{
        username:this.data.login_username,
        pwd:this.data.login_password
      }
    })
    if(res.errno ===  0){
      // 1）提示登录成功
      wx.showToast({
        title: '登录成功',
        icon:"success",
        mask:true
      })

      // 2）保存token和userInfo到localStoage中
      wx.setStorageSync('token', res.data.token)
      wx.setStorageSync('userInfo', JSON.stringify(res.data.userInfo))

      // 3）隐藏登录框
      // 4）刷新页面上的用户信息
      this.setData({
        isShowLoginWindow:false, // 隐藏登录框
        username:res.data.userInfo.nickname,
        avatar:res.data.userInfo.avatar,
        isLogin:true,
      })
    }

  },
  // 点击小箭头弹出dialog
  gotoLogout(){
    if(!this.data.isLogin){
      // 没有登录 
      return
    }
    this.setData({
      isShowLogoutWindow:true
    })
  },
  // 实现退出登录
  async isLogoutOKFn(){
    wx.clearStorageSync(); // 清空storage

    this.setData({
      isLogin:false,
      username:"点击登录",
      avatar:"../../assets/images/default_avatar.png"
    })
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