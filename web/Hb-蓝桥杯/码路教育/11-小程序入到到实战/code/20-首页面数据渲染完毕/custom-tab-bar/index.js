Component({
  data: {
    tabbarArr:[{
      "pagePath": "/pages/home/home",
      "text": "首页",
      "icon":"home-o"
    },{
      "pagePath": "/pages/topic/topic",
      "text": "专题",
      "icon":"user-o"
    },{
      "pagePath": "/pages/category/category",
      "text": "分类",
      "icon":"apps-o"
    },{
      "pagePath": "/pages/cart/cart",
      "text": "购物车",
      "icon":"cart-o"
    },{
      "pagePath": "/pages/user/user",
      "text": "我的",
      "icon":"user-o"
    }],
    active:0
  },
  methods: {
    // ------------------------- 这一片代码是没有实现守卫
    // onChange(event){
    //   // event.detail 得到点击哪一项的索引 从0开始的
    //   // console.log(event.detail);
    //   this.setData({
    //     active:event.detail
    //   })

    //   wx.switchTab({
    //     url: this.data.tabbarArr[event.detail].pagePath
    //   })
    // }

    // ----------------------------实现守卫
    onChange(event){
      // 判断你是否要去购物车
      if(this.data.tabbarArr[event.detail].pagePath === "/pages/cart/cart"){
        // 说明要进入购物车，判断有没有登录，如果没有登录，不能去购物车
        let token = wx.getStorageSync('token');
        if(!token){
          getApp().globalData.prevRoute = "/pages/cart/cart"
          getApp().globalData.isGoBack = true;
          getApp().globalData.isPageFromTabbar = true;
          // 没有登录
          wx.showToast({
            title: '请先登录',
            icon:"none"
          })
          // 去登录页面
          setTimeout(()=>{
            wx.switchTab({
              url: '/pages/user/user',
            })
          },1000)
          return;
        }else{
          getApp().globalData.isGoBack = false;
        }
      }

      this.setData({
        active:event.detail
      })

      wx.switchTab({
        url: this.data.tabbarArr[event.detail].pagePath
      })
    }
  }
})
