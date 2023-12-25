import Mock from 'mockjs'


Mock.mock('/api/stat/line', 'get', () => {
  return Mock.mock({
    code: 1,
    days: ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"],
    'count|7': ["@natural(800,1500)"],
    'count1|7': ["@natural(400,1000)"]
  })
})


Mock.mock('/api/stat/pie', 'get', () => {
  return Mock.mock({
    code: 1,
    'title|5': ["@ctitle(3,6)"],
    'list|5': [{
      value: "@natural(100,1600)"
    }]
  })
})