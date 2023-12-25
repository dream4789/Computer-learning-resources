function loginByPhoneAndPwdSubmit() {
	let phone = $("#phone").val().trim();
	let pwd = $("#pwd").val();
	let fid = $("#fid").val();  // 1
	let refer = $("#refer").val();  // https%3A%2F%2Fi.chaoxing.com
	let forbidotherlogin = $("#forbidotherlogin").val();  // 0
	let t = $("#t").val();  // true
	let _blank = $("#_blank").val();  // 1
	let doubleFactorLogin = $("#doubleFactorLogin").val();  // 0
	let independentId = $("#independentId").val();  // 0
	if(t == "true"){
		let transferKey = "u2oh6Vu^HWe4_AES";
		pwd = encryptByAES(pwd, transferKey);
		phone = encryptByAES(phone, transferKey);
	}
	let validate = $("#validate").val();
	if(undefined == validate){
		validate = "";
	}
	$.ajax({
		url: _CP_+"/fanyalogin",
		type:"post",
		dataType : 'json',
		data: {
			'fid': fid,
			'uname': phone,
			'password': pwd,
			'refer': refer,
			't': t,
			'forbidotherlogin': forbidotherlogin,
			'validate': validate,
			'doubleFactorLogin': doubleFactorLogin,
			'independentId': independentId
		},
		success: function(data){
			if(data.status){
				let url = "";
				if(isChaoxingReader()){
					let path= window.location.protocol+'//' + window.location.host ;
					url = path+_CP_+"/towriteother?name="+encodeURIComponent(data.name)+"&pwd="+encodeURIComponent(data.pwd)+"&refer="+data.url;
				}else{
					url = decodeURIComponent(data.url);
				}
				//跳转到双因子登录页面
				if (data.containTwoFactorLogin) {
					let toTwoFactorLoginPCUrl = data.twoFactorLoginPCUrl;
					location.href = toTwoFactorLoginPCUrl + "&_blank=" + _blank + "&refer=" + encodeURIComponent(url);
					return false;
				}

				if (top.location != self.location && _blank == "1") {
					top.location = url;
				} else {
					window.location = url;
				}
			} else {
				if (data.weakpwd) {
					window.location =_CP_+ "/v11/updateweakpwd?uid=" + data.uid + "&oldpwd=" + encodeURIComponent($("#pwd").val()) + "&_blank=" + $("#_blank").val() + "&refer=" + refer;
				} else {
					let msg = util.isEmpty(data.msg2) ? "登录失败" : data.msg2;
					msg = ("密码错误" == msg || "用户名或密码错误" == msg) ? "手机号或密码错误" : msg;
					util.showMsg(true,"err-txt",msg);
				}
			}
		}
	});
}

/**
 * 工具JS(多个地方使用，请勿轻易改动)
 */
var please_input_phone = "请输入手机号";
var please_input_pwd = "请输入密码";
var phone_format_error =  "手机号格式错误";
var captcha_format_error = "验证码格式错误";
var please_input_captcha = "请输入验证码";
var please_input_studentcode = "请输入学号/工号";
var out_of_limit="发送失败，超出今日短信发送上限";
var send_successful="验证码发送成功，请注意查收";
var send_fail="验证码发送失败";


