// // 作业：利用函数封装Cache工具函数
// class Cache {
//     // constructor(isLocal) {
//     //     isLocal = isLocal || true;
//     // }
//     constructor(isLocal = true) {
//         this.storage = isLocal ? localStorage : sessionStorage;
//     }
//     setItem(key, value) {
//         if (value) {
//             this.storage.setItem(key, JSON.stringify(value))
//         }
//     }
//     getItem(key) {
//         let value = this.storage.getItem(key);
//         if (value) {
//             value = JSON.parse(value)
//             return value;
//         }
//     }
//     removeItem(key) {
//         this.storage.removeItem(key)
//     }
//     clear() {
//         this.storage.clear()
//     }
//     length() {
//         return this.storage.length;
//     }
// }
// // 如果没有传递参数或传递true，表示localStoage
// let localCache = new Cache();
// // 如果传递一个false，表示会话级别的cache
// let sessionCache = new Cache(false);

class Cache {
    constructor(isLocal = true) {
        this.storage = isLocal ? localStorage : sessionStorage;
    }
    setItem(key, value) {
        if (value) {
            this.storage.setItem(key, JSON.stringify(value))
        }
    }
    getItem(key) {
        let value = this.storage.getItem(key);
        if (value) {
            value = JSON.parse(value)
            return value;
        }
    }
    removeItem(key) {
        this.storage.removeItem(key)
    }
    clear() {
        this.storage.clear()
    }
    length() {
        return this.storage.length;
    }
}
let localCache = new Cache();
let sessionCache = new Cache(false);