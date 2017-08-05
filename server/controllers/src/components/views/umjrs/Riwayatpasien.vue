<template lang="html">
<div id="riwayatpasien" class="content">

  <form action="" method="#" class="form-horizontal" >
    <div class="form-group">
        <label class="control-label col-sm-4" for="pwd">No BPJS:</label>
        <div class="col-sm-4">
          <v-select :value.sync="param_riwayat.selected" :options="param_riwayat.no_bpjs" :onChange="selectChange"></v-select>
        </div>
    </div>
      <!-- <div class="form-group">
          <label class="control-label col-sm-2" for="pwd">no_bpjs </label>
          <div class="col-sm-10">
              <input v-model="param_riwayat.no_bpjs" type="text" class="form-control" required>
          </div>
      </div> -->
      <div class="form-group">
          <div class="col-sm-10 col-sm-offset-2">
              <button @click.prevent="showHistory()" class="btn btn-primary btn-block">Tampilkan Data</button>
          </div>
      </div>
  </form>
  <br>
  <div class="row">
    <download-excel
        class   = "btn btn-primary"
        :data   = "tabel.json_data"
        :fields = "tabel.json_fields"
        name    = "filename.xls">
        Export Data
    </download-excel>
  </div>
  <br>
  <div class="row">
      <v-client-table :data="tabelriwayat.data" :columns="tabelriwayat.columns" :options="tabelriwayat.options"></v-client-table>
  </div>
</div>
</template>

<script>
import vSelect from 'vue-select'
export default {
  components: {vSelect},
  data () {
    return {
      tabel: {
        json_fields: {
          'id': 'String',
          'bpm': 'String',
          'no_bpjs': 'String',
          'temperature': 'String',
          'update_at': 'String'
        },
        json_data: []
      },
      param_riwayat: {
        no_bpjs: ['foo', 'bar'],
        selected: null
      },
      tabelriwayat: {
        columns: [
          'id',
          'no_bpjs',
          'bpm',
          'temperature',
          'update_at'
        ],
        data: [
        ],
        options: {
// see the options API
        }
      }
    }
  },
  mounted () {
    var thisVue = this
    thisVue.axios({
      method: 'get',
      url: 'riwayat/getallpasien'
    })
      .then(function (response) {
        thisVue.param_riwayat.no_bpjs = []
        // // thisVue.tabelriwayat.data = response.data.data
        for (var i = 0; i < response.data.data.length; i++) {
          thisVue.param_riwayat.no_bpjs[i] = response.data.data[i].no_bpjs
          response.data.data[i].created_at = moment(moment(response.data.data[i].created_at).toString()).format('DD-MM-YYYY HH:mm:ss')
          response.data.data[i].update_at = moment(moment(response.data.data[i].update_at).toString()).format('DD-MM-YYYY HH:mm:ss')
        }
      }).catch(function (error) {
        if (typeof error.response === 'undefined') {
          alert('network errors')
          return
        }
        swal(
            'info',
            error.response.data.error,
            'error'
          )
      })// end axios
  },
  methods: {
    selectChange: function (param) {
      this.param_riwayat.selected = param
    },
    showHistory: function () {
      alert(this.param_riwayat.selected)
      if (this.param_riwayat.selected === null || this.param_riwayat.selected === '') {
        swal(
            'info',
            'harap memilih no bpjs',
            'error'
          )
        return
      }
      var thisVue = this
      thisVue.axios({
        method: 'post',
        url: 'riwayat/gethistorybynobpjs',
        data: {
          no_bpjs: thisVue.param_riwayat.selected
        }
      })
        .then(function (response) {
          for (var i = 0; i < response.data.data.length; i++) {
            response.data.data[i].created_at = moment(moment(response.data.data[i].created_at).toString()).format('DD-MM-YYYY HH:mm:ss')
            response.data.data[i].update_at = moment(moment(response.data.data[i].update_at).toString()).format('DD-MM-YYYY HH:mm:ss')
          }
          thisVue.tabelriwayat.data = response.data.data
          thisVue.tabel.json_data = []
          thisVue.tabel.json_data = response.data.data
        }).catch(function (error) {
          if (typeof error.response === 'undefined') {
            alert('network errors')
            return
          }
          swal(
              'info',
              error.response.data.error,
              'error'
            )
        })// end axios
    }
  }
}
</script>

<style lang="css">
</style>
