const baseUrl = "http://kumanxuan1.f3322.net:8001";

export default function ajax(url,params={}) {
  // 封装网络请求的代码
  return new Promise(function (resolve, reject) {
    wx.showLoading({
      title: '加载中...',
    })
    let token = wx.getStorageSync('token');
    var defaultHeader = {}
    if(token){
      if(params.header){
        // params有可能是一个{}, 则params.header就是undefined，params.header["X-Nideshop-Token"]报错
        params.header["X-Nideshop-Token"] = token
      }else{
          // 已经登录，但是没有传params
          defaultHeader = {
            "X-Nideshop-Token":token
          }
      }
    }
    // 发起请求
    wx.request({
      url: baseUrl + url,
      data: params.data || {},
      header: params.header || defaultHeader,
      method: params.method || 'GET',
      dataType: 'json',
      success: function(res) {
        wx.hideLoading();
        if(res.data.errno==0){
          resolve(res.data)
        }else{
            wx.showToast({
                title: res.data.errmsg,
                icon:"error",
                duration: 2000
            })
        }
      },
      fail: function(err) {
        wx.hideLoading();
        wx.showToast({
          title: err || '请求错误！',
        })
        reject(err)
      }
    })
  }) 
}