let address = "bj";

// exports.address = address;


// 导出的代码，不能放到异步代码中
setTimeout(() => {
    exports.address = address;
}, 3000)