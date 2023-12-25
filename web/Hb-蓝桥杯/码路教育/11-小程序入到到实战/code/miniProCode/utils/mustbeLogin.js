export default ()=>{
  let token = wx.getStorageSync('token');
    if(!token){
      let pages = getCurrentPages(); 
      let prevRoute = pages[pages.length-1].route
      getApp().globalData.prevRoute = "/" + prevRoute
      getApp().globalData.isGoBack = true;
       wx.showToast({
        title: '请先登录',
        icon:"none"
      })
      setTimeout(()=>{
        wx.switchTab({
          url: '/pages/user/user',
        })
      },1000)
      return true;
    }
    return false
}