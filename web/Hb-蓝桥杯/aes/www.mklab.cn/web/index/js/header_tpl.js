function changeURLPar(destiny,par,par_value){var pattern=par+"=([^&]*)";var replaceText=par+"="+par_value;if(destiny.match(pattern)){var tmp="/\\"+par+"=[^&]*/";tmp=destiny.replace(eval(tmp),replaceText);return(tmp)}else{if(destiny.match("[?]")){return destiny+"&"+replaceText}else{return destiny+"?"+replaceText}}return destiny+"\n"+par+"\n"+par_value}function getLang(){var a=navigator.language.substring(0,2).toLowerCase();switch(a){case"en":return"en-US";break;case"zh":return"zh-CN";break;default:return"zh-CN"}}$(function(){var a=$.cookie("_i18n");$("#lang").val($.isEmptyObject(a)?getLang():a);$("#lang").change(function(b){location.href=changeURLPar(location.href,"_lang",$(this).val())})});