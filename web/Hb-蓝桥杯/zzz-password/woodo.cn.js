/* WEBPACK VAR INJECTION */
(function($) {
	/* harmony import */
	var __WEBPACK_IMPORTED_MODULE_0__assets_common_js_zIndex_js__ = __webpack_require__(18);

	/* harmony default export */
	__webpack_exports__["a"] = ({
		name: 'LoginModal',
		data: function data() {
			return {
				zIndex: Object(__WEBPACK_IMPORTED_MODULE_0__assets_common_js_zIndex_js__[
					"a" /* default */ ])(),
				user: null,
				show_modal: false, // 展示标识
				login_type: 'qrcode', // 打开登录还是注册面板
				modal_class: 'component', // 弹框样式 (组件还是页面)
				/** 微信扫码登录相关data */
				show_wxLogin: false, //是否显示微信扫码组件
				weixin_qrcode_expire: true, //是否已过期，默认已过期
				weixin_qrcode_expire_time: 300, //5分钟过期
				weixin_qrcode_expire_timeer: "", //微信二维码过期定时器，时刻检测过期
				weixin_qrcode_timeer: "", //微信二维码登录定时器，时刻检测登录
				wechat_img: "", // 公众号二维码
				ewm_expired: false, // 二维码过期
				user_email: "",
				poling_code: "",

				/*输入校验相关*/
				valid_text: null, // 错误提示内容
				valid_detail_text: {
					email: null,
					phone: null,
					code: null,
					pwd: null,
					repeat_pwd: null,
					nick_name: null,
					invitation_code: null
				}, // 详细的错误提示内容
				test_email: {
					error: false,
					success: false
				}, // 邮箱校验结果
				test_code: {
					error: false,
					success: false
				}, // 验证码校验结果
				test_phone: {
					error: false,
					success: false
				}, // 手机校验结果
				test_nick_name: {
					error: false,
					success: false
				}, // 昵称校验结果
				test_invitation_code: {
					error: false,
					success: false
				}, // 邀请码校验结果
				test_pwd: {
					error: false,
					success: false
				}, // 密码校验结果
				test_repeat_pwd: {
					error: false,
					success: false
				}, // 确认密码校验结果
				test_bind_account: {
					error: false,
					success: false
				}, // 手机号或者邮箱校验结果
				code_text: '获取验证码', // 验证码按钮文本
				can_get_code: true, // 获取验证码状态
				countdown: 60, // 发送验证码倒计时

				valid_msg_show: false,
				mid: "SMS_150742979", // 手机模版id（找回密码）
				sign_up_mid: 'SMS_150738151', // 手机模板id（手机注册）
				bind_mid: "SMS_150742973", // 绑定账号mid
				// 验证码倒计时
				code_interval: null,
				account: '', // 输入的手机号或邮箱
				invitationCode: '', // 邀请码
				has_password: false,
				remember_pwd: false, // 是否记住密码
				show_password: false, // 展示密码标识
				toast_content: null, // toast提示内容
				toast_show: false // 展示toast提示标识
			};
		},

		watch: {
			login_type: function login_type() {
				this.$nextTick(function() {
					$('input').val('');
				});
			},

			account: {
				handler: function handler(n, o) {
					if (n && typeof n === 'string') {
						this.account = n.replace(/\s/g, '');
					}
				}
			}
		},
		mounted: function mounted() {},

		methods: {
			// 打开登录弹框
			open: function open(opt) {
				var that = this;
				var body = document.body || window.document.body;
				var option = {
					type: 'qrcode',
					className: 'component'
				};
				option = Object.assign(option, opt);
				that.login_type = option.type;
				that.modal_class = option.className;
				that.show_modal = true;
				that.change_login_type(that.login_type);
				that.modal_class === 'component' && $(body).css('overflow', 'hidden');
			},

			// 关闭弹框
			close: function close() {
				var body = document.body || window.document.body;
				this.show_modal = false;
				this.modal_class === 'component' && $(body).css('overflow', 'auto');
				if (this.login_type === 'bind_wechat' || this.login_type === 'bind_account') this.$emit(
					'success_callback');
				// 清除定时器 
				clearInterval(this.weixin_qrcode_expire_timeer);
				clearInterval(this.weixin_qrcode_timeer);
				clearInterval(this.code_interval);
			},

			// 获取用户个人信息
			get_user_info: function get_user_info() {
				var that = this;
				that.user = that.$common.get_login_state();
				var no_email = $validate(that.user.email).empty(),
					no_phone = $validate(that.user.mobile).empty();
				// 未设置密码
				if (!no_email && !no_phone) that.has_password = true;
			},

			// 清除空格
			remove_space: function remove_space(e, key) {
				var value = e.target.value;
				var nowrap_value = void 0;
				if (typeof value === 'string' && value.includes(' ')) {
					nowrap_value = value.replace(/\s/g, '');
					this.$refs[key].value = nowrap_value;
				}
			},

			/*------------------- wechat start -------------------*/

			// 设置小程序码链接
			get_wxlogin_msg: function get_wxlogin_msg(type) {
				var that = this;
				var sceneType = type === 'bind_wechat' ? 'binding' : 'login';
				that.$axios.get("/api/weixin/app/create_app_code/", {
					params: {
						sceneType: sceneType
					}
				}).then(function(data) {
					that.wechat_img = "data:image/png;base64," + data.data.data.image;
					that.weixin_qrcode_expire = false;
					that.weixin_qrcode_expire_time = 300;
					that.show_wxLogin = true;
					that.ewm_expired = false;
					that.poling_code = data.data.data.polingCode;
					that.wechat_timmer_start();
				});
			},

			// 微信扫码检测
			weixin_login_check: function weixin_login_check() {
				var that = this;
				var sceneType = that.login_type === 'bind_wechat' ? 'binding' : 'login';
				that.$axios.get("/api/weixin/app/check_scan/", {
					params: {
						polingCode: that.poling_code,
						sceneType: sceneType
					}
				}).then(function(data) {
					if (data.data.code === "2") {
						var toast_content = that.login_type === 'bind_wechat' ? '绑定成功' : '登录成功';
						that.get_user_info();
						that.$toast(toast_content, 2000);
						that.$emit('get_user_info');
						// 清除定时器 
						clearInterval(that.weixin_qrcode_expire_timeer);
						clearInterval(that.weixin_qrcode_timeer);
						// toast延时
						setTimeout(function() {
							that.close();
							that.$emit('success_callback');
						}, 500);
					} else if (data.data.code === '3') {
						// 清除定时器 
						clearInterval(that.weixin_qrcode_expire_timeer);
						clearInterval(that.weixin_qrcode_timeer);
						that.ewm_expired = true;
						that.$toast(data.data.content, 2000);
					}
				});
			},

			// 二维码刷新
			refresh_wexin_qrcode: function refresh_wexin_qrcode() {
				var that = this;
				// 重新获取微信登录二维码
				that.get_wxlogin_msg(that.login_type);
				// 启动定时器
				that.wechat_timmer_start();
			},
			wechat_timmer_start: function wechat_timmer_start() {
				var that = this;
				// 清除定时器 
				clearInterval(that.weixin_qrcode_expire_timeer);
				clearInterval(that.weixin_qrcode_timeer);
				// 启动扫描登录检测定时器
				that.weixin_qrcode_expire_timeer = setInterval(that.weixin_login_check, 1500);
				// 二维过期定时器，5分钟过期
				that.weixin_qrcode_timeer = setInterval(function() {
					that.weixin_qrcode_expire_time--;
					if (that.weixin_qrcode_expire_time <= 0) {
						// 清除定时器 
						clearInterval(that.weixin_qrcode_expire_timeer);
						clearInterval(that.weixin_qrcode_timeer);
						that.ewm_expired = true;
					}
				}, 1000);
			},


			/*------------------- wechat end -------------------*/

			// 切换登录方式
			change_login_type: function change_login_type(type) {
				var _this = this;

				var that = this;
				// 清除定时器 
				clearInterval(that.weixin_qrcode_expire_timeer);
				clearInterval(that.weixin_qrcode_timeer);
				clearInterval(that.code_interval);
				that.$emit('type_change', type);
				// 初始化状态
				that.countdown = 60;
				that.wechat_img = null;
				that.valid_text = null;
				that.account = null;
				that.invitationCode = '';
				that.valid_detail_text = {
					email: null,
					phone: null,
					code: null,
					pwd: null,
					repeat_pwd: null,
					nick_name: null,
					invitation_code: null
				}, that.test_email = {
					error: false,
					success: false
				};
				that.test_code = {
					error: false,
					success: false
				};
				that.test_phone = {
					error: false,
					success: false
				};
				that.test_nick_name = {
					error: false,
					success: false
				};
				that.test_pwd = {
					error: false,
					success: false
				};
				that.test_repeat_pwd = {
					error: false,
					success: false
				};
				that.test_bind_account = {
					error: false,
					success: false
				};
				that.test_invitation_code = {
					error: false,
					success: false
				};
				that.can_get_code = true;
				that.code_text = '获取验证码';
				that.login_type = type;
				// 切换到二维码登录页后才进行轮询
				if (['wechat', 'qrcode', 'bind_wechat'].indexOf(type) >= 0) that.get_wxlogin_msg(type);
				if (type === 'bind_account') that.get_user_info();
				if (type === 'account') {
					that.$nextTick(function() {
						setTimeout(function() {
							that.get_cookies();
						}, 30);
					});
				}
				// 切换时清除表单数据，防止表单数据乱套
				$('.center_main input').each(function() {
					$(_this).val(null);
				});
			},

			// 校验昵称是否可用
			useful_nick_name: function useful_nick_name(name, callback) {
				var that = this,
					result = void 0;
				that.$axios.get("/api/register/check_nickName/", {
					params: {
						nickName: name
					}
				}).then(function(data) {
					if (data.data.code === '2') {
						result = true;
					} else {
						result = false;
					}
					if (typeof callback === 'function') {
						callback(result);
					}
				});
			},

			// 校验邮箱是否可用
			useful_email: function useful_email(email, callback) {
				var that = this,
					result = void 0,
					content = void 0;
				that.$axios.get("/api/register/check_email/", {
					params: {
						email: email
					}
				}).then(function(data) {
					if (data.data.code === '2') {
						result = true;
						content = '';
					} else {
						result = false;
						content = data.data.content;
					}
					if (typeof callback === 'function') {
						callback(result, content);
					}
				});
			},

			// 校验手机是否可用
			useful_phone: function useful_phone(phone, callback) {
				var that = this,
					result = void 0,
					tips = void 0;
				that.$axios.get("/api/register/check_mobile/", {
					params: {
						mobile: phone
					}
				}).then(function(data) {
					var code = data.data.code;
					if (typeof callback === 'function') {
						callback(code);
					}
				});
			},


			/*帐号登录*/
			username_submit_event: function username_submit_event() {
				var that = this,
					password = that.$refs.password.value,
					username = that.$refs.username.value.replace(/\s/g, '');
				that.valid_text = '';
				if ($validate(password).empty() || $validate(username).empty()) {
					that.valid_text = '请输入登录账号和密码';
					return false;
				}
				$(".accounts .submit button").prop("disabled", true);
				that.$axios.get("/api/common/public_key/").then(function(data) {
					var RsaKey = that.$rsa,
						Base64 = that.$base64,
						rsakey = new RsaKey(),
						base64 = new Base64(),
						modulus = data.data.modulus,
						exponent = data.data.exponent;
					rsakey.setPublic(base64.b64tohex(modulus), base64.b64tohex(exponent));
					var enPassword = base64.hex2b64(rsakey.encrypt(password));
					that.$axios.post("/api/login/submit/", {
						username: username,
						enPassword: enPassword
					}).then(function(data) {
						if (data.data.code === '2') {
							that.$toast("登录成功", 2000);
							that.get_user_info();
							that.$emit('get_user_info');
							that.valid_text = null;
							if (that.remember_pwd) {
								that.set_cookies();
							} else {
								that.delete_cookies();
							}
							setTimeout(function() {
								// 判断是否绑定微信
								var user = that.$common.get_login_state();
								if (user.BindWeixin) {
									that.close();
									that.$emit('success_callback');
								} else {
									that.change_login_type('bind_wechat');
								}
							}, 300);
						} else if (data.data.code === '3') {
							that.valid_text = data.data.content;
							var error_count = 5 - Number(data.data
							.data); // data是当前次数，剩余次数显示需要+1
							if (error_count <= 3 && error_count >= 0) {
								that.valid_text = '用户名或密码错误，再输入' + error_count +
									'次将锁定该账号';
							}
							if (error_count <= 0) {
								that.valid_text = '用户名或密码错误，账号已被锁定，24小时后解除';
							}
						} else {
							that.valid_text = data.data.content;
						}
						$(".accounts .submit button").prop("disabled", false);
					});
				});
			},

			/* 记住密码功能 */
			toggle_remember_pwd: function toggle_remember_pwd() {
				this.remember_pwd = !this.remember_pwd;
			},

			// 设置cookies
			set_cookies: function set_cookies() {
				var that = this;
				var account = that.$refs.username.value.replace(/\s/g, '');
				var pwd = that.$refs.password.value;
				// 存储cookie时插入盐值
				var salt_value = '500dwoodo';
				pwd = salt_value + pwd;
				pwd = window.btoa(pwd);
				utils.setCookies('woodo_remember_pwd', true);
				utils.setCookies('woodo_account', account);
				utils.setCookies('woodo_pwd', pwd);
			},

			// 获取cookies
			get_cookies: function get_cookies() {
				var that = this;
				if (!utils.getCookies('woodo_remember_pwd')) return false;
				that.remember_pwd = true;
				var account = utils.getCookies('woodo_account');
				var pwd = utils.getCookies('woodo_pwd');
				var salt_value = '500dwoodo';
				pwd = window.atob(pwd).replace(salt_value, '');
				$('.username_field input').val(account);
				$('.pwd_field input').val(pwd);
			},

			// 删除cookies
			delete_cookies: function delete_cookies() {
				utils.deleteCookies('woodo_remember_pwd');
				utils.deleteCookies('woodo_account');
				utils.deleteCookies('woodo_pwd');
			},

			/*邮箱注册*/
			// 邮箱校验
			validate_email: function validate_email() {
				var that = this,
					email = that.account;
				if (!email) {
					that.valid_detail_text.email = null;
					that.test_email = {
						error: false,
						success: false
					};
					return false;
				}
				if (!$validate(email).email()) {
					that.valid_detail_text.email = "格式错误";
					that.test_email = {
						error: true,
						success: false
					};
					return false;
				}
				that.useful_email(email, function(result, content) {
					if (that.login_type === 'email' && !result) {
						that.valid_detail_text.email = content;
						that.test_email = {
							error: true,
							success: false
						};
					} else if (that.login_type === 'email_pwd' && result) {
						that.valid_detail_text.email = '该邮箱号未注册，请检查后输入';
						that.test_email = {
							error: true,
							success: false
						};
					} else {
						that.valid_detail_text.email = null;
						that.test_email = {
							error: false,
							success: true
						};
					}
				});
			},

			// 获取邮箱验证码
			get_email_code: function get_email_code() {
				var that = this,
					type = that.login_type,
					email = that.account,
					mid = null,
					en_email = void 0;
				if (type === 'email') {
					mid = that.sign_up_mid;
				} else {
					mid = type === 'bind_account' ? that.bind_mid : that.mid;
				}
				if (!that.can_get_code) return false;
				if (that.test_email.error) return false;
				if (that.login_type === 'bind_account' && !that.test_bind_account.success) return false;
				that.$axios.get("/api/common/public_key/", {
					params: {
						email: email
					}
				}).then(function(data) {
					var RsaKey = that.$rsa,
						Base64 = that.$base64,
						rsakey = new RsaKey(),
						base64 = new Base64(),
						modulus = data.data.modulus,
						exponent = data.data.exponent;
					rsakey.setPublic(base64.b64tohex(modulus), base64.b64tohex(exponent));
					en_email = base64.hex2b64(rsakey.encrypt(email));
					that.$axios.post("/api/common/get_email_msg_code", {
						email: email,
						mid: mid,
						enEmail: en_email,
						modulus: modulus,
						exponent: exponent
					}).then(function(data) {
						if (data.data.code === '2') {
							that.show_toast('验证码已发送，注意邮箱通知~');
							that.can_get_code = false;
							that.code_text = '重新发送' + that.countdown;
							that.code_interval = setInterval(function() {
								if (that.countdown <= 0) {
									clearInterval(that.code_interval);
									that.code_text = '获取验证码';
									that.countdown = 60;
									that.can_get_code = true;
								} else {
									that.countdown += -1;
									that.code_text = '重新发送' + that.countdown;
								}
							}, 1000);
						} else {
							that.show_toast(data.data.content);
						}
					});
				});
			},

			// 密码校验
			validate_password: function validate_password(e) {
				var that = this,
					pwd = e.target.value,
					pwd_reg = /^(\w){6,20}$/;
				if (pwd === '') {
					that.valid_detail_text.pwd = null;
					that.test_pwd = {
						error: false,
						success: false
					};
					return false;
				}
				if (pwd.length < 6 || pwd.length > 20) {
					that.valid_detail_text.pwd = '请输入6-20个字符的密码';
					that.test_pwd = {
						error: true,
						success: false
					};
					return false;
				}
				if (!pwd_reg.test(pwd)) {
					that.valid_detail_text.pwd = '只能输入6-20个字母、数字、下划线';
					that.test_pwd = {
						error: true,
						success: false
					};
					return false;
				}
				if (that.login_type !== 'bind_account' && pwd === that.$refs.repeat_pwd.value && that
					.$refs.repeat_pwd.value) {
					that.valid_detail_text.repeat_pwd = null;
					that.test_repeat_pwd = {
						error: false,
						success: true
					};
				}
				that.valid_detail_text.pwd = null;
				that.test_pwd = {
					error: false,
					success: true
				};
			},

			// 昵称校验
			validate_nickname: function validate_nickname(e) {
				var that = this,
					name = e.target.value,
					str_reg = /^[a-zA-Z0-9_\-\u4e00-\u9fa5]+$/;
				if (name === '') {
					that.valid_detail_text.nick_name = null;
					that.test_nick_name = {
						error: false,
						success: false
					};
					return false;
				}
				if (name.length > 6) {
					that.valid_detail_text.nick_name = '不能超过6个字符哦~';
					that.test_nick_name = {
						error: true,
						success: false
					};
					return false;
				}
				if (!str_reg.test(name)) {
					that.valid_detail_text.nick_name = '昵称不能含有特殊字符！';
					that.test_nick_name = {
						error: true,
						success: false
					};
					return false;
				}
				that.useful_nick_name(name, function(result) {
					if (result) {
						that.valid_detail_text.nick_name = null;
						that.test_nick_name = {
							error: false,
							success: true
						};
					} else {
						that.valid_detail_text.nick_name = '该昵称已被占用';
						that.test_nick_name = {
							error: true,
							success: false
						};
					}
				});
			},

			// 校验邀请码是否过期
			validateInvitationCode: function validateInvitationCode() {
				var that = this;
				var inviteCode = that.invitationCode;
				return new Promise(function(resolve) {
					// 判断是否有邀请码 有的话验证邀请码后再注册 否则直接注册
					if (inviteCode) {
						that.$axios({
							url: '/api/register/check_invite_code/',
							params: {
								inviteCode: inviteCode
							}
						}).then(function(res) {
							var code = res.data.code;

							if (code === '2') {
								resolve(inviteCode);
							} else {
								that.test_invitation_code.error = true;
								that.valid_detail_text.invitation_code =
									'\u9080\u8BF7\u7801\u65E0\u6548\uFF01\u8BF7\u91CD\u65B0\u83B7\u53D6';
							}
						});
					} else {
						resolve();
					}
				});
			},

			// 邮箱注册提交事件
			email_register: function email_register() {
				var that = this,
					email = that.$refs.email.value,
					code = that.$refs.code.value,
					password = that.$refs.password.value,
					nick_name = that.$refs.nick_name.value;
				if (!that.test_email.error && !that.test_email.success) {
					that.test_email.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				if (!that.test_nick_name.error && !that.test_nick_name.success) {
					that.test_nick_name.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				if (!that.test_pwd.error && !that.test_pwd.success) {
					that.test_pwd.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				if (!that.test_repeat_pwd.error && !that.test_repeat_pwd.success) {
					that.test_repeat_pwd.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				if (!that.test_code.error && !that.test_code.success) {
					that.test_code.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				$(".submit button").prop("disabled", true);
				that.validateInvitationCode().then(function(invitationCode) {
					that.$axios.get("/api/common/public_key/").then(function(data) {
						var RsaKey = that.$rsa,
							Base64 = that.$base64,
							rsakey = new RsaKey(),
							base64 = new Base64(),
							modulus = data.data.modulus,
							exponent = data.data.exponent;
						rsakey.setPublic(base64.b64tohex(modulus), base64.b64tohex(
							exponent));
						var enPassword = base64.hex2b64(rsakey.encrypt(password));
						var registerParams = {
							code: code,
							nickName: nick_name,
							email: email,
							enPassword: enPassword,
							mid: that.sign_up_mid
						};
						if (invitationCode) {
							registerParams.inviteCode = invitationCode;
						}
						that.$axios.post("/api/register/submit/", registerParams).then(
							function(data) {
								if (data.data.code === '2') {
									that.show_toast("注册成功~");
									that.get_user_info();
									that.$emit('get_user_info');
									// 判断是否绑定微信
									var user = that.user;
									if (user.BindWeixin) {
										that.close();
										that.$emit('success_callback');
									} else {
										that.change_login_type('bind_wechat');
									}
								} else {
									var content = data.data.content;
									that.valid_text = content;
									switch (true) {
										case content.indexOf('验证码') >= 0:
											that.test_code = {
												error: true,
												success: false
											};
											break;
										case content.indexOf('邮箱') >= 0:
											that.test_email = {
												error: true,
												success: false
											};
											break;
										case content.indexOf('密码') >= 0:
											that.test_pwd = {
												error: true,
												success: false
											};
											break;
										case content.indexOf('昵称') >= 0:
											that.test_nick_name = {
												error: true,
												success: false
											};
											break;
									}
								}
								$(".submit button").prop("disabled", false);
							});
					});
				});
			},


			/*------------------- 手机注册 -------------------*/

			// 手机校验
			validate_phone: function validate_phone(get_code) {
				var that = this,
					phone = that.account;
				if (!phone) {
					that.valid_detail_text.phone = null;
					that.test_phone = {
						error: false,
						success: false
					};
					return false;
				}
				if (!$validate(phone).phone()) {
					that.valid_detail_text.phone = "格式错误";
					that.test_phone = {
						error: true,
						success: false
					};
					return false;
				}
				that.useful_phone(phone, function(code) {
					if (that.login_type === 'phone' && code !== '2') {
						if (code === '3') {
							that.valid_detail_text.phone = '该手机已被注册，请直接登录';
							that.test_phone = {
								error: true,
								success: false
							};
						} else {
							that.valid_detail_text.phone = '该号码格式暂不支持，请更换后继续';
							that.test_phone = {
								error: true,
								success: false
							};
						}
					} else if (that.login_type === 'phone_pwd' && code === '2') {
						that.valid_detail_text.phone = '该手机未注册，请检查后输入';
						that.test_phone = {
							error: true,
							success: false
						};
					} else {
						that.valid_detail_text.phone = null;
						that.test_phone = {
							error: false,
							success: true
						};
						if (get_code) that.get_phone_code;
					}
				});
			},

			// 获取手机验证码
			get_phone_code: function get_phone_code() {
				var that = this,
					type = that.login_type,
					phone = that.account,
					mid = null,
					en_phone = void 0;
				if (type === 'phone') {
					mid = that.sign_up_mid;
				} else {
					mid = type === 'bind_account' ? that.bind_mid : that.mid;
				}
				if (!that.can_get_code) return false;
				if (that.test_phone.error) return false;
				if (that.login_type === 'bind_account' && !that.test_bind_account.success) return false;
				that.$axios.get("/api/common/public_key/").then(function(data) {
					var RsaKey = that.$rsa,
						Base64 = that.$base64,
						rsakey = new RsaKey(),
						base64 = new Base64(),
						modulus = data.data.modulus,
						exponent = data.data.exponent;
					rsakey.setPublic(base64.b64tohex(modulus), base64.b64tohex(exponent));
					en_phone = base64.hex2b64(rsakey.encrypt(phone));
					that.$axios.post('/api/common/get_mobile_msg_code/', {
						mobile: phone,
						mid: mid,
						enMobile: en_phone
					}).then(function(data) {
						if (data.data.code === '2') {
							that.show_toast('验证码已发送，注意短信通知~');
							that.can_get_code = false;
							that.code_text = '重新发送' + that.countdown;
							that.code_interval = setInterval(function() {
								if (that.countdown <= 0) {
									clearInterval(that.code_interval);
									that.can_get_code = true;
									that.code_text = '获取验证码';
									that.countdown = 60;
								} else {
									that.countdown += -1;
									that.code_text = '重新发送' + that.countdown;
								}
							}, 1000);
						} else {
							that.show_toast(data.data.content);
						}
					});
				});
			},

			// 手机注册提交事件
			phone_register: function phone_register() {
				var that = this,
					mobile = that.$refs.phone.value,
					code = that.$refs.phone_code.value,
					password = that.$refs.password.value,
					nick_name = that.$refs.nick_name.value;
				if (!that.test_phone.error && !that.test_phone.success) {
					that.test_phone.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				if (!that.test_nick_name.error && !that.test_nick_name.success) {
					that.test_nick_name.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				if (!that.test_pwd.error && !that.test_pwd.success) {
					that.test_pwd.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				if (!that.test_code.error && !that.test_code.success) {
					that.test_code.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				if (!that.test_repeat_pwd.error && !that.test_repeat_pwd.success) {
					that.test_repeat_pwd.error = true;
					that.valid_text = "请完善注册内容";
					return false;
				}
				$(".submit button").prop("disabled", true);
				that.validateInvitationCode().then(function(invitationCode) {
					that.$axios.get("/api/common/public_key/").then(function(data) {
						var RsaKey = that.$rsa,
							Base64 = that.$base64,
							rsakey = new RsaKey(),
							base64 = new Base64(),
							modulus = data.data.modulus,
							exponent = data.data.exponent;
						rsakey.setPublic(base64.b64tohex(modulus), base64.b64tohex(
							exponent));
						var enPassword = base64.hex2b64(rsakey.encrypt(password));
						var registerParams = {
							mid: that.sign_up_mid,
							code: code,
							mobile: mobile,
							nickName: nick_name,
							enPassword: enPassword
						};
						if (invitationCode) {
							registerParams.inviteCode = invitationCode;
						}
						that.$axios.post("/api/register/mobile_submit/", registerParams)
							.then(function(data) {
								if (data.data.code === '2') {
									that.show_toast("注册成功~");
									that.get_user_info();
									that.$emit('get_user_info');
									// 判断是否绑定微信
									var user = that.user;
									if (user.BindWeixin) {
										that.close();
										that.$emit('success_callback');
									} else {
										that.change_login_type('bind_wechat');
									}
								} else {
									var content = data.data.content;
									that.valid_text = content;
									switch (true) {
										case content.indexOf('验证码') >= 0:
											that.test_code = {
												error: true,
												success: false
											};
											break;
										case content.indexOf('手机') >= 0:
											that.test_phone = {
												error: true,
												success: false
											};
											break;
										case content.indexOf('密码') >= 0:
											that.test_pwd = {
												error: true,
												success: false
											};
											break;
										case content.indexOf('昵称') >= 0:
											that.test_nick_name = {
												error: true,
												success: false
											};
											break;
									}
								}
								$(".submit button").prop("disabled", false);
							});
					});
				});
			},


			/*------------------- 找回密码 -------------------*/

			// 确认密码校验
			validate_repeat_pwd: function validate_repeat_pwd(e) {
				var that = this,
					password = that.$refs.password.value,
					repeat_password = e.target.value;
				// 判断密码输入错误 -> 返回
				if (that.test_pwd.error) return false;
				if (!password) {
					that.valid_detail_text.repeat_pwd = null;
					that.test_repeat_pwd = {
						error: false,
						success: false
					};
					return false;
				}
				if (password !== repeat_password) {
					that.valid_detail_text.repeat_pwd = '两次输入密码不一致';
					that.test_repeat_pwd = {
						error: true,
						success: false
					};
					return false;
				}
				that.valid_detail_text.repeat_pwd = null;
				that.test_repeat_pwd = {
					error: false,
					success: true
				};
			},

			// 重置密码
			reset_password: function reset_password() {
				var that = this,
					password = that.$refs.password.value,
					test_account = that.login_type === 'email_pwd' ? 'test_email' : 'test_phone';
				that.valid_text = '';
				if (!that[test_account].error && !that[test_account].success) {
					that[test_account].error = true;
					that.valid_text = "请输入正确的信息";
				}
				if (!that.test_pwd.error && !that.test_pwd.success) {
					that.test_pwd.error = true;
					that.valid_text = "请输入正确的信息";
				}
				if (!that.test_repeat_pwd.error && !that.test_repeat_pwd.success) {
					that.test_repeat_pwd.error = true;
					that.valid_text = "请输入正确的信息";
				}
				if (!that.test_code.error && !that.test_code.success) {
					that.test_code.error = true;
					that.valid_text = "请输入正确的信息";
				}
				if (that[test_account].error || that.test_code.error || that.test_pwd.error || that
					.test_repeat_pwd.error) return false;
				var code = void 0,
					user_name = void 0,
					mid = void 0,
					enPassword = void 0;
				if (that.login_type === 'email_pwd') {
					code = that.$refs.email_code.value;
					user_name = that.$refs.email.value;
					mid = that.mid;
				} else {
					user_name = that.$refs.phone.value;
					code = that.$refs.phone_code.value;
					mid = that.mid;
				}
				if (code.length <= 0) return false;
				that.$axios.get("/api/common/public_key/").then(function(data) {
					var RsaKey = that.$rsa,
						Base64 = that.$base64,
						rsakey = new RsaKey(),
						base64 = new Base64(),
						modulus = data.data.modulus,
						exponent = data.data.exponent;
					rsakey.setPublic(base64.b64tohex(modulus), base64.b64tohex(exponent));
					enPassword = base64.hex2b64(rsakey.encrypt(password));
					that.$axios.post('/api/password/find_password_submit/', {
						code: code,
						username: user_name,
						mid: mid,
						enPassword: enPassword
					}).then(function(data) {
						if (data.data.code === '2') {
							that.can_get_code = true;
							that.show_toast('修改成功');
							that.delete_cookies();
							that.change_login_type('account');
						} else {
							var content = data.data.content;
							that.valid_text = content;
							if (that.login_type === 'email_pwd') {
								switch (true) {
									case content.indexOf('验证码') >= 0:
										that.test_code = {
											error: true,
											success: false
										};
										break;
									case content.indexOf('邮箱') >= 0:
										that.test_email = {
											error: true,
											success: false
										};
										break;
									case content.indexOf('密码') >= 0:
										that.test_pwd = {
											error: true,
											success: false
										};
										break;
								}
							} else {
								switch (true) {
									case content.indexOf('验证码') >= 0:
										that.test_code = {
											error: true,
											success: false
										};
										break;
									case content.indexOf('手机') >= 0:
										that.test_phone = {
											error: true,
											success: false
										};
										break;
									case content.indexOf('密码') >= 0:
										that.test_pwd = {
											error: true,
											success: false
										};
										break;
								}
							}
						}
					});
				});
			},


			/* 验证码校验 */
			validate_code: function validate_code(e) {
				var that = this,
					code = e.target.value,
					code_reg = /^\d{6}$/,
					obj = that.test_code;
				if (code === '') {
					that.valid_detail_text.code = null;
					obj = {
						error: false,
						success: false
					};
					that.test_code = obj;
					return false;
				}
				if (!code_reg.test(code)) {
					that.valid_detail_text.code = "请输入正确的验证码";
					obj = {
						error: true,
						success: false
					};
					that.test_code = obj;
					return false;
				}
				that.valid_detail_text.code = null;
				obj = {
					error: false,
					success: true
				};
				that.test_code = obj;
			},


			// 控制密码是否明文展示
			toggle_password_show: function toggle_password_show(e) {
				var that = this;
				var $input = $(e.target).parent().find('input');
				var type = $input.attr('type') === 'password' ? 'text' : 'password';
				$input.attr('type', type);
				that.show_password = !that.show_password;
				$(e.target).toggleClass('show');
			},


			/*------------------- 绑定账号 -------------------*/
			validate_account: function validate_account(get_code) {
				var that = this,
					account = that.account;
				if (!account) {
					that.valid_detail_text.account = null;
					that.test_bind_account = {
						error: false,
						success: false
					};
					return false;
				}
				if (!$validate(account).phone() && !$validate(account).email()) {
					that.valid_detail_text.account = "格式错误";
					that.test_bind_account = {
						error: true,
						success: false
					};
					return false;
				}
				// 手机号校验
				if ($validate(account).phone()) {
					that.useful_phone(account, function(code) {
						if (code === '2') {
							that.valid_detail_text.account = null;
							that.test_bind_account = {
								error: false,
								success: true
							};
							if (that.can_get_code && get_code) that.get_phone_code();
						} else {
							that.valid_detail_text.account = '该手机已被绑定';
							that.test_bind_account = {
								error: true,
								success: false
							};
						}
					});
				}
				// 邮箱号校验
				if ($validate(account).email()) {
					that.useful_email(account, function(result, content) {
						if (!result) {
							that.valid_detail_text.account = '该邮箱已被绑定';
							that.test_bind_account = {
								error: true,
								success: false
							};
						} else {
							that.valid_detail_text.account = null;
							that.test_bind_account = {
								error: false,
								success: true
							};
							if (that.can_get_code && get_code) that.get_email_code();
						}
					});
				}
			},

			// 绑定手机或邮箱
			bind_account: function bind_account() {
				var that = this;
				var account = that.account;
				if (!that.test_bind_account.error && !that.test_bind_account.success) {
					that.test_bind_account.error = true;
					that.valid_text = "请输入正确的信息";
					return false;
				}
				if (!that.test_code.error && !that.test_code.success) {
					that.test_code.error = true;
					that.valid_text = "请输入正确的信息";
					return false;
				}
				if (!that.test_pwd.error && !that.test_pwd.success && !that.has_password) {
					that.test_pwd.error = true;
					that.valid_text = "请输入正确的信息";
					return false;
				}
				if ($validate(account).phone()) {
					that.bind_account_by_type('mobile');
				} else {
					that.bind_account_by_type('email');
				}
			},

			// 绑定邮箱或手机号
			bind_account_by_type: function bind_account_by_type(type) {
				var that = this;
				var account = that.account;
				var code = that.$refs.code.value;
				var url = '/api/member/bind_' + type + '_submit/';
				var params = {};
				if (type === 'email') {
					params = {
						mid: that.bind_mid,
						email: account,
						code: code
					};
				} else {
					params = {
						mid: that.bind_mid,
						mobile: account,
						code: code
					};
				}
				// 已有密码时
				if (that.has_password) {
					that.$axios.post(url, params).then(function(data) {
						if (data.data.code === '2') {
							that.$toast("关联成功", 2000);
							that.close();
							that.$emit('success_callback');
						} else {
							that.$toast(data.data.content, 2000);
						}
					});
				} else {
					var password = that.$refs.password.value;
					that.$axios.get("/api/common/public_key/").then(function(data) {
						var res_data = data.data;
						var RsaKey = that.$rsa,
							Base64 = that.$base64,
							rsakey = new RsaKey(),
							base64 = new Base64(),
							modulus = res_data.modulus,
							exponent = res_data.exponent;
						rsakey.setPublic(base64.b64tohex(modulus), base64.b64tohex(exponent));
						var enPassword = base64.hex2b64(rsakey.encrypt(password));
						params.enPassword = enPassword;
						that.$axios.post(url, params).then(function(data) {
							if (data.data.code === '2') {
								that.$toast("关联成功", 2000);
								that.close();
								that.$emit('success_callback');
							} else {
								that.$toast(data.data.content, 2000);
							}
						});
					});
				}
			},

			// 重置输入框状态
			reset_input_state: function reset_input_state(type) {
				var that = this;
				var test = 'test_' + type;
				var all_have_value = true;
				$('.center_main input').each(function(index, ele) {
					if (!$(ele).hasClass('hidden') && !$(ele).val()) all_have_value = false;
				});
				if (all_have_value) {
					$('.center_main .submit').addClass('able');
				} else {
					$('.center_main .submit').removeClass('able');
				}
				if (that[test]) {
					that[test] = {
						error: false,
						success: false
					};
					that.valid_detail_text[type] = null;
				}
			},

			// 显示toast提示
			show_toast: function show_toast(content) {
				var that = this;
				that.toast_content = content;
				that.toast_show = true;
				setTimeout(function() {
					that.toast_show = false;
					that.toast_content = null;
				}, 1500);
			}
		}
	});
	/* WEBPACK VAR INJECTION */
}.call(__webpack_exports__, __webpack_require__(5)))

//////////////////
// WEBPACK FOOTER
// ./node_modules/babel-loader/lib!./node_modules/vue-loader/lib/selector.js?type=script&index=0!./src/components/LoginModal.vue
// module id = 328
// module chunks = 82

//# sourceURL=webpack:///./src/components/LoginModal.vue?./node_modules/babel-loader/lib!./node_modules/vue-loader/lib/selector.js?type=script&index=0
