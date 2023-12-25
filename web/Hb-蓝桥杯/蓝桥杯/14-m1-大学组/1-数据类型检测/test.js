const {getType} = require('./main')
// 示例
const testArr = [
	"s",
	0,
	false,
	undefined,
	Symbol(),
	function() {},
	123n,
	null,
	{},
	[],
	new Date(),
	new Map(),
	new Set(),
	/a/,
];
const result = testArr.map((item) => getType(item));
console.log("得到的结果：", result);
/*
  得到的结果：[
	'string',  'number',
	'boolean', 'undefined',
	'symbol',  'function',
	'bigint',  'null',
	'object',  'array',
	'date',    'map',
	'set',     'regExp'
  ]
  
  得到的结果： [
    'string',          'number',
    'boolean',         'undefined',
    'symbol',          'function',
    'bigint',          '[object Null]',
    '[object Object]', '[object Array]',
    '[object Date]',   '[object Map]',
    '[object Set]',    '[object RegExp]'
  ]
*/
