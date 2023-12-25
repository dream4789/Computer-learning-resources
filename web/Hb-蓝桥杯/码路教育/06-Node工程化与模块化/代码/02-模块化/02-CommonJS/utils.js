let PI = 3.14;

function formatTime() {
    return "2022-09-08"
}

function sum(num1, num2) {
    return num1 + num2;
}

console.log("看我执行不执行~")

// 导出去了三个数据
console.log(exports); // {}
exports.PI = PI;
exports.formatTime = formatTime;
exports.sum = sum;
console.log(exports);