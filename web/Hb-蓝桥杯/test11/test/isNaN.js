let a
a = 11
console.log(isNaN(a))

a = '11c'
console.log(isNaN(a))

a = 99999999999999999999999999999999
console.log(isNaN(a))

a = 00231
console.log(isNaN(a))


eval('console.log("111")')


var age = 1;
console.log((age >= 18) ? true : false)


console.log(null ?? 'I win')
console.log(undefined ?? 'Me too')
console.log(false ?? 'I lose')
console.log(0 ?? 'I lose again')
console.log('' ?? 'Damn it' )

console.log("\u1E9B\u0323".normalize("NFC"))  // 标准化
console.log(Number.EPSILON)  // 2.220446049250313e-16

const arr = [1, 2, 3]
const { 1: a1, 0: b, 2: c } = arr
console.log(a1, b, c) // 2 1 3
