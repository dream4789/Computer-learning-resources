Page({
  // 给页面提供数据
  data: {
    userInfo:{}
  },
  // 监听页面加载，当加载这个页面时，会调用此钩子函数
  onLoad: function (options) {
      // 获取全局共享数据
      // 得到app
      let app = getApp();

      let token = app.globalData.token;
      let userInfo = app.globalData.userInfo;

      console.log("token:",token);
      console.log("userInfo:",userInfo);

      // this.data.userInfo = userInfo;

      this.setData({
        userInfo
      })
  },
})