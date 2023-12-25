
// https://passport2.chaoxing.com/js/common/crypto-js.min.js

// import "crypto-js.js"
const CryptoJS = require('./crypto-js.js')

let phone = 11111111;
let pwd = 123456;

let transferKey = "u2oh6Vu^HWe4_AES";
pwd = encryptByAES(pwd, transferKey);
phone = encryptByAES(phone, transferKey);
console.log(pwd, phone)

function encryptByAES(message, key) {
	let CBCOptions = {
		iv: CryptoJS.enc.Utf8.parse(key),
		mode: CryptoJS.mode.CBC,
		padding: CryptoJS.pad.Pkcs7
	};
	let aeskey = CryptoJS.enc.Utf8.parse(key);
	let secretData = CryptoJS.enc.Utf8.parse(message);
	let encrypted = CryptoJS.AES.encrypt(
		secretData,
		aeskey,
		CBCOptions
	);
	return CryptoJS.enc.Base64.stringify(encrypted.ciphertext);
}
/*
CBCOptions:iv:i.init
sigBytes:16
words:(4)[1966239592, 911635806, 1213687092, 1598113107]
	[[Prototype]]:Object
	
mode: {$super: {…},Encryptor: {…},Decryptor: {…},init: ƒ}
padding: {pad: ƒ,unpad: ƒ}
	[[Prototype]]:Object
	
aeskey:i.init
sigBytes:16
words:(4)[1966239592, 911635806, 1213687092, 1598113107]
	[[Prototype]]:Object
	
encrypted: {$super: {…},ciphertext: i.init,key: i.init,iv: i.init,init: ƒ,…}
key:"u2oh6Vu^HWe4_AES"
message:"123456banban"

secretData:i.init
sigBytes:12
words:(3)[825373492, 892756577, 1851941230]
	[[Prototype]]:Object
*/

function encryptByDES(message, key) {
	var keyHex = CryptoJS.enc.Utf8.parse(key);
	var encrypted = CryptoJS.DES.encrypt(message, keyHex, {
		mode: CryptoJS.mode.ECB,
		padding: CryptoJS.pad.Pkcs7
	});
	return encrypted.ciphertext.toString();
}