var util = {
		isEmpty: function (value) {
			if (typeof value == 'undefined' || value == undefined || value == null || value === "") {
				return true;
			}
			return false;
		},
		isInterPhone:function(phone,countryCode){	//国际手机格式验证,区号86则必须11位
			var phone_pattern  = /^\d{5,11}$/;
			var phone_cn_pattern  = /^\d{11}$/;
			if(countryCode == "86"){
				return phone_cn_pattern.test(phone);
			}else{
				return phone_pattern.test(phone);
			}
		},
		notNull:function(value){
			if(util.isEmpty(value)){
				return "";
			}
			return value;
		},
		showMsg:function(flag,id,msg,isSingle){ //flag id msg必需   isSingle表示是否需要将该元素的父级边框变红
			if(!util.isEmpty(id)){
				if(flag){
					if(isSingle){
						$("#"+id).parent().addClass("error-tip");
					}
					if(msg != undefined && msg != null){
						$("#"+id).html(msg);
					}
				}else{
					if(isSingle){
						$("#"+id).parent().removeClass("error-tip");
					}
					if(msg != undefined && msg != null){
						$("#"+id).html(msg);
					}
				}
			}
		},
		checkPwd:function(pwd){ //密码要求8-16位字符，至少包含数字、字母、符号两种元素,不能包含空格和中文
			if(util.isEmpty(pwd)){
				return false;
			}
			if(pwd.length < 8 || pwd.length > 16){
				return false;
			}
			//var reg_pwd = /(?!^(\d+|[a-zA-Z]+|[!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~]+)$)^[\w!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~]{6,16}$/;
			var reg = /^(((?=.*[0-9])(?=.*[a-zA-Z])|(?=.*[0-9])(?=.*[^\s0-9a-zA-Z])|(?=.*[a-zA-Z])(?=.*[^\s0-9a-zA-Z]))[^\s\u4e00-\u9fa5]+)$/
			return reg.test(pwd);
		},
		checkPhoneCode:function(code){//验证4位验证码
			var reg_code = /^\d{4}$/;
			return reg_code.test(code);
		},
		checkEmail:function(email){	//验证邮箱
			var reg_email  = /^([a-zA-Z0-9_\.\-])+\@(([a-zA-Z0-9\-])+\.)+([a-zA-Z0-9]{2,4})+$/;
			return reg_email.test(email);
		},
		URIComponent:function(value,flag){//URL加密解密
			if(flag){
				return encodeURIComponent(value);
			}else{
				return decodeURIComponent(value);
			}
		},
		checkMobile:function(){
			var sUserAgent = navigator.userAgent.toLowerCase();
			var phoneReg = /\b(ip(hone|od)|android|opera m(ob|in)i|windows (phone|ce)|blackberry|s(ymbian|eries60|amsung)|p(laybook|alm|rofile\/midp|laystation portable)|nokia|fennec|htc[-_]|mobile|up.browser|[1-4][0-9]{2}x[1-4][0-9]{2})\b/;
			var tableReg = /\b(ipad|tablet|(Nexus 7)|up.browser|[1-4][0-9]{2}x[1-4][0-9]{2})\b/;
			return phoneReg.test(sUserAgent) || tableReg.test(sUserAgent);

		}
}

/**
 * 国家手机号Code区号公共JS，需要Jquery, 使用方式：countryCode.init() 或 countryCode.init(id1,id2,id3,id4,id5)
 * nameCodeId			code搜索文本框ID
 * codeSearchId			code搜索按钮ID
 * codeContentId		code列表所在DIV的ID
 * targetShowCodeId		选择code之后显示目标ID
 * targetSaveCodeId		选择code之后保存目标ID
 */
