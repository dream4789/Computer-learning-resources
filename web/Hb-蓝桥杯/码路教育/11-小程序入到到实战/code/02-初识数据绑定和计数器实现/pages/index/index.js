Page({

  /**
   * 页面的初始数据
   * 给html提供数据
   */
  data: {
    // 这里面定义的数据并不是响应式数据
    msg:"hello 码路~",
    singers:["林忆莲","谭晶","迪玛希","杜丽莎","狮子合唱团","袁娅维"],
    counter:0
  },

  // 加1
  increment(){
    // 在vue中，data中的数据是响应式的，数据变了，界面重新渲染
    // 但是：在小程序中，data中的数据并不是响应式的，数据变了，界面也不会渲染
    // 需要告诉渲染层重新渲染数据：
    //    setDate() 可以重新渲染数据  更新状态机
    // this.data.counter += 1;
    // console.log(this.data.counter);

    // 更新状态机  setDate可以让界面重新渲染
    this.setData({
      counter: this.data.counter + 1
    })
  },
  // 减1
  decrement(){
    this.setData({
      counter: this.data.counter - 1
    })
  },
})