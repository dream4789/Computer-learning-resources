Component({
  properties:{
    hotKeywordList:{
      type:Array,
      value:[]
    },
    historyKeywordList:{
      type:Array,
      value:[]
    },
  },
  methods:{
    // 清空历史记录
    async clearFn(){
        this.triggerEvent("clearHistory")
    },
    // 点击热门搜索中的tag，去商品列表
    gotoProduct(e){
      // this.triggerEvent("fn")
      // console.log(e.currentTarget.dataset.kw);

      this.triggerEvent("fn",{
        num:3,
        keyword:e.currentTarget.dataset.kw
      })
    }
  }
})