var countryCode = {
		init:function(nameCodeId,codeSearchId,codeContentId,targetShowCodeId,targetSaveCodeId){
			if(!util.isEmpty(nameCodeId)){
				countryCode.nameCodeId = nameCodeId;
			}
			if(!util.isEmpty(codeSearchId)){
				countryCode.codeSearchId = codeSearchId
			}
			if(!util.isEmpty(codeContentId)){
				countryCode.codeContentId = codeContentId;
			}
			if(!util.isEmpty(targetShowCodeId)){
				countryCode.targetShowCodeId = targetShowCodeId;
			}
			if(!util.isEmpty(targetSaveCodeId)){
				countryCode.targetSaveCodeId = targetSaveCodeId;
			}
			countryCode.getCountryCode();
			countryCode.lister();

		},
		nameCodeId:"nameCode",		//code搜索文本框ID
		codeSearchId:"codeSearch",  //code搜索按钮ID
		codeContentId:"codeContent",//code列表所在DIV的ID
		targetShowCodeId:"showCountryCode",	//选择编码之后展示目标ID
		targetSaveCodeId:"countryCode",	//选择编码之后保存目标ID
		getCountryCode:function(){
			var nameCode = $("#"+countryCode.nameCodeId).val();
			if(util.isEmpty(nameCode)){
				nameCode = "";
			}
			nameCode = nameCode.trim();
			$.get(_CP_+"/countryCode/getCountryCode",{'nameCode':nameCode},function(data,status){
				var browserLocale = countryCode.getCookie('browserLocale');
				var msg = "";
				if(data.status == 1){
					var codeArray = data.countryCode;
					if(codeArray != null && codeArray.length > 0){
						for (var i = 0; i < codeArray.length; i++) {
							var name = codeArray[i].zh;
							if(browserLocale == "en_US"){
								name = codeArray[i].en;
							}
							msg += ' <li data-id="'+codeArray[i].code+'" onclick="countryCode.setCountryCode('+codeArray[i].code+')"><span class="fl">'+name+'</span><span class="fr">+'+codeArray[i].code+'</span></li>';
						}
					}
				}
				$("#"+countryCode.codeContentId).html(msg);
			},"json");

		},
		setCountryCode:function(code){
			$("#"+countryCode.targetShowCodeId).html("+"+code);
			$("#"+countryCode.targetSaveCodeId).val(code);
		},
		lister:function(){
			$("#"+countryCode.nameCodeId).bind('input propertychange', function() {
				countryCode.getCountryCode();
			});
			$("#"+countryCode.codeSearchId).bind("click",function(){
				countryCode.getCountryCode();
			});
		},
		getCookie:function (c_name) {
		if (document.cookie.length > 0)     {
			c_start = document.cookie.indexOf(c_name + "=")
			if (c_start != -1){
				c_start = c_start + c_name.length + 1
				c_end = document.cookie.indexOf(";", c_start)
				if (c_end == -1)
					c_end = document.cookie.length
				return unescape(document.cookie.substring(c_start, c_end))
			}
		}
		return "";
	}
}
try {
	if(countryCode.getCookie("browserLocale") == 'en_US'){
		please_input_phone = "please input phone number";
		please_input_pwd = "please input password";
		phone_format_error = "phone format error";
		captcha_format_error = "captcha format error";
		please_input_captcha = "please input captcha";
		please_input_studentcode = 'please input Student ID/Institution ID';
		out_of_limit="Sending failed, exceeding today's SMS sending limit";
		send_successful="The verification code was sent successfully. Please check it";
		send_fail="Verification code sending failed";
	}
}catch (e) {
	console.log('请先引用util.js')
}
/**
 * 发送手机验证码
 * phoneId			手机号文本框ID
 * countrycodeId	手机区号文本框ID
 * sendBtnId		发送验证码按钮ID
 * phoneErrorId		手机号下方的提示ID(上方手机号边框变红)
 * msgId			整体页面提示ID
 * isExistPhone		是否需要判断手机号存在：true 需要判断 false 不判断，直接发送验证码 默认true
 */
