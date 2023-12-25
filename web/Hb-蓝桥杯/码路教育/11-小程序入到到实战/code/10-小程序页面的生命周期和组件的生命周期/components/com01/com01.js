// components/com01/com01.js
Component({
  // lifetimes是组件的生命周期
  lifetimes:{
    created(){
      // 组件被创建后，执行created
      console.log("组件 created");
    },
    attached(){
      // 在组件实例进入页面节点树时执行
      console.log("组件 attached");
    },
    detached(){
      // 在组件实例被从页面节点树移除时执行
      console.log("组件 detached");
    }
  },

  pageLifetimes:{
    show: function() {
      // 页面被展示
      console.log("组件 pageLifetimes show");
    },
    hide: function() {
      // 页面被隐藏
      console.log("组件 pageLifetimes hide");
    },
  },
  /**
   * 组件的属性列表
   */
  properties: {

  },

  /**
   * 组件的初始数据
   */
  data: {

  },

  /**
   * 组件的方法列表
   */
  methods: {

  }
})
