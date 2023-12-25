Component({
  properties:{
    goodsList:{
      type:Array,
      value:[]
    },
    filterCategory:{
      type:Array,
      value:[]
    },
    filterCategoryCurrentID:{
      type:Number,
      value:0
    }
  },
  data: {
    option1: [
      { text: '价格由高到低', value: "desc" },
      { text: '价格由低到高', value: "asc" },
    ],
    // value1: "desc",
    value1: "",
  },
  methods:{
    cateChange(e){
      // console.log(e.detail);
      this.triggerEvent("fn",e.detail)
    },
    // 价格排序
    priceChange(e){
      // console.log("e.detail:",e.detail);
      this.triggerEvent("fn2",e.detail)
    }
  }
})