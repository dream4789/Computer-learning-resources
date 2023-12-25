$(function(){
	var layer, form;
	layui.use(['layer', 'form'], function(){
		layer = layui.layer;
		form = layui.form;
		
//		form.on('select(mode)', function(data){
//			if(data.value == "ECB"){
//				$("#iv").attr("disabled", true);
//			}
//		});
		var type = $("#type_value").val();
		if(type.startsWith("aes")){
			changeDigit(form, [64]);
		}else if(type.startsWith("des")){
			changeDigit(form, [128, 192, 256]);
		}
	});
	function changeDigit(form, digit){
		digit.forEach(i=>{
			$("#digit").find("option[value='"+i+"']").attr("selected", false).attr("disabled", true);
		});
		form.render();
	}
	
	var clipboard = new ClipboardJS('#copy');
	clipboard.on('success', function(e){
		layer.msg('复制成功!', {time:1000});
		return false;
	});
	
	$("#key").bind("input propertychange", function(){
		var count = $(this).val().length;
		$("#key_tip").text(count + " bytes");
	});
	$("#iv").bind("input propertychange", function(){
		var count = $(this).val().length;
		$("#iv_tip").text(count + " bytes");
	});
	
	$(".fun #clear").click(function(){
		$("#leftTxt").val("");
		$("#rightTxt").val("");
		$("#jsTxt").val("");
		$("#javaTxt").val("");
		$("#key").val("");
		$("#iv").val("");
		return false;
	});
	
	$(".fun").on("click", ".bg_handle", function(){
		var cases = $("input[name='case']:checked").val() || "lower";
		var param = {
			data : $("#leftTxt").val(),
			type : $(this).attr("id")
		};
		$.post("/utils/handle", param, function(data){
			$("#rightTxt").val((cases == "lower") ? data.result : data.result.toUpperCase());
		});
	});
	$(".fun").on("click", ".js_handle", function(){
		var val = $("#leftTxt").val();
		var result = "";
		if($(this).is("#to_upper_case")){
			result = val.toUpperCase();
		}else if($(this).is("#to_lower_case")){
			result = val.toLowerCase();
		}else if($(this).is("#to_cap_case")){
			var regex = /( |^)[a-z]/g;
			result = val.toLowerCase().replace(regex, (L) => L.toUpperCase());
		}else if($(this).is("#format")){
			result = formatAll(val);
        }else if($(this).is("#compress")){
        	result = compressAll(val);
        }else if($(this).is("#confuse")){
        	result = confuseAll(val);
        }else if($(this).is("#unconfuse")){
        	result = unconfuseAll(val);
        }
		
		$("#rightTxt").val(result);
	});
	
	$(".fun").on("click", ".jsbg_handle", function(){
		var cases = $("input[name='case']:checked").val() || "lower";
		var val = $("#leftTxt").val();
		var id = $(this).attr("id");
		var encode = $("#encode").val();
		var key = "";
		var digit = "";
		var mode = "";
		var pad = "";
		var iv = "";
		
		var result = "";
		if(id.startsWith("md5")){
			result = CryptoJS.MD5(val).toString(CryptoJS.enc.Hex);
			result = id.startsWith("md5-32") ? result : result.substring(8, 24);
			result = (encode == "Hex") ? result : CryptoJS.enc.Base64.stringify(CryptoJS.enc.Hex.parse(result));
		}else if(id.startsWith("ripemd")){
			if(id.startsWith("ripemd-160")){
				result = CryptoJS.RIPEMD160(val).toString(
						(encode == "Hex") ? CryptoJS.enc.Hex : CryptoJS.enc.Base64);
			}else{
				result = "---";
			}
		}else if(id.startsWith("sha")){//sha-1_encrypt
        	var sha = id.split("_")[0];
        	var cjAll = sha.split("-");
        	var cjM = cjAll[0].toUpperCase();
        	var cjL = cjAll[1];
        	
        	var hash = "";
    		if(sha.startsWith("sha-")){
    			hash= eval("CryptoJS." + cjM + cjL + "('" + val + "')");
    		}else if(sha.startsWith("sha3")){
    			hash = eval("CryptoJS." + cjM + "('" + val + "', {outputLength:" + cjL + "})");
    		}
    		result = hash.toString((encode == "Hex") ? CryptoJS.enc.Hex : CryptoJS.enc.Base64);
        }else if(id.startsWith("hmac")){//hmac_sha-1_encrypt
        	key = $("#key").val();
        	var all = id.split("_");
        	var sha = all[1];
        	var hmac = all[0].charAt(0).toUpperCase() + all[0].slice(1);
        	var cjAll = sha.split("-");
        	var cjM = cjAll[0].toUpperCase();
        	var cjL = cjAll[1] || "";
        	
        	var hash = "";
    		if(sha.startsWith("sha-") || sha.startsWith("md5") || sha.startsWith("ripemd-160")){
    			hash= eval("CryptoJS." + hmac + cjM + cjL + "('" + val + "', '" + key + "')");
    		}else if(sha.startsWith("sha3")){
    			hash = eval("CryptoJS." + hmac + cjM + "('" + val + "', '" + key + "')");
    		}
    		result = hash ? hash.toString((encode == "Hex") ? CryptoJS.enc.Hex : CryptoJS.enc.Base64) : "---";
        }else if(id.startsWith("aes") || id.startsWith("des") || id.startsWith("tripledes")){
        	encode = $("#encode").val();
        	key = $("#key").val();
        	digit = $("#digit").val();
        	mode = $("#mode").val();
        	pad = $("#pad").val();
        	iv = $("#iv").val();
        	
        	var crypto_key 	= CryptoJS.enc.Utf8.parse(key);
        	
        	var cfg = {};
        	(mode !== "ECB") && (cfg.iv = CryptoJS.enc.Utf8.parse(iv));
        	cfg.mode = eval("CryptoJS.mode." + mode)
        	cfg.pad = eval("CryptoJS.pad." + pad)
        	
        	var crypto = null; 
        	crypto = id.startsWith("aes") ? CryptoJS.AES : crypto;
        	crypto = id.startsWith("des") ? CryptoJS.DES : crypto;
        	crypto = id.startsWith("tripledes") ? CryptoJS.TripleDES : crypto;
        	
    		try{
    			if(id.endsWith("_encrypt")){
    				var cj = crypto.encrypt(val, crypto_key, cfg);
    				result = (encode == "Hex") ? cj.ciphertext : cj.toString();
    			}else{
            		var valByte = (encode == "Hex") ? CryptoJS.enc.Base64.stringify(CryptoJS.enc.Hex.parse(val)) : val;
            		var cj = crypto.decrypt(valByte, crypto_key, cfg);
            		result = cj.toString(CryptoJS.enc.Utf8);
            	}
    		}catch(err){
    			console.log(err);
    			result = err.message;
    		}
        	
        }
    	//AnsiX923 -> ansix923
    	//Iso10126 -> iso10126
    	//Iso97971 
    	//NoPadding -> nopadding
    	//Pkcs7 -> pkcs5padding
    	//ZeroPadding
		if(!id.startsWith("hmac_sha3")){
			if(pad == "Pkcs7") pad = "Pkcs5Padding";
			var param = {
				data : val,
				type : id
			};
			encode && (param.encode = encode);
			key && (param.key = key);
			digit && (param.digit = digit);
			mode && (param.mode = mode);
			pad && (param.pad = pad);
			iv && (param.iv = iv);
			$.post("/utils/handle", param, function(data){
				if(cases !== "lower" && (id.startsWith("md5") || id.startsWith("sha") || id.startsWith("hmac"))){
					$("#javaTxt").val(data.result.toUpperCase());
				}else{
					$("#javaTxt").val(data.result);
				}
				
			});
		}else{
			$("#javaTxt").val("---");
		}
		
		$("#jsTxt").val((cases == "lower") ? result : result.toUpperCase());
	});
	
	function formatAll(val){
    	return buildAll(val, "format");
    }
    function compressAll(val){
    	return buildAll(val, "compress");
    }
    function confuseAll(val){
    	return buildAll(val, "confuse");
    }
    function unconfuseAll(val){
    	return buildAll(val, "unconfuse");
    }
    
    function buildAll(val, fun){
    	var type = $("#type_value").val();
    	var method = type;
    	if(fun == "compress") method += "min";
    		
    	var fmtTxt = "";
    	if(type == "xml") fmtTxt=$.format(val, {method: method, step:'    '});
    	if(type == "json") fmtTxt=$.format(val, {method: method, step:'    '});
    	if(type == "sql") fmtTxt=$.format(val, {method: method, step:'    '});
    	if(type == "css") fmtTxt=$.format(val, {method: method, step:'    '});
    	if(type == "js") {
    		if(fun == "format") fmtTxt=js_beautify(val);//alert(js_beautify(val, 4, ' '));
    		if(fun == "compress") fmtTxt=jsmin(val).replace("\n", "");
    		if(fun == "confuse") {
    			var packer = new Packer;
    			fmtTxt=packer.pack(val, true, true);
    		}
    		//if(type == "unconfuse") fmtTxt=jsmin(val);
    	}
    	if(type == "html") {
    		fmtTxt = prettier.format(val, {
        	    parser: "html",
        	    plugins: prettierPlugins
        	});
    	}
    	if(type == "yaml") {
    		fmtTxt = prettier.format(val, {
        	    parser: "yaml",
        	    plugins: prettierPlugins
        	});
    	}
    	
//    		var result = UglifyJS.minify(code);
//    		var result = fuglify("function add(first, second) { return first + second; }");
    	//$.format
    	//prettier
    	return fmtTxt;
    }
});