import {
  GetCategory,
  GetCategory2
} from "../../api/api.js"
Page({
  data: {
    active: "",
    brotherCategory: [], // 标题栏种类数组
    data: [] // 下面数据
  },
  tiao(v) {
    wx.navigateTo({
      url: "/pages/details/details?id=" + v.currentTarget.dataset.ji
    })
  },
  async onClick(name) {
    let res2 = await GetCategory2(name.detail.name)
    this.setData({
      data: res2.data.data,
    })
  },
  async onLoad(options) {
    let a = Number(options.id)
    let res = await GetCategory(a)
    this.setData({
      brotherCategory: res.data.brotherCategory,
      active: Number(options.id)
    })
    let res2 = await GetCategory2(options.id)
    this.setData({
      data: res2.data.data,
    })
  },
})