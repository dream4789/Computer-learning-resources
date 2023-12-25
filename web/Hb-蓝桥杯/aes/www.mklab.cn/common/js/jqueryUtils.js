/**
 *	jquery tools plugins
 *
 *	auth xinchenglong
 *
 * 	date 2013.7.26
 */
;(function($){

	// !! === onbeforeunload

	/*--------------- RegexEnum --------------------------------*/
	var RegexEnum = {
        intege  : "^-?[1-9]\\d*|0$",    					//整数
        intege_p: "^[1-9]\\d*|0$",      					//正整数
        intege_n: "^-[1-9]\\d*|0$",     					//负整数
        num     : "^([+-]?)\\d*\\.?\\d+$",                  //数字
        decmal  : "^([+-]?)\\d*\\.\\d+$",                   //浮点数
        decmal_p: "^[1-9]\\d*.\\d*|0.\\d*[1-9]\\d*$",       //正浮点数
        decmal_n: "^-([1-9]\\d*.\\d*|0.\\d*[1-9]\\d*)$",    //负浮点数
        email   : "^\\w+((-\\w+)|(\\.\\w+))*\\@[A-Za-z0-9]+((\\.|-)[A-Za-z0-9]+)*\\.[A-Za-z0-9]+$",     //邮件
        color   : "^[a-fA-F0-9]{6}$",               		//颜色
        url     : "^http[s]?:\\/\\/([\\w-]+\\.)+[\\w-]+([\\w-./?%&=]*)?$",      //url
        chinese : "^[\\u4E00-\\u9FA5\\uF900-\\uFA2D]+$",                        //仅中文
        ascii   : "^[\\x00-\\xFF]+$",               		//仅ACSII字符
        zipcode : "^\\d{6}$",                       		//邮编
        mobile  : "^13[0-9]{9}|15[012356789][0-9]{8}|18[0256789][0-9]{8}|147[0-9]{8}$",                 //手机
        ip4     : "^(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)\\.(25[0-5]|2[0-4]\\d|[0-1]\\d{2}|[1-9]?\\d)$",  //ip地址
        notempty: "^\\S+$",                         		//非空
        picture : "(.*)\\.(jpg|bmp|gif|ico|pcx|jpeg|tif|png|raw|tga)$",         //图片
        rar     : "(.*)\\.(rar|zip|7zip|tgz)$",                                 //压缩文件
        date    : "^\\d{4}(\\-|\\/|\.)\\d{1,2}\\1\\d{1,2}$",                    //日期
        qq      : "^[1-9]*[1-9][0-9]*$",            		//QQ号码
        tel     : "^(([0\\+]\\d{2,3}-)?(0\\d{2,3})-)?(\\d{7,8})(-(\\d{3,}))?$", //电话号码的函数(包括验证国内区号,国际区号,分机号)
        letter  : "^[A-Za-z]+$",                    		//字母
        letter_u: "^[A-Z]+$",                       		//大写字母
        letter_l: "^[a-z]+$",                       		//小写字母
        idcard  : "^[1-9]([0-9]{14}|[0-9]{17})$"    		//身份证
    };

	/*--------------- jquery static test --------------------------------*/
	$.extend({
    	viewJson : function(json){					//查看json的视图
			if($.type(json) === 'object'){
				var temp = "";
				$.each(json, function(key, val){
					temp += key + " -> " + val + "\n";
				});
				return temp;
			}else if($.type(json) === 'array'){
				var temp = "";
				$.each(json, function(i, v){
					temp += i + " --- ";
					$.each(v, function(key, val){
						temp += key + " -> " + val + " | ";
					});
					temp += "\n";
				});
				return temp;
			}
		},

		viewOffset : function(id){					//查看当前容器以及body，window的offset
			var $div = $(id)[0];
			var $body = $("body")[0];
			var str =
				"\n div.offsetTop    = " + $div.offsetTop+
				"\nbody.offsetTop    = " + $body.offsetTop+

				"\n div.offsetLeft   = "+ $div.offsetLeft+
				"\nbody.offsetLeft   = "+ $body.offsetLeft+

				"\n div.offsetWidth  = "+$div.offsetWidth+
				"\nbody.offsetWidth  = "+$body.offsetWidth+

				"\n div.offsetHeight = "+$div.offsetHeight+
				"\nbody.offsetHeight = "+$body.offsetHeight+

				"\nbody.clientWidth  = " + $body.clientWidth+
				"\nbody.clientHeight = " + $body.clientHeight+
				"\nbody.scrollWidth  = " + $body.scrollWidth+
				"\nbody.scrollHeight = " + $body.scrollHeight+
				"\nbody.scrollTop    = " + $body.scrollTop+
				"\nbody.scrollLeft   = " + $body.scrollLeft+

				"\nwindow.screenTop  = "+window.screenTop+
				"\nwindow.screenLeft = "+window.screenLeft+
				"\nwindow.screen.width       = "+window.screen.width+
				"\nwindow.screen.availWidth  = "+window.screen.availWidth+
				"\nwindow.screen.height      = "+window.screen.height+
				"\nwindow.screen.availHeight = "+window.screen.availHeight;
			return str;
		},

		client : function() {						// 获得浏览器的内核与外壳的类型和版本
			// 浏览器内核类型(只有五种)
			var engine = {
				ie : 0,
				webkit : 0,
				gecko : 0,
				opera : 0,
				khtml : 0
			};
			// 浏览器外壳类型（360浏览器、傲游、腾讯QQ\TT浏览器、世界之窗、彗星浏览器、绿色浏览器、传统IE、谷歌Chrome、网景netscape、火狐、Opera、苹果Safari等等）
			var shell = {
				se360 : 0,
				se : 0,
				maxthon : 0,
				qq : 0,
				tt : 0,
				theworld : 0,
				cometbrowser : 0,
				greenbrowser : 0,
				ie : 0,
				chrome : 0,
				netscape : 0,
				firefox : 0,
				opera : 0,
				safari : 0,
				konq : 0
			};
			// 获得客户端浏览器的信息
			var ua = navigator.userAgent.toLowerCase();
			for ( var type in engine) {
				if (typeof type === 'string') {
					var regexp = 'gecko' === type ? /rv:([\w.]+)/ : RegExp(type + '[ \\/]([\\w.]+)');
					if (regexp.test(ua)) {
						engine.version = window.opera ? window.opera.version() : RegExp.$1;// 浏览器内核版本
						engine[type] = parseFloat(engine.version);
						engine.type = type;// 浏览器内核类型
						break;
					}
				}
			}
			for ( var type in shell) {
				if (typeof type === 'string') {
					var regexp = null;
					switch (type) {
						case "se360":
							regexp = /360se(?:[ \/]([\w.]+))?/;
							break;
						case "se":
							regexp = /se ([\w.]+)/;
							break;
						case "qq":
							regexp = /qqbrowser\/([\w.]+)/;
							break;
						case "tt":
							regexp = /tencenttraveler ([\w.]+)/;
							break;
						case "safari":
							regexp = /version\/([\w.]+)/;
							break;
						case "konq":
							regexp = /konqueror\/([\w.]+)/;
							break;
						case "netscape":
							regexp = /navigator\/([\w.]+)/;
							break;
						default:
							regexp = RegExp(type + '(?:[ \\/]([\\w.]+))?');
					}
					if (regexp.test(ua)) {
						shell.version = window.opera ? window.opera.version() : RegExp.$1 ? RegExp.$1 : 'unknown';// 浏览器外壳版本
						shell[type] = parseFloat(shell.version);
						shell.type = type;// 浏览器外壳类型
						break;
					}
				}
			}
			// 返回浏览器内核与外壳的类型和版本：engine为内核，shell为外壳
			return {
				engine : engine,
				shell : shell,
				test : function(type){
					if(typeof(type) == "string"){
						var result = /\w+\d+/.test(type) ? (shell.type+shell.version).indexOf(shellType) : shell.type.indexOf(type);
						return result > -1;
					}
				}
			};
		}

    });

	/*--------------- jquery static Date ---------------------*/
	$.extend({
		compare : function(){

		},

		nows : function(){
			return Date.hasOwnProperty("now") ? Date.now() : +(new Date());
		},

		isTime : function (str){    			 	//是否为短时间，形如 (13:04:06)
            var time = str.match(/^(\d{1,2})(:)?(\d{1,2})\2(\d{1,2})$/);
            return time == null ? false : (time[1]>24 || time[3]>60 || time[4]>60) ? false : true;
        },

        isDate : function (str){    			 	//是否为短日期，形如 (2003-12-05)
            var r = str.match(/^(\d{1,4})(-|\/)(\d{1,2})\2(\d{1,2})$/);
            if(r == null)return false;
            var d= new Date(r[1], r[3]-1, r[4]);
            return (d.getFullYear()==r[1]&&(d.getMonth()+1)==r[3]&&d.getDate()==r[4]);
        },

        isDateTime : function (str){    		  	//是否为长时间，形如 (2003-12-05 13:04:06)
            var reg = /^(\d{1,4})(-|\/)(\d{1,2})\2(\d{1,2}) (\d{1,2}):(\d{1,2}):(\d{1,2})$/;
            var r = str.match(reg);
            if(r == null) return false;
            var d= new Date(r[1], r[3]-1,r[4],r[5],r[6],r[7]);
            return (d.getFullYear()==r[1]&&(d.getMonth()+1)==r[3]&&d.getDate()==r[4]&&d.getHours()==r[5]&&d.getMinutes()==r[6]&&d.getSeconds()==r[7]);
        },

        parseDate : function(time, expr){ 			//long or GMT parseDate
            var mydate = new Date(time);

            var year = mydate.getFullYear();
            var month = mydate.getMonth() + 1;
            var date = mydate.getDate();
            var hours = mydate.getHours();
            var minutes = mydate.getMinutes();
            var seconds = mydate.getSeconds();
            month = month.toString().length == 1 ? "0"+month : month;
            date = date.toString().length == 1 ? "0"+date : date;
            hours = hours.toString().length == 1 ? "0"+hours : hours;
            minutes = minutes.toString().length == 1 ? "0"+minutes : minutes;
            seconds = seconds.toString().length == 1 ? "0"+seconds : seconds;

            var result = "";
            if(expr == "yyyy-mm-dd"){
                result = year+"-"+month+"-"+date;
            }else if(expr == "HH:MM:ss"){
                result = hours+":"+minutes+":"+seconds;
            }else{
                result = year+"-"+month+"-"+date+" "+hours+":"+minutes+":"+seconds;
            }
            return result;
        },

        format : function(time, expr){				//待修改
            if(/\d{13}/.test(time)){
                return $.parseDate(time, expr);
            }
        }
	});

	/*--------------- jquery instance Array ---------------------
	$.extend(Array.prototype, {
		removeByVal : function(val, flag){
		    for(var i=0; i<this.length; i++) {
		        if(this[i] == val) {
		            this.splice(i, 1);
		            if(flag) continue;
		            else break;
		        }
		    }
		},
		viewProp : function(){
			var show = [];
			var names = Object.getOwnPropertyNames(Array);
			for (var i = 0; i < names.length; i++) {
			    show.push(names[i]);
			}
			alert(show.sort().join("  ->\n"));
		}
	});*/

	/*--------------- jquery static method ---------------------*/
	$.extend({
		setArgsType : function(val, def){			//设置函数方法的子方法  ->内部方法
			if($.type(val) == "string")	{ def.str = val; 	return def; }
			if($.type(val) == "boolean"){ def.bool = val; 	return def; }
			if($.type(val) == "array")	{ def.arr = val; 	return def; }
			if($.type(val) == "function"){ def.fun = val; 	return def; }
			if($.type(val) == "object")	{ def.obj = val; 	return def; }
			if($.type(val) == "regexp")	{ def.reg = val; 	return def; }
			if($.type(val) == "number")	{ def.num = val; 	return def; }
		},

		setArgs : function(){						//设置函数参数方法
			//string boolean array function object number regexp date //s-a-n-f-d-r-b-o
			var def = {
				str : "",
				bool: false,
				arr : [],
				num : 0,
				fun : null,
				obj : null,
				reg : null
			};
			var orders = arguments[arguments.length-1].split("-");
			for(var i=0; i<orders.length; i++){
				var val = arguments[i];
				$.setArgsType(val, def);
				if(orders[i] == "s"){ arguments[i] = def.str; continue;}
				if(orders[i] == "b"){ arguments[i] = def.bool;continue;}
				if(orders[i] == "a"){ arguments[i] = def.arr; continue;}
				if(orders[i] == "f"){ arguments[i] = def.fun; continue;}
				if(orders[i] == "o"){ arguments[i] = def.obj; continue;}
				if(orders[i] == "n"){ arguments[i] = def.num; continue;}
				if(orders[i] == "r"){ arguments[i] = def.reg; continue;}
			}
			return arguments;
		},

		getCheck : function(name, context){			//根据name和上下文得到所有的复选框
			var selector = "input[name='"+name+"']";
			return context ? $(context).find(selector) : $(selector);
		},

		getChecked : function(name, context){		//根据name和上下文得到所有选中的复选框
			var selector = "input[name='"+name+"']:checked";
			return context ? $(context).find(selector) : $(selector);
		},

		checkAll : function(name, type, context){	//选中所有复选框
			return $.getCheck(name, context).prop("checked", type);
		},

		checkHandle : function(options){			//操作选中不同个数复选框
	        var def = {
	        	checkAll 	: "",
	        	checkName 	: "",
	            context		: "",
	            check0 		: null,
	            check1 		: null,
	            checkn 		: null
	        };
	        $.extend(def, options);
	        var $context = def.context ? $(def.context) : $("body");
	        def.checkAll && $context.find(def.checkAll).autoOptAll(def.checkName, def.wrap);

	        var $checked = $.getChecked(def.checkName, def.wrap);
	        var result = undefined;
	        if($checked.size() <= 0){
	            result = def.check0();
	        }else if($checked.size() == 1){
	            result = def.check1($checked);
	        }else if($checked.size() > 1){
	            result = def.checkn($checked);
	        }
	        return (typeof(result) == "undefined" || result) ? true : false;
	    },

		checkVals : function(name, context){		//得到选中复选框的值  ->返回数组
			return $.getCheck(name, context).checkVals();
		},

		minVal : function(x, y){					//返回最小值
			return x < y ? x : y;
		},

		maxVal : function(x, y){					//返回最大值
			return x < y ? y : x;
		},

		isChinese : function(str) {					//字符串是否为中文
            str = str.replace(/(^\s*)|(\s*$)/g, '');
            return /^[\u2E80-\u9FFF]+$/.test(str);
        },

        hasChinese : function(str){					//字符串是否包含中文
            str = str.replace(/(^\s*)|(\s*$)/g, '');
            return /.*?[\u2E80-\u9FFF].*?/.test(str.replace(/(^\s*)|(\s*$)/g, ''));
        },

        byteLen : function(str){                  	//计算字符长度，英文占一个长度，中文两个长度
        	var strs = str.split('');
        	var count = 0;
        	for(i=0, k=strs.length; i<k; i++){
        		$.isChinese(strs[i]) ? count += 2 : count++;
        	};
        	return count;
        },
        
        toFixed : function(num, precision){
        	return Math.round(num * Math.pow(10, precision)) / Math.pow(10,precision);
        },
        
		evalJSON : function(jsonStr){				//字符串转换成json
			var reuslt = (typeof JSON === 'object' && JSON.parse);
			return reuslt ? JSON.parse(jsonStr) : eval('(' + str + ')');
        },

        toJsons : function(json){					//json换成字符串
        	if($.toJson){
        		return $.toJson(json);
        	}
        	var reuslt = (typeof JSON === 'object' && JSON.stringify);
            return reuslt ? JSON.stringify(json) : json;
        },

        getParam : function(key){  					//通过key得到地址栏参数
            var patt = eval("/.*?"+key+"=(.*?)(&|$)/");
            return patt.test(location.search) ? location.search.match(patt)[1] : "";
        },

		encode : function(url){						//字符编码
			return encodeURI(url);
		},

		decode : function(url){						//字符解码
			return decodeURI(url);
		},
		
		parseURL : function(url) {
		    var a =  document.createElement('a');
		    a.href = url;
		    return {
		        source: url,
		        protocol: a.protocol.replace(':',''),
		        host: a.hostname,
		        port: a.port,
		        query: a.search,
		        params: (function(){
		            var ret = {},
		                seg = a.search.replace(/^\?/,'').split('&'),
		                len = seg.length, i = 0, s;
		            for (;i<len;i++) {
		                if (!seg[i]) { continue; }
		                s = seg[i].split('=');
		                ret[s[0]] = s[1];
		            }
		            return ret;
		        })(),
		        file: (a.pathname.match(/\/([^\/?#]+)$/i) || [,''])[1],
		        hash: a.hash.replace('#',''),
		        path: a.pathname.replace(/^([^\/])/,'/$1'),
		        relative: (a.href.match(/tps?:\/\/[^\/]+(.+)/) || [,''])[1],
		        segments: a.pathname.replace(/^\//,'').split('/')
		    };
		},

		arrayXX : function(){
			var temp = ["1", "2", "3"];
			
			// 所有的项都符合时返回true
			var result = temp.every(function(val, index, array){
				alert(val +"-"+ index +"-"+ array);
				return val > 0;
			});
			
			// 其中的一项符合时就返回true
			var result = temp.some(function(val, index, array){
				alert(val +"-"+ index +"-"+ array);
				return val > 0;
			});
			
			// 返回过滤后的数组
			var result = temp.filter(function(val, index, array){
				return val > 1;
			});
			
			// 返回处理后的数组
			var result = temp.map(function(val, index, array){
				return val + 1;
			});
			
			// 对数组进行操作不返回
			temp.forEach(function(val, index, array){
				//
			});
			
			// prev为上一次的结果, 从第二项开始遍历, 返回最终的结果 （reduce, reduceRight）
			var result = temp.reduce(function(prev, cur, index, array){
				return prev+cur;
			});
			var big = Math.pow(2, 53);//javascript最大值
		}
	});

	/*--------------- jquery instance method -------------------*/
	$.extend($.fn, {
		isChecked : function(){						//复选框是否选中
			return this.prop("checked");
		},

		checkAll : function(type){					//选中所有复选框
			return this.prop("checked", type);
		},

		clickOptBtn : function(name, type, context){//全选和取消全选	->bind click
			return this.click(function(){
				$.getCheck(name, context).prop("checked", type);
			});
		},

		autoOptAll : function(name, context){		//设置自动全选和取消全选	->bind click
			return this.click(function(){
				var $check = $.getCheck(name, context);
				$check.prop("checked", $(this).isChecked() ? true : false);
			});
		},

		checkVals : function(){						//得到选中复选框的值  ->返回数组
			var vals = [];
			this.filter(":checked").each(function(i, v){
				vals.push($(v).val());
			});
			return vals;
		},

		autoTmpl : function(url, data, callback){	//自动设置列表模版
			var $this = this;
			if($.type(data) == "function"){
				callback = data;
				data = {};
			}
			$.post(url, data, null, "json").done(function(val){
				$this.tmpl(val, callback);
			});
		},

		tmpl : function(val, callback){				//设置列表模版
			return this.addExe(callback, function(callClient){
				var $this = $(this).eq(0).hide();
				var id = (($this.attr("id") == "undefined") ? "showTpl" : $this.attr("id")+"Tpl");
				$this.nextAll("#"+id).remove();

				var $show = $();
				$.each(val, function(i, v){
					var $tpl = $this.clone(true).prop("id", id).show();
					callClient($tpl, v);
					$.merge($show, $tpl);
				});
				return $this.after($show);
			});
		},

		optTmpl : function(val, hasAll, show, callback){	//设置option模版
			var args = $.setArgs(hasAll, show, callback, "b-s-f");
			hasAll = args[0];
			show = args[1];
			callback = args[2];
			return this.addExe(callback, function(callClient){					//callback是done函数中的回调
				$(this).eq(0).find("option").remove().end();
				var tpl = "<option value=''></option>";
				var $show = hasAll ? $(tpl).val("-1").text(show ? show : "全部") : $();
				$.each(val, function(i, v){
					var $tpl = $(tpl);
					callClient($tpl, v);
					$.merge($show, $tpl);
				});
				return $(this).append($show);
			});
		},

		optRange : function(start, end){			//选中输入框中指定的字符
			return this.each(function() {
				this.focus();
				this.setSelectionRange(start, end);
		    });
		},

		pointer : function(){						//添加手型鼠标样式
			return this.each(function(){
				$(this).css("cursor", "pointer");
			});
		},

		autoUpper : function(){                		//输入框中输入的字母变大写
			return this.each(function(){
				$(this).keyup(function(){
					this.value = this.value.toUpperCase();
				}).trigger("keyup");
			});
		},

		autoLower : function(){		          		//输入框中输入的字母变小写
			return this.each(function(){
				$(this).keyup(function(){
					this.value = this.value.toLowerCase();
				}).trigger("keyup");
			});
		},

		widen : function(id){			          	//输入框自动变长
			return this.each(function(){
				$(this).keyup(function(){
					var len = $.byteLen(this.value);
					len > this.size && (this.size = len + 2);
				});
			});
		},

		input : function(regex){					//输入框内容必须符号要求
			return this.each(function(){
				$(this).keyup(function(){
					this.value = this.value.match(regex);
				}).trigger("keyup");
			});
		},

		addExe : function(callback, execute){
			return this.each(function(){
				if(!!callback){
					execute.call(this, callback);
				}else{
					this.fun = execute;
				}
			});
		},

		done : function(callback){
			return this.each(function(){
				this.fun(callback);
			});
		}

	});

	/*--------------- bPopup -----------------------------------*/
	$.extend($.fn, {
		popup : function(options, handle, callback) {
			var args = $.setArgs(options, handle, callback, "o-s-f");
			options = args[0];
			handle = args[1];
			callback = args[2];
			var defaults = {};
			$.extend(defaults, options);
			$(this).bPopup(defaults, callback);

			if(!!this.easydrag){
	       		this.easydrag();
	       		handle && this.setHandler(handle);
			}
			return this;
		}
	});

	var init = function(){
		for(var p in []){
			Object.defineProperty(Array.prototype, p, {enumerable : false});
		};
	};
	//init();
})(jQuery);

