// let name = "wc";
// let age = 18;
// function sum() {
//     return 110;
// }

let moduleA = (function () {
    let name = "wc";
    let age = 18;
    function sum() {
        return 110;
    }
    return {
        name,
        age,
        sum
    }
}())