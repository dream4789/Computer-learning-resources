import { GetTopicList } from "../../api/api.js"
Page({
  data: {
    TopicList:'',
    pageSize:'',
    currentPage:''
  },
  async onLoad(options) {
    let res=await GetTopicList();
    this.setData({
      TopicList:res.data
    })
  },
  onShow() {
    this.getTabBar().setData({
      active: 1
    })
  },
})