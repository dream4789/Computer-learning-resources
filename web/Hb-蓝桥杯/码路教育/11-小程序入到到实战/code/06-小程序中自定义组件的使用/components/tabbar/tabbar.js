// components/tabbar/tabbar.js
Component({
  /**
   * 组件的属性列表
   */
  properties: {
    tabbarData:{
      type:Array,
      value:[]
    }
  },

  /**
   * 组件的初始数据
   */
  data: {
    currentIndex:0
  },

  /**
   * 组件的方法列表
   */
  methods: {
    itemTap(event){
      // console.log(event.currentTarget.dataset);
      let index = event.currentTarget.dataset.index;
      this.setData({
        currentIndex:index
      })

      this.triggerEvent("indexChange",index)
    }
  }
})
