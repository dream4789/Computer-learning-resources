import ajax from "../../utils/ajax"

Page({

  // 放数据
  data: {
    msg:""
  },
  // 当页面加载时，会触发load事件
  // 在load事件中，就可以发请求
  onLoad: async function (options) {
      // ----------------- 1）发送网络请求的基本使用
      // wx.request({
      //   // 发的请求，需要在小程序后台配置一下
      //   // 需要在小程序后台配置合法域：https://v.api.aa1.cn
      //   // 开发时，如果不配，会报错误
      //   // 如果不想配，可以详情中，找到本地设置，勾选不校验域名的合法性
      //   url: 'https://v1.hitokoto.cn/',
      //   success:(res)=>{
      //     this.setData({
      //       msg:res.data.hitokoto
      //     })
      //   },
      //   fail:err=>{
      //     console.log("err:",err);
      //   }
      // })

      // ----------------- 2）发送网络请求传递参数
      // wx.request({
      //   // 没有指定请求方式，默认是get请求
      //   // url: 'https://v1.hitokoto.cn/?a=1&b=2',
      //   url: 'https://v1.hitokoto.cn',
      //   // method:"post",
      //   data:{
      //     pageno:1,
      //     pagesize:3
      //   },
      //   success:(res)=>{
          // this.setData({
          //   msg:res.data.hitokoto
          // })
      //   },
      //   fail:err=>{
      //     console.log("err:",err);
      //   }
      // })
      

      // ----------------- 3）封装成一个promise
      // ajax({url:"https://v1.hitokoto.cn"}).then(res=>{
      //    this.setData({
      //      msg:res.hitokoto
      //    })
      // })

      let res = await ajax({url:"https://v1.hitokoto.cn"})
      this.setData({
        msg:res.hitokoto
      })
  },

  toastFn(){
    // wx.showToast({
    //   title: '成功',
    //   icon: 'success',
    //   duration: 2000,
    //   // 是否显示透明蒙层，防止触摸穿透	
    //   mask:true
    // })

    // loading效果
    wx.showLoading({
      title: '加载中',
    })
    setTimeout(function () {
      wx.hideLoading()
    }, 2000)
  },

  modalFn(){
    wx.showModal({
      title: '提示',
      content: '这是一个模态弹窗',
      success (res) {
        if (res.confirm) {
          console.log('用户点击确定')
        } else if (res.cancel) {
          console.log('用户点击取消')
        }
      }
    })
  },
  actionSheetFn(){
    wx.showActionSheet({
      itemList: ['A', 'B', 'C', 'D','E','F'],
      success (res) {
        console.log(res.tapIndex)
      },
      fail (res) {
        console.log(res.errMsg)
      }
    })
  },
  getLocationFn(){
    wx.getLocation({
      type: 'wgs84',
      success (res) {
        const latitude = res.latitude
        const longitude = res.longitude
        const speed= res.speed
        console.log(latitude,longitude,speed);
      }
     })
  },
  getSystemInfoFn(){
    wx.getSystemInfo({
      success: (result) => {
        console.log("result:",result);
      },
    })
  },

  storageFn(){
    // Sync 同步存储
    // wx.setStorageSync('name1', "malu")
    // wx.setStorageSync('name2', 18)
    // wx.setStorageSync('name3', ["wc","xq"])

    // console.log(wx.getStorageSync('name1'));
    // console.log(wx.getStorageSync('name2'));
    // console.log(wx.getStorageSync('name3'));

    // wx.removeStorageSync('name1')

    // wx.clearStorageSync();

    // ------------------------- 还有异步操作

    // 淌有带Sync就是异步操作
    wx.setStorage({
      key:"name",
      data:"malu"
    })
  }
})