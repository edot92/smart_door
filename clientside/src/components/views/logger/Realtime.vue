<template lang="html">
<div id="realtime" class="content">
  <div class="row">
      <div class="col-md-4">
          <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Temperature (&#8451;):</label>
              <div class="col-sm-6">
                  <input disabled type="text" class="form-control" v-model="Temperature" placeholder="???">
              </div>
          </div>
      </div>
      <div class="col-md-4">
          <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Humidity (%):</label>
              <div class="col-sm-6">
                  <input  disabled type="text" class="form-control"               v-model="Humidity"
 placeholder="???">
              </div>
          </div>
      </div>
      <div class="col-md-4">
          <div class="form-group">
              <label class="control-label col-sm-5" for="pwd"> Tegangan (Volt):</label>
              <div class="col-sm-6">
                  <input disabled type="text" class="form-control"   v-model="Loadvoltage"  placeholder="???">
              </div>
          </div>
          </div>
      </div>
      <div class="row">
      <div class="col-md-4">
          <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Arus (miliAmpere]):</label>
              <div class="col-sm-6">
                  <input disabled type="text" class="form-control" v-model="Current" placeholder="???">
              </div>
          </div>
      </div>
      <div class="col-md-4">
          <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Daya (Watt):</label>
              <div class="col-sm-6">
                  <input disabled type="text" class="form-control"  v-model="Daya"  placeholder="???">
              </div>
          </div>
          </div>
          <div class="col-md-4">
              <div class="form-group">
                  <label class="control-label col-sm-5" for="pwd">Auto Updated Chart:</label>
                  <div class="col-sm-6">
                    <toggle-button @change="onChangeautoUpdateChart" :value="autoUpdateChart" color="#82C7EB" :sync="true" :labels="true"/>

                  </div>
              </div>
              </div>
      </div>
      <br>

<div class="row" style="display:none">
  <button @click="sampleUpdate">Updated</button>
<div>
<label>TIME </label>
<input id="waktu" val="">
</div>
</div>
<div class="row">
  <div id="chartAkuh" style="min-width: 310px; height: 400px; margin: 0 auto"></div>
</div>
<br>

</div>
</template>

<script>
function initChart () {
  $(document).ready(function () {
    Highcharts.setOptions({
      global: {
        useUTC: false
      }
    })
    Highcharts.chart('chartAkuh', {
      chart: {
        type: 'spline',
        animation: Highcharts.svg, // don't animate in old IE
        marginRight: 10,
        events: {
          load: function () {
            var thisHighchart = this
            $(document).on('updatedValue', updatedValueHandler)
            function updatedValueHandler (e) {
              var seriesTemperature = thisHighchart.series[0]
              var seriesHumidity = thisHighchart.series[1]
              var seriesCurrent = thisHighchart.series[2]
              var seriesLoadvoltage = thisHighchart.series[3]
              var x = (new Date()).getTime() // current time
              var yTemperature = e.Temperature
              var yHumidity = e.Humidity
              var yCurrent = e.Current
              var yLoadvoltage = e.Loadvoltage
              $('#waktu').val((new Date()).getTime())
              seriesTemperature.addPoint([x, yTemperature], true, true)
              seriesHumidity.addPoint([x, yHumidity], true, true)
              seriesCurrent.addPoint([x, yCurrent], true, true)
              seriesLoadvoltage.addPoint([x, yLoadvoltage], true, true)
            }
          }
        }
      },
      title: {
        text: 'GRAFIK SISTEM DATA LOGGER TEMPERATURE BATERAI'
      },
      xAxis: {
        type: 'datetime',
        tickPixelInterval: 150
      },
      yAxis: {
        title: {
          text: 'Value'
        },
        plotLines: [{
          value: 0,
          width: 1,
          color: '#808080'
        }]
      },
      tooltip: {
        formatter: function () {
          return '<b>' + this.series.name + '</b><br/>' +
                    Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) + '<br/>' +
                    Highcharts.numberFormat(this.y, 2)
        }
      },
      legend: {
        enabled: true
      },
      exporting: {
        enabled: false
      },
      series: [{
        name: 'Temperature',
        data: (function () {
                // generate an array of random data
          var data = []
          var time = (new Date()).getTime()
          var i

          for (i = -19; i <= 0; i += 1) {
            data.push({
              x: time + i * 1000,
              y: 0
            })
          }
          return data
        }())
      },
      {
        name: 'Humidity',
        data: (function () {
                // generate an array of random data
          var data = []
          var time = (new Date()).getTime()
          var i

          for (i = -19; i <= 0; i += 1) {
            data.push({
              x: time + i * 1000,
              y: 0
            })
          }
          return data
        }())
      }, {
        name: 'Current',
        data: (function () {
                // generate an array of random data
          var data = []
          var time = (new Date()).getTime()
          var i

          for (i = -19; i <= 0; i += 1) {
            data.push({
              x: time + i * 1000,
              y: 0
            })
          }
          return data
        }())
      }, {
        name: 'Loadvoltage',
        data: (function () {
                // generate an array of random data
          var data = []
          var time = (new Date()).getTime()
          var i

          for (i = -19; i <= 0; i += 1) {
            data.push({
              x: time + i * 1000,
              y: 0
            })
          }
          return data
        }())
      }]
    })
  })
}
export default{

  mounted () {
    initChart()
    var thisVue = this
    setInterval(function () {
      thisVue.axios({
        method: 'get',
        url: '/device/realtimebox'
      })
    .then(function (response) {
      thisVue.Temperature = response.data.data.temperature
      thisVue.Humidity = response.data.data.humidity
      if (response.data.data.current < 0) {
        // response.data.data.current = response.data.data.current * -1
        response.data.data.current = 0
      }
      thisVue.Current = response.data.data.current
      thisVue.Shuntvoltage = response.data.data.shuntvoltage
      thisVue.Busvoltage = response.data.data.busvoltage
      thisVue.Loadvoltage = response.data.data.loadvoltage
      thisVue.Daya = (parseFloat(thisVue.Loadvoltage) * 0.001)
      thisVue.Daya = thisVue.Daya * parseFloat(thisVue.Current)
      if (thisVue.autoUpdateChart === true) {
        $.event.trigger({
          type: 'updatedValue',
          val1: Math.floor(Math.random() * 10) + 1,
          val2: Math.floor(Math.random() * 10) + 1,
        // data: {
          Temperature: thisVue.Temperature,
          Humidity: thisVue.Humidity,
          Current: thisVue.Current,
          Loadvoltage: thisVue.Loadvoltage,
          waktu: thisVue.LastUpdate
        // }
        })
      }
    })
    .catch(function (error) {
      console.error(error)
    })
    }, 2000)
  },
  data () {
    return {
      autoUpdateChart: true,
      Daya: 0,
      Temperature: 4.42,
      Humidity: 4.42,
      Current: 1,
      Loadvoltage: 4.42,
      Shuntvoltage: 4.42,
      Busvoltage: 4.42,
      LastUpdate: 0
    }
  },
  methods: {
    onChangeautoUpdateChart () {
      this.autoUpdateChart = !this.autoUpdateChart
    },
    sampleUpdate () {
      const thisVue = this
      $.event.trigger({
        type: 'updatedValue',
        val1: Math.floor(Math.random() * 10) + 1,
        val2: Math.floor(Math.random() * 10) + 1,
        // data: {
        Temperature: thisVue.Temperature,
        Humidity: thisVue.Humidity,
        Current: thisVue.Current,
        Loadvoltage: thisVue.Loadvoltage,
        waktu: thisVue.LastUpdate
      })
    }

  }
}
</script>

<style lang="css">
</style>
