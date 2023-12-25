import ajax from "./ajax"
// 请求首页数据
export const GetHomeDataApi = () => ajax("/index/index")
// 请求搜索页面的历史和热门数据
export const HistoryHotApi = () => ajax("/search/index")
// 请求清除历史记录
export const ClearHistoryApi = params => ajax("/search/clearhistory", params)
// 请求商品列表信息
export const GoodsSearchApi = params => ajax("/goods/list", params)
// 请求提示列表数据
export const TipsListApi = params => ajax("/search/helper", params)
// 请求登录/注册
export const LoginByWebApi = params => ajax("/auth/loginByWeb", params)
// 请求详情页数据
export const GetGoodsDetailApi = params => ajax("/goods/detail", params)
// 请求相关产品数据
export const GetGoodsRelatedApi = params => ajax("/goods/related", params)
// 请求加入购物车
export const AddToCartApi = params => ajax("/cart/add", params)
// 请求购物车数量
export const GetGoodsCountApi = params => ajax("/cart/goodscount", params)
// 请求专题页
export const GetTopicList = (params, params2) => ajax("/topic/list", {
  data: {
    page: params,
    size: params2
  }
});
//  请求分类页
export const GetTypeIndex = () => ajax("/catalog/index");
//  请求分类右侧
export const GetTypeCurrent = (params) => ajax("/catalog/current", {
  data: {
    id: params
  }
});
// 二级分类
export const GetCategory = (params) => ajax("/goods/category", {
  data: {
    id: params
  }
});
export const GetCategory2 = (params) => ajax("/goods/list", {
  data: {
    categoryId: params
  }
});

// ----------------------------------------------------

// 获取购物车数据
export const GetCartIndex = () => ajax("/cart/index");

// 删除商品
export const CartDel = (params) => ajax("/cart/delete", {
  data: {
    productIds: params
  },
  method: "post"
});

// 步进器
export const Step = (params, params2, params3, params4) => ajax("/cart/update", {
  data: {
    goodsId: params,
    id: params2,
    number: params3,
    productId: params4
  },
  method: "POST"
});

//  点击切换商品选中状态
export const ChangeStatus = (params, params2) => ajax("/cart/checked", {
  data: {
    isChecked: params,
    productIds: params2
  },
  method: "POST"
});