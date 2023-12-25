import {
  GetCartIndex,
  ChangeStatus,
  Step,
  CartDel
} from "../../api/api"
Page({
  data: {
    cartList: [], // 购物车的数据
    cartTotal: 0, // 购物车中商品的数据
    isEmptyShow: true, // 控制空组件是否显示
    isAllChecked: false, // 表示全选按钮是否选中

    bjq: false, // 步进器是否显示
    btn: true, // 控制编辑或完成是否显示
    isDisable: false, // 控制复选框是否可以选中
  },

  // 点击编辑
  edit() {
    this.setData({
      bjq: true,
      btn: false,
      isDisable: true
    })
  },
  // 点击完成
  finish() {
    this.setData({
      bjq: false,
      btn: true,
      isDisable: false
    })
  },

  // 点击+1或-1
  async stepChange(e) {
    await Step(e.currentTarget.dataset.goods_id, e.currentTarget.dataset.id, e.detail, e.currentTarget.dataset.product_id)
    this.onLoad();
  },
  // 删除
  async del(e) {
    await CartDel(String(e.currentTarget.dataset.product_id));
    this.onLoad();
  },
  // 切换商品的状态（是否选中）
  async changeGoodStatus(e) {
    let a = e.currentTarget.dataset.a ? 0 : 1;
    let b = String(e.currentTarget.dataset.b);
    let res = await ChangeStatus(a, b)
    this.setData({
      cartList: res.data.cartList,
      cartTotal: res.data.cartTotal
    })
    if (res.data.cartTotal.checkedGoodsCount == res.data.cartTotal.goodsCount) {
      this.setData({
        isAllChecked: true
      })
    } else {
      this.setData({
        isAllChecked: false
      })
    }
  },
  // 全选或反选
  selectAll(e) {
    let checked = e.currentTarget.dataset.a;
    if (checked == true) { // 得到true，说明全选按钮是选中的，就需要取消所有的商品的选中
      for (let i = 0; i < this.data.cartList.length; i++) {
        this.data.cartList[i].checked = false;
        this.setData({
          cartList: this.data.cartList
        })
      }
    } else {
      for (let i = 0; i < this.data.cartList.length; i++) {
        this.data.cartList[i].checked = true;
        this.setData({
          cartList: this.data.cartList
        })
      }
    }
    this.setData({
      isAllChecked: !this.data.isAllChecked
    })
  },
  async onLoad() {
    let res = await GetCartIndex();
    this.setData({
      cartList: res.data.cartList,
      cartTotal: res.data.cartTotal
    })
    if (res.data.cartList.length > 0) {
      this.setData({
        isEmptyShow: false
      })
    }
    // 判断一下 全选按钮中否需要选中
    if (this.data.cartTotal.checkedGoodsCount > 0) {
      if (this.data.cartTotal.checkedGoodsCount == this.data.cartTotal.goodsCount) {
        this.setData({
          isAllChecked: true
        })
      } else {
        this.setData({
          isAllChecked: false
        })
      }
    }
  },
  onShow() {
    this.onLoad();
    this.getTabBar().setData({
      active: 3
    })
  },
})