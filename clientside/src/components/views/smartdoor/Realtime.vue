<template lang="html">
  <div id="realtime" class="content">
    <div class="text-align:right;">
      <h5>User Login: {{Auth.nama_lengkap}}</h5>
    </div>
    <!-- <div>

      <button type="button" class="btn btn-primary" @click="refreshData"><i class="fa fa-refresh"></i>refresh</button>
    </div> -->
    <div class="row garis" style="align-content: center">
      <!-- <div class="col-md-6">
        <div class="row">
          <div style="text-align: center">
            <h4>Status</h4>
          </div>
        </div> -->
      <!-- <div class="row">
          <div class="col-md-6">
            <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Door 1 :</label>
              <div class="col-sm-6">
                <div v-if="statusDoor.door1==='0'">
                  <input disabled type="text" class="form-control" value="tertutup">
                </div>
                <div v-else-if="statusDoor.door1==='1'">
                  <input disabled type="text" class="form-control" value="terbuka">
                </div>
              </div>
            </div>
          </div>
          <div class="col-md-6">
            <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Door 2:</label>
              <div class="col-sm-6">
                <div v-if="statusDoor.door2==='0'">
                  <input disabled type="text" class="form-control" value="tertutup">
                </div>
                <div v-else-if="statusDoor.door2==='1'">
                  <input disabled type="text" class="form-control" value="terbuka">
                </div>
              </div>
            </div>
          </div>
        </div> -->
      <!-- </div> -->
      <div class="col-md-12">
        <div class="row">
          <div style="text-align: center">
            <h4>Control</h4>
          </div>
        </div>
        <div class="row">
          <div class="col-md-6">
            <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Door 1 :</label>
              <div class="col-sm-6">
                <button type="button" class="btn btn-primary" @click="updateDoorValue('1')">Buka Pintu 1</button>
              </div>
            </div>
          </div>
          <div class="col-md-6">
            <div class="form-group">
              <label class="control-label col-sm-5" for="pwd">Door 2 :</label>
              <div class="col-sm-6">
                <button type="button" class="btn btn-primary" @click="updateDoorValue('2')">Buka Pintu 2</button>
              </div>
            </div>
          </div>
        </div>
      </div>
      <br>
    </div>
    <div class="row" style="display:none">
      <button @click="sampleUpdate">Updated</button>
      <div>
        <label>TIME </label>
        <input id="waktu" val="">
      </div>
    </div>


  </div>
</template>

<script>
  export default {

    mounted () {
      var tempAuth = Cookies.get('auth')
      try {
        tempAuth = JSON.parse(tempAuth)
      } catch (error) {
        this.$router.push('/login?error=' + error)
      }
      if (tempAuth.username === '') {
        this.$router.push('/login')
        return
      }
      this.Auth = (tempAuth)
      // console.log(this.Auth)
      this.getData(this)
    },
    data () {
      return {
        Auth: {
          nama_lengkap: 'Ilma'
        },
        statusDoor: {
          door1: '',
          door2: ''
        },
        controlDoor: {
          door1: '',
          door2: ''
        }
      }
    },
    methods: {
      refreshData () {
        this.getData(this)
      },
      getData (thisVue) {
        thisVue.axios({
          method: 'get',
          url: '/device/getlastvalue'
        })
          .then(function (res) {
            if (res.data.status === 'success') {
              const dataRes = res.data.data
              $.notify({
                message: res.data.message
              }, {
                delay: 400,
                type: 'success'
              })
              thisVue.statusDoor.door1 = dataRes.status_door1
              thisVue.statusDoor.door2 = dataRes.status_door2
              thisVue.controlDoor.door1 = dataRes.control_door1
              thisVue.controlDoor.door2 = dataRes.control_door2
            } else {
              $.notify({
                message: res.data.message
              }, {
                delay: 400,
                type: 'danger'
              })
            }
          })
          .catch(function (error) {
            // alert(error)
            console.error(error)
          })
      },
      updateDoorValue (nomorDoor) {
        const thisVue = this
        thisVue.axios({
          method: 'post',
          url: '/device/updatevalue',
          data: {
            number_door: nomorDoor
          }
        })
          .then(function (res) {
            // var jam = window.moment().format('hh:mm:ss')
            // var tanggal = window.moment().format('DD-MM-YYYY')
            if (res.data.status === 'success') {
              $.notify({
                message: res.data.message
              }, {
                delay: 400,
                type: 'success'
              })
            } else {
              $.notify({
                message: res.data.message
              }, {
                delay: 400,
                type: 'danger'
              })
            }
          })
          .catch(function (error) {
            // alert(error)
            console.error(error)
          })
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

<style scoped>
  .garis {
    border-style: solid;
    border-width: 1px;
    border-radius: 10px;
    border-color: gray;
  }
</style>
