const dbConfig = require('./dbConfig')
const MongoClient = require('mongodb').MongoClient
const EventEmitter = require('events')
class Mongo {
    constructor(dbConfig) {
        this.dbConfig = dbConfig
        this.emitter = new EventEmitter()
        // 创建客户端
        this.client = new MongoClient(this.dbConfig.url)
        // 建立连接
        this.client.connect((err) => {
            if (err) throw err
            console.log('连接数据库成功')
            this.emitter.emit('connect')
        })
    }
    once(eventName, cb) {
        //   只会连接一次
        this.emitter.once(eventName, cb)
    }
    //   获取集合的方法
    col(colName, dbName = this.dbConfig.dbName) {
        return this.client.db(dbName).collection(colName)
    }
}
module.exports = new Mongo(dbConfig)