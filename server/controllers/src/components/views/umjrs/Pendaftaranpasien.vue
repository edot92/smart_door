<template lang="html">
  <div id="pendaftaranpasien" class="content">
    <!-- <h1>Biodata Pasien Baru</h1> -->
    <form action="" method="#" class="form-horizontal" role="form">
  <div class="form-group">
      <label class="control-label col-sm-2" for="pwd">no_bpjs </label>
      <div class="col-sm-6">
          <input v-model="biodata_pasien.no_bpjs" type="text" class="form-control" required>
      </div>
      <div class="col-sm-2">
        <button @click.prevent="cekAvailPasien()" class="btn btn-primary btn-block">CEK DATA</button>
      </div>
      <div class="col-sm-2">
        <button @click.prevent="resetForm()" class="btn btn-primary btn-block">RESET FORM</button>
      </div>
  </div>
</form>
    <form action="" method="#" class="form-horizontal" role="form">

        <div class="form-group">
            <label class="control-label col-sm-2" for="pwd">nama_lengkap </label>
            <div class="col-sm-10">
                <input  v-bind:disabled="isNoBpjsAvail" v-model="biodata_pasien.nama_lengkap" type="text" class="form-control" required>
            </div>
        </div>
        <div class="form-group">
            <label class="control-label col-sm-2" for="pwd">jenis_kelamin </label>
            <div class="col-sm-10">

            <input  v-bind:disabled="isNoBpjsAvail" v-model="biodata_pasien.jenis_kelamin" type="text" class="form-control" required>
</div>
        </div>
        <div class="form-group">
            <label class="control-label col-sm-2" for="pwd">tanggal_lahir </label>
            <div class="col-sm-10">
                <input  v-bind:disabled="isNoBpjsAvail" v-model="biodata_pasien.tanggal_lahir" type="text"  id="demo"  class="form-control" required>
            </div>
        </div>

        <div class="form-group">
            <div class="col-sm-10 col-sm-offset-2">

                <button v-bind:style="{ display: btnSytle,  }" @click.prevent="buatpendaftarbaru()" class="btn btn-primary btn-block">SIMPAN</button>
            </div>
        </div>
    </form>
</div>
</template>

<script>
export default {

  data () {
    return {
      isNoBpjsAvail: false,
      btnSytle: 'inline',
      biodata_pasien: {
        nama_lengkap: '',
        jenis_kelamin: '',
        tanggal_lahir: '',
        no_bpjs: ''
      }
    }
  },
  mounted () {
    $('#demo').daterangepicker({
      locale: {
        format: 'DD-MM-YYYY'
      },
      // 'dateLimit': {
      //   'minutes': 30 * 24 * 60
      // },
      'singleDatePicker': true
      // 'timePicker': true,
      // 'timePicker24Hour': true,
      // 'timePickerSeconds': true,
      // 'startDate': '11-06-2017',
      // 'endDate': '12-06-2017'
    }, function (start, end, label) {
      console.log(start.format('YYYY-MM-DD'))
      // paramDate.startdate = start.format('YYYY-MM-DD HH:mm:ss.SSS')
      // paramDate.enddate = end.format('YYYY-MM-DD HH:mm:ss.SSS')
    })
  },
  methods: {
    resetForm: function () {
      this.biodata_pasien.jenis_kelamin = ''
      this.biodata_pasien.nama_lengkap = ''
      this.biodata_pasien.no_bpjs = ''
      this.biodata_pasien.tanggal_lahir = ''
      this.btnSytle = 'inline'
      this.isNoBpjsAvail = false
    },
    cekAvailPasien: function () {
      // jika pasien sudah terdaftar maka munculkan data
      var thisVue = this
      thisVue.axios({
        method: 'get',
        url: 'pasien/ceknobpjspendaftar?no_bpjs=' + thisVue.biodata_pasien.no_bpjs
      })
        .then(function (response) {
          let temp = response.data.message
          thisVue.biodata_pasien.jenis_kelamin = temp.jenis_kelamin
          thisVue.biodata_pasien.nama_lengkap = temp.nama_lengkap
          thisVue.biodata_pasien.no_bpjs = temp.no_bpjs
          thisVue.biodata_pasien.tanggal_lahir = temp.tanggal_lahir
          thisVue.btnSytle = 'none'
          thisVue.isNoBpjsAvail = true
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
          thisVue.biodata_pasien.jenis_kelamin = ''
          thisVue.biodata_pasien.nama_lengkap = ''
          thisVue.biodata_pasien.no_bpjs = ''
          thisVue.biodata_pasien.tanggal_lahir = ''
          thisVue.btnSytle = 'inline'
          thisVue.isNoBpjsAvail = false
        })
    },
    buatpendaftarbaru: function () {
      if (this.biodata_pasien.nama_lengkap === '' ||
        this.biodata_pasien.jenis_kelamin === '' ||
        this.biodata_pasien.tanggal_lahir === '' ||
        this.biodata_pasien.no_bpjs === '') {
        swal(
            'info',
            'harap isi biodata secara lengkap',
            'error'
          )
      }
      var thisVue = this
      thisVue.axios({
        method: 'post',
        url: '/pasien/pendaftaranbaru',
        data: thisVue.biodata_pasien
      })
        .then(function (response) {
          swal(
              'info',
              'Pendaftaran baru berhasil',
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
              error.response.data.error,
              error.response.data.message,
              'error'
            )
        })
    }
  }
}
</script>

<style lang="css">
</style>
