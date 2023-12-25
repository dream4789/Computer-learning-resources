let n1 = 10; // 定义模块私有成员 n1
let n2 = 20; // 定义模块私有成员 n2 (外界访问不到n2，因为没有被共享出去)
function show() {}; //定义模块私有方法 show

export default {
  n1,
  show
} // 默认导出
