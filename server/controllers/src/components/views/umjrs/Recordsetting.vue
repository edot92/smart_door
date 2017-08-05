<template lang="html">
<div id="Recordsetting" class="content">
  <div class="form-horizontal">
        <div class="form-group">
            <label class="control-label col-sm-4" for="pwd">No BPJS:</label>
            <div class="col-sm-4">
              <v-select :value.sync="selected" :options="options" :onChange="selectChange"></v-select>
            </div>
        </div>

        <div class="form-group">
            <label class="control-label col-sm-4" for="pwd">Nama Pasien:</label>
            <div class="col-sm-4">
              <input disabled type="text" class="form-control" v-model="recordform.nama_lengkap" placeholder="???">
            </div>
        </div>
    <hr>
          <div class="form-group">
              <label class="control-label col-sm-4" for="pwd">Temperature Dan BPM:</label>
              <div class="col-sm-4">
                <toggle-button :width="100" :sync="true"  :color="{checked: '#42b983', unchecked: '#dd4b39' }" @change="onChangeChecked" :value="recordform.recordToogle" :labels="{checked: 'RECORD START', unchecked: 'RECORD STOP'}"/>
              </div>
          </div>
      <hr>
            <hr>
            <div class="form-group">
              <div class="col-sm-8 col-sm-offset-1"><button class="btn btn-primary btn-block" v-on:click="simpanRecord">Simpan </button>
              </div>
            </div>
    </div>
</div>
</template>

<script>
import vSelect from 'vue-select'
var promise
export default {
  components: {vSelect},
  data () {
    return {
      selected: null,
      promise: null,
      options: ['foo', 'bar', 'baz'],
      isActiveChecked: false,
      recordform: {
        no_bpjs: '',
        nama_lengkap: '',
        temperature: '',
        recordToogle: true,
        status: ''
      }
    }
  },
  mounted () {
    var thisVue = this
    promise = new Promise((resolve, reject) => {
      thisVue.axios({
        method: 'get',
        url: 'record/getallpasien'
      })
      .then(function (response) {
        resolve(response)
      }).catch(function (error) {
        if (typeof error.response === 'undefined') {
          reject('network errors')
          return
        }
        swal(
            'info',
            error.response.data.error,
            'error'
          )
        reject(error.response.data.error)
      })// end axios
    })

    // get last state record
    promise.then(res => {
      window.listpasien = res.data.data
      thisVue.options = []
      for (var i = 0; i < window.listpasien.length; i++) {
        thisVue.options[i] = window.listpasien[i].no_bpjs
      }
      return new Promise((resolve, reject) => {
        thisVue.axios({
          method: 'get',
          url: 'record/getrecordactive'
        })
        .then(function (response) {
          if (response.data.message.status === 'active') {
            resolve(response)
          } else {
            reject('param json invalid on url record/getrecordactive')
          }
        }).catch(function (error) {
          thisVue.recordform.recordToogle = false
          thisVue.isActiveChecked = thisVue.recordform.recordToogle
          if (typeof error.response === 'undefined') {
            reject('network errors')
            return
          }
          if (error.response.data.error === 'record not found') {
            reject('record not found')
            return
          } else {
            reject(error.response.data.error)
          }
        })// end axios
      })
    }).then(res => {
      console.log(res)
      const response = res
      thisVue.no_bpjs = response.data.message.no_bpjs
      thisVue.selected = response.data.message.no_bpjs
      thisVue.nama_lengkap = response.data.message.nama_lengkap
      thisVue.recordform.recordToogle = true
      thisVue.isActiveChecked = thisVue.recordform.recordToogle
      console.log(thisVue.recordform.recordToogle)
      console.log(thisVue.isActiveChecked)
    }).catch(err => {
      console.log(err)
      // alert(err)
      if (err !== null) {
        swal(
          'info',
          err,
          'error'
        )
      }
    })
  },
  methods: {
    simpanRecord: function (param) {
      if (this.recordform.nama_lengkap === '' ||
      this.recordform.no_bpjs === '') {
        swal(
            'info',
            'pilih pasien dengan memilih no bpjs no bpjs',
            'error'
          )
        return false
      }
      var thisVue = this
      console.log(this.recordform.status)
      var paramJSON = {
        status: thisVue.recordform.status,
        no_bpjs: thisVue.recordform.no_bpjs,
        nama_lengkap: thisVue.recordform.nama_lengkap,
        created_at: '',
        update_at: ''
      }
      console.log(paramJSON)
      thisVue.axios({
        method: 'post',
        url: 'record/setrecordactive',
        data: paramJSON
      })
      .then(function (response) {
        swal(
            'info',
            response.data.message,
            'success'
          )
      }).catch(function (error) {
        if (typeof error.response === 'undefined') {
          swal(
              'info',
              'network errors',
              'error'
            )
          return
        }
        swal(
            'info',
            error.response.data.error,
            'error'
          )
      })
    },
    selectChange: function (param) {
      for (var i = 0; i < window.listpasien.length; i++) {
        if (window.listpasien[i].no_bpjs === param) {
          this.recordform.no_bpjs = window.listpasien[i].no_bpjs
          this.recordform.nama_lengkap = window.listpasien[i].nama_lengkap
        }
      }
    },
    onChangeChecked: function () {
      this.isActiveChecked = !this.isActiveChecked
      if (this.isActiveChecked === true) {
        this.recordform.status = 'active'
      } else {
        this.recordform.status = ''
      }
      console.log(this.isActiveChecked)
    },
    getListPasien: function () {

    }
  }
}
</script>

<style lang="css">
</style>
