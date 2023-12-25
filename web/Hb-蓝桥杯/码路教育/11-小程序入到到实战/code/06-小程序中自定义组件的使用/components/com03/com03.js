// components/com03/com03.js
Component({
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
    clickFn(){
      // vue: this.$emit("malu")

      // triggerEvent 小程序中，通过triggerEvent触发自定义事件
      this.triggerEvent("malu","给父1000万")
    }
  }
})
