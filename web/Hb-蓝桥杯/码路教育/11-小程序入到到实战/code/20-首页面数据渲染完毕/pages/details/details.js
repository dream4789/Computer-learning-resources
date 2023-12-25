// pages/details/details.js
import {GetGoodsDetailApi,GetGoodsRelatedApi,AddToCartApi,GetGoodsCountApi} from "../../api/api"
import mustbeLogin  from "../../utils/mustbeLogin"

Page({

  /**
   * 页面的初始数据
   */
  data: {
      // 轮播图数组
      gallery: [],
      // 产品信息
      info: {
        name: "",
        goods_brief: "",
        retail_price: 0
      },
      // 产品参数
      attribute: [],
      // 常见问题
      issue: [],
      // productList
      productList: [],
      // 相关商品
      goodsList:[],
      // 收藏样式切换
      collectStatus:false,
      // 是否显示弹出层
      isShowSku:false,
      // 商品数量
      stepNum:0,
      // 购物车中商品的数量
      goodsCount:0
  },

  // 控制点击收藏的样式
  collectToggle(){
    if(mustbeLogin()) return

    this.setData({
      collectStatus:!this.data.collectStatus
    })
  },
  // 关闭弹出层
  onCloseSku(){
      this.setData({
          isShowSku:false
      })
  },
  // 显示弹出层
  onShowSku(){
      this.setData({
          isShowSku:true
      })
  },
  // 点击加入购物车
  async addToCart(){
    if(this.data.isShowSku){
      // 弹出层已经显示了
      // 1）把弹框隐藏掉
      this.onCloseSku(); 
      // 2）需要登录
      if(mustbeLogin()) return;
      // 3)发ajax请求，添加商品到购物车
      let res = await AddToCartApi({
        method:"POST",
        data:{
          goodsId:getApp().globalData.detailsId,
          productId:this.data.productList[0].id,
          number:this.data.stepNum,
        }
      })
      this.setData({
        goodsCount:res.data.cartTotal.goodsCount
      })
      // 提示添加购物车成功
      if(res.errno === 0){
        wx.showToast({
          title: '添加购物车成功',
          icon:"success"
        })
      }
    }else{
      // 弹出层没显示
      this.onShowSku();
    }
  },
  // 计数器
  onChange(e){
    this.setData({
      stepNum:e.detail
    })
  },
  // 点击购物车去购物车页
  goToCarPage(){
    if(mustbeLogin()){
      return; // 表示需要登录 
    }
    // let token = wx.getStorageSync('token');
    // if(!token){
    //   // -------------------------------------------------
    //   // 获取当前详情页的路径，存储到全局中
    //   let pages = getCurrentPages(); // 获取当前所有活着的页面
    //   let prevRoute = pages[pages.length-1].route
    //   getApp().globalData.prevRoute = "/" + prevRoute

    //   // 设置isGoBack为true
    //   getApp().globalData.isGoBack = true;
      
    //   // -------------------------------------------------
    //    // 没有登录
    //    wx.showToast({
    //     title: '请先登录',
    //     icon:"none"
    //   })
    //   // 去登录页面
    //   setTimeout(()=>{
    //     wx.switchTab({
    //       url: '/pages/user/user',
    //     })
    //   },1000)
    //   return;
    // }
    wx.switchTab({
      url: '/pages/cart/cart',
    })
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: async function (options) {

    let cartTotalRes = await GetGoodsCountApi()
    this.setData({
      goodsCount:cartTotalRes.data.cartTotal.goodsCount
    })

    // 加载详情页时，就存储ID
    getApp().globalData.detailsId = options.id;

    let res = await GetGoodsDetailApi({
      data:{
        id:options.id
      }
    });
    // 相关商品
    let goodsAboutRes = await GetGoodsRelatedApi({
      data:{
        id:options.id
      }
    })
    let {gallery, info, attribute, issue, productList} = res.data;
    // replace替换字符
    info.goods_desc = info.goods_desc.replace(/<img/g, '<img class="img"');
    
    this.setData({
      gallery, 
      info, 
      attribute, 
      issue, 
      productList,
      goodsList:goodsAboutRes.data.goodsList
    })
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