var phoneCode = {
		init:function(phoneId,countrycodeId,sendBtnId,phoneErrorId,msgId,isExistPhone){
			if(!util.isEmpty(phoneId)){
				phoneCode.phoneId = phoneId;
			}
			if(!util.isEmpty(countrycodeId)){
				phoneCode.countrycodeId = countrycodeId;
			}
			if(!util.isEmpty(sendBtnId)){
				phoneCode.sendBtnId = sendBtnId;
			}
			if(!util.isEmpty(phoneErrorId)){
				phoneCode.phoneErrorId = phoneErrorId;
			}
			if(!util.isEmpty(msgId)){
				phoneCode.msgId = msgId;
			}
			if(!util.isEmpty(isExistPhone)){
				phoneCode.isExistPhone = isExistPhone;

			}
			phoneCode.lister();
		},
		phoneId:"phone",
		countrycodeId:"countryCode",
		sendBtnId:"sendCodeBtn",
		phoneErrorId:"phoneMsg",
		msgId:"msg",
		isExistPhone:true,
		getCode:function(){
			util.showMsg(false,phoneCode.phoneErrorId, "",true);
			var phone = $("#"+phoneCode.phoneId).val().trim();
			var countrycode = $("#"+phoneCode.countrycodeId).val();
			if(!util.isEmpty(phone)){
				  countrycode = util.isEmpty(countrycode) ? "86" : countrycode;
				  if(util.isInterPhone(phone)){
					  phoneCode.checkBooleanCode(phone,countrycode);
				  }else{
					  util.showMsg(true,phoneCode.phoneErrorId,phone_format_error,true);
				  }
			}else{
				util.showMsg(true,phoneCode.phoneErrorId,please_input_phone,true);
		    }
		},
		checkBooleanCode:function(phone,countrycode){	//验证短信是否超出上限
			$.ajax({
				url: _CP_+"/num/booleanCode?key="+phone+"&type=1",
				type:"post",
				success: function(data){
					if("alert"==data){
					    util.showMsg(true,phoneCode.msgId,out_of_limit);
					}else{
						if(phoneCode.isExistPhone){
							phoneCode.isPhoneExist(phone,countrycode);
						}else{
							phoneCode.getPhoneCode(phone,countrycode);
						}
					}
				}
		   });
		},
		isPhoneExist:function(phone,countrycode){
			$.ajax({
				url: _CP_+"/isPhoneExist?phone="+phone,
				type:"post",
				success: function(data){
				     if("true"==data){//手机号在平台存在
				    	 phoneCode.getPhoneCode(phone,countrycode);
					 }else{
						 util.showMsg(true,phoneCode.phoneErrorId,"手机号不存在，请先注册",true);
					 }
				}
			});
		},
		getPhoneCode:function(phone,countrycode){	//获取手机号验证码
			if(capInstance == null){
				//容错
				phoneCode.send();
			}else{
				capInstance && capInstance.popUp();
			}

		},
		lister:function(){
			$("#"+phoneCode.sendBtnId).bind('click', function() {
				phoneCode.getCode();
			});
		},
		send:function(phone,countryCode){
			var code = "";
			var needcode = false;
			var validate = $("#validate").val();
			if(undefined == validate){
				validate = "";
			}
			var fid = $("#fid").val();
			if(undefined == fid){
				fid = "0";
			}
			var phone = $("#"+phoneCode.phoneId).val().trim();
			var countrycode = $("#"+phoneCode.countrycodeId).val();
			if (typeof voiceCodeFunc != "undefined" && !util.isEmpty(voiceCodeFunc) && voiceCodeFunc.isVoiceCode) {
				voiceCodeFunc.sendVoiceCode(code,needcode,validate,fid,phone,countrycode);
			}else{
				$.ajax({
					url: _CP_+"/num/phonecode?phone="+phone+"&code="+code+"&type=1&needcode="+needcode+"&countrycode="+countrycode+"&validate="+validate+"&fid="+fid,
					type:"get",
					success: function(date){
						var myjson=eval("("+date+")");
						if (myjson.result) {
							util.showMsg(false, phoneCode.msgId, send_successful, true);
							countdownTime(); //计时器
						} else {
							var msg = util.isEmpty(myjson.msg) ? send_fail : myjson.msg;
							util.showMsg(true, phoneCode.msgId, msg);
						}
					}
				});
			}
		}
};

function enterSubmit(submitBtn){
	$("body").keydown(function (event) {
	    if (event.keyCode == 13) { //enter键键值为13
	        $("#"+submitBtn).click();
	    }
	});
}
function getTimestamp(msec) {
    msec = !msec && msec !== 0 ? msec : 1
    return parseInt((new Date()).valueOf() / msec, 10)
}

function loadScript(src, cb) {
    var head = document.head || document.getElementsByTagName('head')[0]
    var script = document.createElement('script')

    cb = cb || function () {}

    script.type = 'text/javascript'
    script.src = src

    if (!('onload' in script)) {
        script.onreadystatechange = function () {
            if (this.readyState !== 'complete' && this.readyState !== 'loaded') return
            this.onreadystatechange = null
            cb(script)
        }
    }

    script.onload = function () {
        this.onload = null
        cb(script)
    }

    head.appendChild(script)
}

function encryptByAES(message, key){
	let CBCOptions = {
		iv: CryptoJS.enc.Utf8.parse(key),
		mode:CryptoJS.mode.CBC,
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
