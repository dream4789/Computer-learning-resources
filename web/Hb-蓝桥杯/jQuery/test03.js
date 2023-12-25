$(function() {
		$("input[name='q']").focus();

		var lan = "other" //浏览器语言
		switch (navigator.language.toLowerCase()) {
			case "zh-cn":
				lan = "zh-cn"
				break;
			default:
				break;
		}

		var isLoginUser = $.cookie("openid") ? true : false;
		var userAgent = navigator.userAgent;
		var isSearchEngineBot = false;
		if (!userAgent ||
			userAgent.toLowerCase().indexOf('Googlebot'.toLowerCase()) > -1 ||
			userAgent.toLowerCase().indexOf('Baiduspider'.toLowerCase()) > -1 ||
			userAgent.toLowerCase().indexOf('bingbot'.toLowerCase()) > -1 ||
			userAgent.toLowerCase().indexOf('360Spider'.toLowerCase()) > -1 ||
			userAgent.toLowerCase().indexOf('360Spider'.toLowerCase()) > -1 ||
			userAgent.toLowerCase().indexOf('spider'.toLowerCase()) > -1 ||
			userAgent.toLowerCase().indexOf('YandexBot'.toLowerCase()) > -1 ||
			userAgent.toLowerCase().indexOf('DuckDuckGo'.toLowerCase()) > -1 ||
			userAgent.toLowerCase().indexOf('AdsBot'.toLowerCase()) > -1
		) {
			isSearchEngineBot = true;
		}
		var isChineseQuestionUrl = location.href.indexOf("/stackoom.com/question/") != -1 || location.href.indexOf(
			"/stackoom.com/cn_en/question/") != -1;
		var isTWUrl = location.href.indexOf("/stackoom.com/zh/") != -1;
		if (lan == 'zh-cn' && isTWUrl && !isSearchEngineBot) {
			location.href = location.href.replace("/zh/", "/");
		}

		function showLogin(msg) {
			if ($("#loginLabel").text()) {
				$("#loginLabel").text(msg);
			} else {
				$(".container").append(
					'<div id="myModal" class="modal hide" style="max-height:500px;max-width:300px;z-index:100;">' +
					'<div class="modal-header"><button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button><h4 id="loginLabel">' +
					msg + '</h4></div><div class="modal-body">' +
					'<div><img src="https://www.codeprj.com/img/qrcode.jpg"></div>' +
					'<center>扫码->点关注公众号->自动回复“<strong>登录码</strong>”</center>' +
					'<div><B>登录码:</B><input type="text" name="loginCode" placeholder="请输入登录码登录"></div>' +
					'</div><div class="modal-footer"><button class="btn loginBtn btn-primary">登录</button></div></div>'
				);
			}
			$('#myModal').modal('show');
			$('.modal-backdrop').css("z-index", 2);
		}

		//循环添加百度广告
		function loopAddBaiduAd() {
			var baiduAdIndex = 0;
			var waitTime = 10;
			var waitAllTime = 0;
			var baiduAdInterval = setInterval(function() {
				$('.adsbygoogle').each(function() {
					if ($(this).attr("data-ad-status") == 'unfilled' && !$(this).attr(
							"baidu-ad-status") && $(this).parent().attr("class") !=
						'google-auto-placed') {
						if ($(this).css("height") == '0px') {
							$(this).css("height", "200px");
						}
						var baiduAdId = "baiduAdIndex" + baiduAdIndex;
						if ($(this).parent().attr("class") == 'googlead') {
							$(this).parent().css("height", "200px");
							$(this).parent().attr("id", baiduAdId);
							$(this).parent().html("");
						} else {
							$(this).attr("id", baiduAdId);
							$(this).attr("baidu-ad-status", "filled");
						}
						BAIDU_CLB_fillSlotAsync("u6868670", baiduAdId);
						baiduAdIndex = baiduAdIndex + 1;
					}
					waitAllTime = waitAllTime + waitTime;
					if (waitAllTime >= 30 * 1000) {
						clearInterval(baiduAdInterval);
					}
				});
			}, waitTime);
		}

		//加载百度广告js
		function loadBaiduAdJs() {
			var s = document.createElement('script'),
				h = document.getElementsByTagName('head')[0];
			s.src = "https://cpro.baidustatic.com/cpro/ui/cm.js";
			s.crossorigin = "anonymous";
			s.async = true;
			h && h.insertBefore(s, h.firstChild);
		}

		//加载谷歌广告js
		function loadGoogleAdJs() {
			var oHead = document.getElementsByTagName("head").item(0);
			var oScript = document.createElement("script");
			oScript.type = "text/javascript";
			oScript.src =
				"https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-4353345653789615";
			oScript.crossorigin = "anonymous";
			oScript.async = true;
			oHead.appendChild(oScript);
		}

		//加载广告
		function loadAd() {
			//	    loadGoogleAdJs();
			//	    loadBaiduAdJs();
			//		loopAddBaiduAd();
		}

		function hideAd() {
			$(".adsbygoogle").css("visibility", "hidden");
		}

		//   if(!isLoginUser && !isSearchEngineBot){
		if (!isLoginUser) {
			loadAd();
		} else {
			hideAd();
		}

		function login_sucess() {
			$(".top_login_info").show();
			$(".top_login_info").html("已登录(" + $.cookie("loginCode") +
				")，<a href=\"javascript:void(0)'\" class=\"navbar-link loginOutBtn\" style=\"color:grey\">退出</a>"
			);
		}

		function show_login_colors() {
			$(".top_login_info").show();
		}

		$(".container").on("click", ".btn-show-login", function() {
			var msg = "1秒登录永久去广告"
			if ($(this).attr("tip")) {
				msg = $(this).attr("tip");
			}
			showLogin(msg);
		});

		$(".container").on("click", ".loginBtn", function() {
			var loginCode = $("input[name='loginCode']").val();
			if (!loginCode) {
				alert("请输入登录码");
			} else {
				$.ajax({
					url: '/weixin/login?loginCode=' + loginCode + '&loginFrom=stackoom',
					type: 'post',
					dataType: 'json',
					async: true,
					success: function(data) {
						if (data.success) {
							$('#myModal').modal('hide');
							$.cookie("openid", data.openid, {
								expires: 365,
								path: '/'
							});
							$.cookie("loginCode", data.loginCode, {
								expires: 365,
								path: '/'
							});
							login_sucess();
							location.reload();
						} else {
							alert(data.msg);
						}
					}
				});
			}
		});

		$("body").on("click", ".loginOutBtn", function() {
			$.cookie("openid", '', {
				expires: 0,
				path: '/'
			});
			$.cookie("loginCode", '', {
				expires: 0,
				path: '/'
			});
			location.reload();
		});

		$("body").on("click", ".closeBtn", function() {
			$('#myModal').modal('hide');
		});

		function hide_answers() {
			if ($(".arc-body-main-more")) {
				$(".arc-body-main-more").show();
			}
			$(".answer").each(function() {
				$(this).append(
					'<div style="top:0;left:0;z-index:1;opacity:0.9;filter:alpha(opacity=30);position:absolute;width:100%;height:100%;background-color:white;font-weight:bold">' +
					'<div class="alert alert-info"><p style="font-size:14px;margin:0px;min-height:20px;"><strong>提示:</strong> ' +
					'您需要登录才能查看该回复，点击<a href="javascript:void(0)" class="btn-show-login" tip="1秒登录永久有效"><strong style="color:red">登录</strong></a>，只需一秒，永久有效，广告全屏蔽。</p></div></div>'
				);
			})
		}

		function show_answers() {
			if ($(".arc-body-main-more")) {
				$(".arc-body-main-more").hide();
			}
			if ($(".btn-show-login")) {
				$(".btn-show-login").hide();
			}
			if ($(".addown")) {
				$(".addown").hide();
			}
		}

		function timeout_show_login() {
			setTimeout(function() {
				showLogin("登录");
			}, 1000 * 60 * 60);
		}

		function copy_should_login() {
			$("body").bind({
				copy: function() {
					if (!$.cookie("openid")) {
						showLogin("您需要登录才能复制内容");
						return false;
					}
				},
				paste: function() {
					console.log("您执行了粘贴");
				},
				cut: function() {
					console.log("您执行了剪切");
				}
			});
		}

		if (isLoginUser) {
			show_answers();
			login_sucess();
		} else {
			if (isChineseQuestionUrl && !isSearchEngineBot) {
				show_login_colors();
				copy_should_login();
				hide_answers();
				timeout_show_login();
			}
		}

		/**
		 * 检查登陆情况
		 */
		function check_login() {
			var num = 1800;
			var openid = $.cookie("openid");
			var loginCode = $.cookie("loginCode");
			if (openid && loginCode && openid != loginCode) {
				var checkInterval = setInterval(function() {
					$.ajax({
						url: '/weixin/check_login?loginCode=' + loginCode + '&openid=' + openid +
							"&rand=" + Math.random(),
						type: 'post',
						dataType: 'json',
						async: true,
						success: function(data) {
							if (data.success) {
								console.log("登录状态正常。");
							} else {
								clearInterval(checkInterval);
								alert("您取消了公众号关注，登录状态会消失。");
								$.cookie("openid", '', {
									expires: 0,
									path: '/'
								});
								$.cookie("loginCode", '', {
									expires: 0,
									path: '/'
								});
								$.cookie("openid", '', {
									expires: 0,
									path: '/'
								});
								$.cookie("loginCode", '', {
									expires: 0,
									path: '/'
								});
								$.cookie("openid", '', {
									expires: 0,
									path: '/'
								});
								$.cookie("loginCode", '', {
									expires: 0,
									path: '/'
								});
								location.reload();
							}
						}
					});
				}, 5000);
			}
		}

		check_login();

		function timeout_next_page() {
			var urls = []
			$(".list-group-item").each(function(item, index) {
				if ($(this).attr("title") && !$(this).attr("rel")) {
					urls.push($(this).attr("href"))
				}
			})

			$(".post-item-title").each(function(item, index) {
				if ($(this).attr("href") && !$(this).attr("rel")) {
					urls.push($(this).attr("href"))
				}
			})

			$(".btn-link").each(function(item, index) {
				if ($(this).attr("href") && !$(this).attr("rel")) {
					urls.push($(this).attr("href"))
				}
			})

			var len = urls.length;
			if (len > 0) {
				var index = Math.floor(Math.random() * len);
				var num = 1800;
				var intervalProcess = setInterval(function() {
					if (num <= 0) {
						var url = urls[index]
						window.location.href = url;
						clearInterval(intervalProcess);
					}
					num--;
				}, 1000);
			} else {
				console.log("no urls");
			}
		}
	})
	(function() {
		function buffer(a, b, c) {
			var d;
			return function() {
				if (d) return;
				d = setTimeout(function() {
						a.call(this),
							d = undefined
					},
					b)
			}
		}

		function e() {
			var d = document.body.scrollTop || document.documentElement.scrollTop;
			d > b ? (a.className = "div1 div2", c && (a.style.top = d - b + "px")) : a.className = "div1"
		}
		var a = document.getElementById("float");
		if (a == undefined) return !1;
		var b = 0,
			c, d = a;
		while (d) b += d.offsetTop,
			d = d.offsetParent;
		c = window.ActiveXObject && !window.XMLHttpRequest;
		if (!c || !0) window.onscroll = buffer(e, 50, this)
	})();

