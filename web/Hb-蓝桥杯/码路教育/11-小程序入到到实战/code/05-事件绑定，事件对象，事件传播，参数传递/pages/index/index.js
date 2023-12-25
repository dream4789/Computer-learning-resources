Page({

  /**
   * 页面的初始数据
   */
  data: {
      titles:["电影","音乐","娱乐","体育"],
      currentIndex:0
  },
  onBtnTap(event){
    console.log(event);
    console.log("点了弄啥~");
  },
  onOuterTap(event){
    // target触发事件的元素  target表示里面的元素
    // currentTarget处理事件的元素
    // console.log(event.target);
    // console.log(event.currentTarget);

    console.log(event.currentTarget.dataset.name);
  },
  onArguemntsTap(event){
    console.log(event.currentTarget.dataset);
  },
  onItemTap(event){
    this.setData({
      currentIndex:event.currentTarget.dataset.index
    })
  },
  onView01Tap(){
    console.log("onView01Tap");
  },
  onView02Tap(){
    console.log("onView02Tap");
  },
  onView03Tap(){
    console.log("onView03Tap");
  },
  onView01CaptureTap(){
    console.log("onView01CaptureTap");
  },
  onView02CaptureTap(){
    console.log("onView02CaptureTap");
  },
  onView03CaptureTap(){
    console.log("onView03CaptureTap");
  },

  onArguemntsTap02(event){
    console.log(event.mark);
  }
})