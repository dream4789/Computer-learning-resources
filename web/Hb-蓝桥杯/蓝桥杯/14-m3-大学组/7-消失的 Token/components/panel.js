/*
 * 本题示例登录成功界面，非作答区域
 */
const PanelTemplate = `
<blockquote v-show="username" class="c-quote">
    <div class="c-quote__content">
        <p> <slot /> </p>
    </div>
    <cite class="c-quote__cite">
        <img src="data:image/jpeg;base64,/9j/4AAQSkZJRgABAQAAAQABAAD/2wCEAAoKCgoKCgsMDAsPEA4QDxYUExMUFiIYGhgaGCIzICUgICUgMy03LCksNy1RQDg4QFFeT0pPXnFlZXGPiI+7u/sBCgoKCgoKCwwMCw8QDhAPFhQTExQWIhgaGBoYIjMgJSAgJSAzLTcsKSw3LVFAODhAUV5PSk9ecWVlcY+Ij7u7+//CABEIACgAKAMBIgACEQEDEQH/xAAxAAACAgIDAAAAAAAAAAAAAAAABQIEAwYBBwgBAAMBAAAAAAAAAAAAAAAAAAECAwD/2gAMAwEAAhADEAAAAOubFVlZafO2E2sG4gPnWbh1IamzcVxlhnDpMQnskgQUwHP/xAArEAACAQMCAwYHAAAAAAAAAAABAgMABBEFIQYSMRMUMkFRkRAiQkNxgdH/2gAIAQEAAT8AWKkgJ8qu4rqCJ5kfCggYxnb1rR7p7m5W2l3Z/AcVHpzDqtJqcAXJiOfTNQappxKh2ZMjzX+VE9jLGw7WF1Zd1LDcHau52sWu2iGSPs7e07eWRsDLydPYEYqG0UgHb4KjP4aW2lZlT5AW82dVH7JO1a/drf6jJNEwaLlVU/CirbXNas41jgv5VRei5zVvo5m6yhai4Xt2XLXlPw9Zq/IJ5ifXkwvvT8Px/ROak0SRPuire7K0l8ceKjdsRXenCk8+1TXRK75Ff//EAB0RAAICAQUAAAAAAAAAAAAAAAABAgMTERIhQVH/2gAIAQIBAT8AyIdvJlHbFdmWJvrfhKKNEJI//8QAGBEAAwEBAAAAAAAAAAAAAAAAABESECD/2gAIAQMBAT8ARJOvj//Z" alt="">
        <div>
            <p><span>用户名：</span><strong id="username"> {{username}} </strong></p>
        </div>
    </cite>
</blockquote>
`
Vue.component('Panel', {
	name: 'Panel',
	template: PanelTemplate,
	props: ['username'],
	data: {},
	watch: {},
	mounted() {},
	methods: {},
})
