<template lang="html">
  <div id="Realtimesensor" class="content">
    <ul class="nav nav-tabs">
   <li class="active"><a data-toggle="tab" href="#home">Realtime Value</a></li>
   <li><a data-toggle="tab" href="#menu1">Biodata Pasien</a></li>
 </ul>
 <div class="tab-content">
    <div id="home" class="tab-pane fade in active">
      <div class="row">
        <div class="col-md-8">
          <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Auto Updated Chart:</label>
              <div class="col-sm-6">
                <toggle-button @change="onChangeautoUpdateChart" :value="autoUpdateChart" color="#82C7EB" :sync="true" :labels="true"/>
              </div>
          </div>
        </div>
        <div class="col-md-4">
          <h5>Last Updated:  {{lastupdated}}</h5>

        </div>
      </div>
      <div class="row">
        <div id="chartAkuh" style="min-width: 310px; height: 400px; margin: 0 auto"></div>
      </div>
      <br>
          <div class="row">
            <div class="col-md-6">
              <div id="gauge1">
              </div>
              </div>
              <div class="col-md-6">
                <div id="gauge2">
                </div>
                </div>
          </div>
    </div>
    <!-- end menu 1 -->
    <div id="menu1" class="tab-pane fade">
      <h3>Biodata Pasien</h3>
      <div class="row">
          <div class="form-group">
            <label class="control-label col-sm-2" for="pwd">No BPJS: </label>
            <div class="col-sm-10">
                <input  disabled v-model="biodata_pasien.no_bpjs" type="text" class="form-control" required>
            </div>

          </div>
                <div class="form-group">
                    <label class="control-label col-sm-2" for="pwd">nama_lengkap </label>
                    <div class="col-sm-10">
                        <input  disabled v-model="biodata_pasien.nama_lengkap" type="text" class="form-control" required>
                    </div>
                </div>
                <div class="form-group">
                    <label class="control-label col-sm-2" for="pwd">jenis_kelamin </label>
                    <div class="col-sm-10">

                    <input disabled  v-model="biodata_pasien.jenis_kelamin" type="text" class="form-control" required>
        </div>
                </div>
                <div class="form-group">
                    <label class="control-label col-sm-2" for="pwd">tanggal_lahir </label>
                    <div class="col-sm-10">
                        <input  disabled  v-model="biodata_pasien.tanggal_lahir" type="text"  id="demo"  class="form-control" required>
                    </div>
                </div>
      </div>
    </div>
    <!-- end menu 2 -->

  </div>


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
              var seriesBpm = thisHighchart.series[1]
              var x = (new Date()).getTime() // current time
              var yTemperature = e.Temperature
              var yBpm = e.Bpm
              // console.log(yTemperature)
              // console.log(yBpm)
              $('#waktu').val((new Date()).getTime())
              seriesTemperature.addPoint([x, yTemperature], true, true)
              seriesBpm.addPoint([x, yBpm], true, true)
            }
          }
        }
      },
      title: {
        text: 'GRAFIK DATA PASIEN'
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
        name: 'BPM',
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
function initGauge (vueThis) {
  vueThis.gauge1 = $('#gauge1').jqxGauge({
    ranges: [{ startValue: 0, endValue: 55, style: { fill: '#4bb648', stroke: '#4bb648' }, endWidth: 5, startWidth: 1 },
                            { startValue: 55, endValue: 110, style: { fill: '#fbd109', stroke: '#fbd109' }, endWidth: 10, startWidth: 5 },
                            { startValue: 110, endValue: 165, style: { fill: '#ff8000', stroke: '#ff8000' }, endWidth: 13, startWidth: 10 },
                            { startValue: 165, endValue: 220, style: { fill: '#e02629', stroke: '#e02629' }, endWidth: 16, startWidth: 13 }],
    ticksMinor: { interval: 5, size: '5%' },
    ticksMajor: { interval: 10, size: '9%' },
    value: 0,
    colorScheme: 'scheme05',
    animationDuration: 1200,
    caption: {
      value: 'Temperature',
      position: 'bottom',
      offset: [0, 10],
      visible: true
    }
  })
  vueThis.gauge1 = $('#gauge2').jqxGauge({
    ranges: [
          { startValue: 0, endValue: 55, style: { fill: '#4bb648', stroke: '#4bb648' }, endWidth: 5, startWidth: 1 },
          { startValue: 55, endValue: 110, style: { fill: '#fbd109', stroke: '#fbd109' }, endWidth: 10, startWidth: 5 },
          { startValue: 110, endValue: 165, style: { fill: '#ff8000', stroke: '#ff8000' }, endWidth: 13, startWidth: 10 },
          { startValue: 165, endValue: 500, style: { fill: '#e02629', stroke: '#e02629' }, endWidth: 16, startWidth: 13 }
    ],
    ticksMinor: { interval: 5, size: '5%' },
    ticksMajor: { interval: 10, size: '9%' },
    value: 0,
    colorScheme: 'scheme02',
    animationDuration: 1200,
    caption: {
      value: 'BPM',
      position: 'bottom',
      offset: [0, 10],
      visible: true
    },
    max: 400
  })
}
export default {
  data () {
    return {
      isNoBpjsAvail: false,
      autoUpdateChart: false,
      gauge1: '',
      lastupdated: '',
      gauge2: '',
      biodata_pasien: {
        nama_lengkap: '',
        jenis_kelamin: '',
        tanggal_lahir: '',
        no_bpjs: ''
      },
      realtime_sensor: {
        namapasien: '',
        temperature: '',
        bpm: '',
        last_update: ''
      }

    }
  },
  mounted () {
    // this.realtimelast()
    const thisVue = this

    const promise = new Promise((resolve, reject) => {
      initGauge(thisVue)
      initChart()
      setTimeout(function () { thisVue.realtimelast(thisVue) }, 2000)
      resolve(true)
    })
    promise.then(res => {
      return new Promise((resolve, reject) => {
        thisVue.axios({
          method: 'get',
          url: '/device/getrecordactiveandbiodata'
        })
        .then(function (response) {
          resolve(response)
        }).catch(function (error) {
          // swal(
          //     'info',
          //     'server error',
          //     'error'
          //   )
          console.log(error)
          reject(error)
        })
      })
    }).then(res => {
      if (res.data.data.record.status === 'active') {
        thisVue.biodata_pasien.no_bpjs = res.data.data.biodata.no_bpjs
        thisVue.biodata_pasien.nama_lengkap = res.data.data.biodata.nama_lengkap
        thisVue.biodata_pasien.jenis_kelamin = res.data.data.biodata.jenis_kelamin
        thisVue.biodata_pasien.tanggal_lahir = res.data.data.biodata.tanggal_lahir
        // thisVue.biodata_pasien.created_at = res.data.data.biodata.created_at
        thisVue.autoUpdateChart = true
      } else {
        thisVue.autoUpdateChart = false
      }
      this.realtimelast(thisVue)
    }).catch(err => {
      console.log(err)
    })
    this.lastupdated = window.moment().format('hh:mm:ss DD-MM-YYYY')
  },

  methods: {
    onChangeautoUpdateChart: function (param) {
      this.autoUpdateChart = param.value
      console.log(this.autoUpdateChart)
    },
    realtimelast: function (thisVue) {
      if (thisVue.autoUpdateChart === true) {
        console.log('autoUpdateChart=true')
        thisVue.axios({
          method: 'get',
          url: '/device/realtimelastactiverecord'
        })
        .then(function (response) {
          $('#gauge1').jqxGauge({
            value: parseInt(response.data.data.temperature, 10)
          })
          console.log('updated')
          $('#gauge2').jqxGauge({
            value: parseInt(response.data.data.bpm, 10)
          })
          thisVue.realtime_sensor.temperature = response.data.data.temperature
          thisVue.realtime_sensor.bpm = response.data.data.bpm
          thisVue.realtime_sensor.last_update = response.data.data.created_at

          $.event.trigger({
            type: 'updatedValue',
            val1: Math.floor(Math.random() * 10) + 1,
            val2: Math.floor(Math.random() * 10) + 1,
          // data: {
            Temperature: parseFloat(thisVue.realtime_sensor.temperature),
            Bpm: parseFloat(thisVue.realtime_sensor.bpm)
          })
          setTimeout(function () { thisVue.realtimelast(thisVue) }, 2000)
        }).catch(function (error) {
          console.log(error)
          // setTimeout(function () { thisVue.realtimelast(thisVue) }, 2000)
          // swal(
          //     'info',
          //     'server error',
          //     'error'
          //   )
        })
      }
    }
  }

}

</script>

<style lang="css">
hr {
    display: block;
    margin-top: 0.5em;
    margin-bottom: 0.5em;
    margin-left: auto;
    margin-right: auto;
    border-style: inset;
    border-width: 1px;
}
</style>
