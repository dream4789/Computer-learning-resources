; (function () {
    // 接口地址：https://sp0.baidu.com/5a1Fazu8AA54nxGko9WTAnF6hhy/su?wd=
    // "https://sp0.baidu.com/5a1Fazu8AA54nxGko9WTAnF6hhy/su?wd=" + value + "&cb=" + callbackName

    // <li class="wd-item">
    //     <a href="https://www.baidu.com/s?wd={{wdLink}}" target="_blank" class="wd-lk">{{wd}}</a>
    // </li> 

    let searchInput = document.getElementsByClassName("J_searchInput")[0];
    let wdList = document.getElementsByClassName("J_wdList")[0];
    let listWrap = wdList.parentNode;

    searchInput.addEventListener("input", function () {
        let val = this.value.trim();
        if (val.length > 0) {
            getDatas(val, "setDatas")
        } else {
            wdList.innerHTML = "";
            listWrap.style.display = "none";
        }
    })

    function getDatas(value, callbackName) {
        let scriptEle = document.createElement("script");
        scriptEle.src = "https://sp0.baidu.com/5a1Fazu8AA54nxGko9WTAnF6hhy/su?wd=" + value + "&cb=" + callbackName
        document.body.append(scriptEle)
    }

    window.setDatas = function (data) {
        // console.log("data:", data);
        renderList(data)
    }

    // renderList渲染数据到页面上
    function renderList(data) {
        var data = data.s;
        let str = "";
        if (data.length) {
            data.forEach(item => {
                str += `
                    <li class="wd-item">
                        <a href="https://www.baidu.com/s?wd=${item}" target="_blank" class="wd-lk">${item}</a>
                    </li> 
                `
            })
            wdList.innerHTML = str;
            listWrap.style.display = "block";
        } else {
            wdList.innerHTML = "";
            listWrap.style.display = "none";
        }
    }

})()