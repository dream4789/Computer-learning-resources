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
    onChange(event){
      // event.detail 得到点击哪一项的索引 从0开始的
      // console.log(event.detail);
      this.setData({
        active:event.detail
      })

      wx.switchTab({
        url: this.data.tabbarArr[event.detail].pagePath
      })
    }
  }
})
