
import ajax from "./ajax"
// 请求首页数据
export const GetHomeDataApi = () => ajax("/index/index")
// 请求搜索页面的历史和热门数据
export const HistoryHotApi = () => ajax("/search/index")
// 请求清除历史记录
export const ClearHistoryApi = params => ajax("/search/clearhistory",params)
// 请求商品列表信息
export const GoodsSearchApi = params => ajax("/goods/list",params)
// 请求提示列表数据
export const TipsListApi = params => ajax("/search/helper",params)
// 请求登录/注册
export const LoginByWebApi = params => ajax("/auth/loginByWeb",params)
// 请求详情页数据
export const GetGoodsDetailApi = params => ajax("/goods/detail",params)
// 请求相关产品数据
export const GetGoodsRelatedApi = params => ajax("/goods/related",params)
// 请求加入购物车
export const AddToCartApi = params => ajax("/cart/add",params)
// 请求购物车数量
export const GetGoodsCountApi = params => ajax("/cart/goodscount",params)
// 请求专题页
export const GetTopicList=(params,params2)=>ajax("/topic/list",{data:{
  page:params,
  size:params2
}});
//  请求分类页
export const GetTypeIndex = () => ajax("/catalog/index");
//  请求分类右侧
export const GetTypeCurrent = (params) => ajax("/catalog/current",{data:{id:params}});
