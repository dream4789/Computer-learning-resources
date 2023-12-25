// pages/details/details.js
import {GetGoodsDetailApi,GetGoodsRelatedApi} from "../../api/api"

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
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: async function (options) {
    console.log(options.id);
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