$(document).ready(function() {
	var show_delay = 90;
	var hide_delay = 200;
	var show_effect = true;

	$("b").each(function() {
		$(this).hover(function() { //变色选中	
			$(this).addClass('sen_hover');
		}, function() {
			$(this).removeClass('sen_hover');
		});

		var preI = $(this).prev();
		if (preI && (preI.prop('nodeName') == 'i' || preI.prop('nodeName') == 'I')) {
			var content = preI.html();
			content = content.replace("<!--", "").replace("-->", "");
			$(this).qtip({
				content: {
					text: content
				},
				position: {
					my: 'bottom center',
					at: 'top center',
					adjust: {
						x: 30,
						y: -25
					}
				},
				show: {
					delay: show_delay,
					effect: show_effect
				},
				hide: {
					delay: hide_delay,
					fixed: true
				}
			});
		}
	});

	$("i").each(function() {
		$(this).hover(function() { //变色选中	
			$(this).addClass('sen_hover');
		}, function() {
			$(this).removeClass('sen_hover');
		});

		var nextB = $(this).next();
		if (nextB && (nextB.prop('nodeName') == 'b' || nextB.prop('nodeName') == 'B')) {
			var content = nextB.html();
			content = content.replace("<!--", "").replace("-->", "");
			$(this).qtip({
				content: {
					text: content
				},
				position: {
					my: 'bottom center',
					at: 'top center',
					adjust: {
						x: 30,
						y: -25
					}
				},
				show: {
					delay: show_delay,
					effect: show_effect
				},
				hide: {
					delay: hide_delay,
					fixed: true
				}
			});
		}
	});

});

