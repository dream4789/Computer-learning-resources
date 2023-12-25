Component({
  properties:{
    goodsList:{
      type:Array,
      value:[]
    }
  },
  methods:{
    toToDetais(e){
      let id=e.currentTarget.id;
      wx.navigateTo({
        url:`/pages/details/details?id=${id}`,
      })
    }
  }
})