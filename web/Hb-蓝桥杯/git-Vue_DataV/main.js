import Vue from 'vue' // 之前没有这句也要加
import dataV from '@jiaminghi/data-view'
Vue.use(dataV)

<dv-scroll-ranking-board :config="config" style="width:500px;height:300px" />
<script>
  export default {
    data() {
      return {
        config: {
          data: [
            {
              name: '周口',
              value: 55
            },
            {
              name: '南阳',
              value: 120
            },
            {
              name: '西峡',
              value: 78
            },
            {
              name: '驻马店',
              value: 66
            },
            {
              name: '新乡',
              value: 80
            },
            {
              name: '信阳',
              value: 45
            },
            {
              name: '漯河',
              value: 29
            }
          ]
        }
      }
    }
  }
</script>
