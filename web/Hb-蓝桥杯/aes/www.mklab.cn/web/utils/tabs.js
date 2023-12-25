$(function() {
	var a = 100;
	$(".menus0 ul").each(function() {
		$(".menus0 li").mouseover(function() {
			var b = $(this).index();
			$(".menus0 .bg").css("left", (b - 1) * a + "px");
			$(".menus0 li").css("color", "#000");
			$(this).css("color", "#fff")
		});
		$(".menus0 li").mouseout(function() {
			$(".menus0 li").css("color", "#000");
			$(".menus0 .bg").css("left", "0");
			$(".menus0 li").eq(0).css("color", "#fff")
		})
	});
	$(".menus1 ul").each(function() {
		var b = 0;
		$(".menus1 li").mouseover(function() {
			var f = $(this).index();
			$(".menus1 .bg").css("left", (f - 1) * a + "px");
			$(".menus1 li").css("color", "#000");
			$(this).css("color", "#fff")
		});
		$(".menus1 li").click(function() {
			var f = $(this).index();
			$(".menus1 .bg").css("left", (f - 1) * a + "px");
			$(this).css("color", "#fff");
			window.location = $(this).find("a").attr("href")
		});
		$(".menus1 li").mouseout(function() {
			$(".menus1 .bg").css("left", b * a + "px");
			$(".menus1 li").css("color", "#000");
			$(".menus1 li").eq(b).css("color", "#fff")
		});
		var c = $.parseURL(window.location);
		var e = c.segments;
		var d = e[e.length - 1];
		$(".menus1 li").each(function() {
			var f = $(this).index();
			if ($(this).attr("id") == d) {
				b = f - 1;
				$(".menus1 .bg").css("left", (f - 1) * a + "px")
			}
		})
	});
	$(".menus2 ul").each(function() {
		var b = 0;
		$(".menus2 li").mouseover(function() {
			var c = $(this).index();
			$(".menus2 .bg").css("left", (c - 1) * a + "px");
			$(".menus2 li").css("color", "#000");
			$(this).css("color", "#fff")
		});
		$(".menus2 li").click(function() {
			var c = $(this).index();
			b = c - 1;
			$(".menus2 .bg").css("left", (c - 1) * a + "px");
			$(this).css("color", "#fff");
			$(".menus2 .menus-list").removeClass("show");
			$(".menus2 .menus-list").eq(c - 1).addClass("show");
			$(".tab1").removeClass("show");
			$(".tab1").eq(c - 1).addClass("show")
		});
		$(".menus2 li").mouseout(function() {
			$(".menus2 .bg").css("left", b * a + "px");
			$(".menus2 li").css("color", "#000");
			$(".menus2 li").eq(b).css("color", "#fff")
		})
	});
	$(".menus3 ul").each(function() {
		$(".menus3 li").mouseover(function() {
			var b = $(this).index();
			$(".menus3 .bg").css("left", (b - 1) * a + "px");
			$(".menus3 li").css("color", "#000");
			$(this).css("color", "#fff");
			$(".tab2").removeClass("show");
			$(".tab2").eq(b - 1).addClass("show")
		})
	})
});
