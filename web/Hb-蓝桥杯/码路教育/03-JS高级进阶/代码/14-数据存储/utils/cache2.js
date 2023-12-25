
function Cache(isLocal = true) {
    // isLocal ? localStorage : sessionStorage;  ==> localStorage / sessionStorage
    this.storage = isLocal ? localStorage : sessionStorage;
}

Cache.prototype.setItem = function (key, value) {
    if (value) {
        this.storage.setItem(key, JSON.stringify(value))
    }
}

Cache.prototype.getItem = function (key) {
    let value = this.storage.getItem(key);
    if (value) {
        value = JSON.parse(value)
        return value;
    }
}

Cache.prototype.removeItem = function (key) {
    this.storage.removeItem(key)
}

Cache.prototype.clear = function (key) {
    this.storage.clear()
}

Cache.prototype.length = function (key) {
    return this.storage.length;
}

let localCache = new Cache();
let sessionCache = new Cache(false);