// 右下角滚动回顶部代码
! function() {
	function o() {
		var o = $(window).scrollTop();
		o >= a ? s.gotopShow() : s.gotopHide()
	}

	function t() {
		var o = !0;
		$(window).on("touchstart",
				function(t) {
					o = !1;
					var e = t.originalEvent.touches,
						n = e[0].screenY;
					$(this).on("touchmove",
						function(o) {
							var t = o.originalEvent.touches,
								e = t[0].screenY,
								i = e - n,
								a = $(window).scrollTop();
							a > 0 ? (i < -10 && s.gotopHide(), i > 10 && s.gotopShow()) : s.gotopHide()
						}).one("touchend",
						function() {
							$(this).off("touchmove touchend"),
								o = !0
						})
				}),
			$(window).on("scroll",
				function() {
					if (o) {
						var t = $(window).scrollTop();
						0 === t && s.gotopHide()
					}
				})
	}
	var e = {
		parentBox: $("body"),
		right: 8,
		bottom: 40,
		zindex: 110,
		hasReport: !1,
		reportFun: null,
		isMobile: !1,
		hasFreeAd: !0,
		vipDiscount: !1
	};
	/Android|webOS|iPhone|iPod|BlackBerry/i.test(window.navigator.userAgent) ? e.hasFreeAd = !1 : e.hasFreeAd = !0;
	var s = $(
			'<div class="meau-gotop-box"><a href="#" id="backtop" class="btn-meau" title="返回顶部"><svg xmlns="http://www.w3.org/2000/svg" width="19" height="12"><path d="M9.314 0l9.313 9.314-2.12 2.121-7.193-7.192-7.193 7.192L0 9.314z" fill="#FFF" fill-rule="evenodd" /></svg></a></div>'
			),
		a = $(window).height();
	s.gotopShow = function() {
			$(this).find("a#backtop").fadeIn(200).css("display", "flex")
		},
		s.gotopHide = function() {
			$(this).find("a#backtop").fadeOut(200)
		},
		s.find("a#backtop").click(function(o) {
			o.preventDefault(),
				$("html,body").animate({
						scrollTop: 0
					},
					200),
				e.isMobile && s.gotopHide()
		});
	var r = function(i) {
		var path = $("input[name='path']").val();
		if (n = !0, void 0 !== i && "object" == typeof i && $.extend(e, i), e.hasReport)
			if (null === e.reportFun) console.warn("请设置内容举报方法");
			else {
				var r = $(
					'<a href="/about.html" class="btn-meau" title="关于本站"><svg xmlns="http://www.w3.org/2000/svg" width="18" height="22"><path d="M0 13.028V3.365L9 0l9 3.365v9.663C18 17.983 13.97 22 9 22s-9-4.017-9-8.972zm2-8.282v8.282c0 3.854 3.134 6.978 7 6.978s7-3.124 7-6.978V4.746L9 2.13 2 4.746zm6 10.276h2v1.993H8v-1.993zm0-8.973h2v6.979H8V6.049z" fill="#FFF" fill-rule="nonzero"/></svg></a>'
					);
				s.append(r)
				// r.click(function(o) {
				// o.preventDefault(),
				// e.reportFun()
				// })
			}
		if (e.hasFreeAd) {
			// var d = $('<a href="'+path+'/help/buyvip.html" id="adContent"
			// class="btn-meau"></a>');
			// s.prepend(d)
		}
		e.isMobile && s.addClass("wap"),
			e.parentBox.append(s),
			s.css({
				right: e.right + "px",
				bottom: e.bottom + "px",
				"z-index": e.zindex
			}),
			e.isMobile ? t() : ($(window).resize(function() {
				a = $(window).height(),
					o()
			}), $(window).scroll(o))
	};
	window.GoTop = r,
		setTimeout(function() {
				n || r()
			},
			200)
}();

GoTop({
	right: 8,
	hasReport: true,
	reportFun: function() {
		showReport(false, articleTit);
	}
});
