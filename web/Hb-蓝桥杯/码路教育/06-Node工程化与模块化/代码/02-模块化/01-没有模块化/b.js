// let name = "xq";
// let age = 28;
// function sum() {
//     return 220;
// }

let moduleB = (function () {
    let name = "xq";
    let age = 28;
    function sum() {
        return 220;
    }
    return {
        name,
        age,
        sum
    }
}())