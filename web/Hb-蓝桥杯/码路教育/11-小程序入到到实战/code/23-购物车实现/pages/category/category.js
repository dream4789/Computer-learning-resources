import {GetTypeIndex} from "../../api/api.js"
import {GetTypeCurrent} from "../../api/api.js"
Page({
  data: {
    activeKey: 0,
    GetTypeIndex: '',
    GetTypeCurrent: '',
    typeId: '',
    currentCategory: '',
    subCategoryList: ''
  },
  async onLoad(options) {
    let res = await GetTypeIndex();
    this.setData({
      GetTypeIndex: res.data
    })
    let ress = await GetTypeCurrent('1005000');
    this.setData({
      currentCategory: ress.data.currentCategory,
      subCategoryList: ress.data.currentCategory.subCategoryList
    })
  },
  async daoHang(v) {
    let res = await GetTypeCurrent(v.currentTarget.dataset.id);
    this.setData({
      currentCategory: res.data.currentCategory,
      subCategoryList: res.data.currentCategory.subCategoryList
    })
    this.setData({
      typeId: v.currentTarget.dataset.id
    })
  },
  onShow() {
    this.getTabBar().setData({
      active: 2
    })
  },
})