const mongoose = require("mongoose");
const config = require("../config");

mongoose.connect(`mongodb://${config.db.host}/${config.db.dbName}`, {
	useNewUrlParser: true,
	useUnifiedTopology: true,
});
const db = mongoose.connection;
db.on("error", () =>{console.error.bind(console, "connection error:")});
db.once("open", async () => {
	console.log("链接数据库成功");
});
