// utils有人叫service,有人叫api,有人叫http,有人叫request

// 不同人的封装是一样的，网上有大量别人封装的代码
export default function ajax(options){
  return new Promise((resolve,reject)=>{
    // 写异步代码
    wx.request({
      url: options.url,
      method:options.method || "get",
      timeout:options.timeout || 5000,
      data:options.data || {}, 
      success:(res)=>{
        resolve(res.data)
      },
      fail:(err)=>{
        reject(err)
      }
    })
  })
}

// import ajax from "./ajax.js"
// ajax({url:"xxx.com",method:"get",data:{}}).then().catch()
// let res = await ajax({url:"xxx.com",method:"get",data:{}})