App({
  // 这里面可以配置多个页面共享的数据
  // vuex  不是响应式的
  globalData:{
    token:"",
    userInfo:{}
  },
  // 当小程序初始化完成时，会触发 onLaunch（全局只触发一次）
  onLaunch: function () {
      // console.log("onLaunch");
      // 从本地得到token和userInfo
      let token = wx.getStorageSync('token')
      let userInfo = wx.getStorageSync('userInfo')

      if(!token || !userInfo){
        wx.setStorageSync('token', "567f8sadfasdf5678754f5asdf");
        wx.setStorageSync('userInfo', {name:"malu",age:18});
      }

      this.globalData.token = token;
      this.globalData.userInfo = userInfo;
  },
})

