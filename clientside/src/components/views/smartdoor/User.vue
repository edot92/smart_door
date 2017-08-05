<template>
  <div class="content">
    <div class="row">
      <div class="col-md-12">

        <button type="button" class="btn btn-primary" @click="showAddNew()"><i class="fa fa-plus"></i>Tambahkan user Baru</button>
        </di>
      </div>
      <v-client-table :data="tabel.tableData" :columns="tabel.columns" :options="tabel.options">
        <template slot="delete" scope="props">
          <div>
            <!-- <a class="fa fa-edit" :href="edit(props.row.id)"></a> -->
            <!-- <a class="fa fa-edit" @click="edit(props.row.id)"></a> -->
            <a class="fa fa-eraser" @click.prevent="deleteRow(props.row.id)"></a>

          </div>
        </template>
      </v-client-table>
      <!-- Modal -->
      <div class="modal fade modal-md" id="myModal" role="dialog">
        <div class="modal-dialog">
          <div class="modal-content">
            <div class="modal-header">
              <button type="button" class="close" data-dismiss="modal">&times;</button>
              <h4 class="modal-title">Tambahkan user</h4>
            </div>
            <div class="modal-body">
              <form action="" class="form-horizontal" role="form">
                <!-- <div class="form-group">
              <legend>Form title</legend>
            </div> -->
                <div class="form-group">
                  <label class="control-label col-sm-4" for="user">Username:</label>
                  <div class="col-sm-8">
                    <input type="text" v-model="form.username" class="form-control" placeholder="Username" required>
                  </div>
                </div>
                <div class="form-group">
                  <label class="control-label col-sm-4" for="user">Password:</label>
                  <div class="col-sm-8">
                    <input type="password" v-model="form.password" class="form-control" placeholder=" Password" required>
                  </div>
                </div>
                <div class="form-group">
                  <div class="col-sm-8 col-sm-offset-2">
                    <button type="submit" class="btn-block btn btn-primary" @click.prevent="AddNew()">Simpan</button>
                  </div>
                </div>
              </form>

            </div>
            <div class="modal-footer">
              <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  export default {
    data () {
      return {
        form: {
          username: '',
          password: ''
        },
        tabel: {
          columns: ['id', 'username', 'password', 'delete'],
          tableData: [

          ],
          options: {
            // see the options API
            headings: {
              id: 'ID',
              username: 'Username',
              password: 'user',
              delete: 'Delete'
            }
            // childRow: function (h, row) {
            //   return '<div>My custom content for row {row.id}</div>'
            // }
          }
        }
      }
    },
    mounted () {
      this.getAlluser()
    },
    methods: {
      deleteRow: function (row) {
        // this.preventDefault()
        // return `<a href='#!/${row.id}/edit'><i class='glyphicon glyphicon-edit'></i></a>`
        const thisVue = this
        thisVue.axios({
          method: 'post',
          url: '/user/deleteuserbyid',
          data: { id: parseInt(row) }
        })
          .then(function (res) {
            console.log(res.data)
            // var jam = window.moment().format('hh:mm:ss')
            // var tanggal = window.moment().format('DD-MM-YYYY')
            if (res.data.status === 'success') {
              $.notify({
                message: res.data.message
              }, {
                z_index: 2000,
                delay: 400,
                type: 'success'
              })
              thisVue.getAlluser()
            } else {
              $.notify({
                message: res.data.message
              }, {
                z_index: 2000,
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
      getAlluser () {
        const thisVue = this
        thisVue.axios({
          method: 'get',
          url: '/user/getalluser'
        })
          .then(function (res) {
            console.log(res.data)
            // var jam = window.moment().format('hh:mm:ss')
            // var tanggal = window.moment().format('DD-MM-YYYY')
            if (res.data.status === 'success') {
              $.notify({
                message: res.data.message
              }, {
                z_index: 2000,
                delay: 400,
                type: 'success'
              })
              thisVue.tabel.tableData = res.data.data
            } else {
              $.notify({
                message: res.data.message
              }, {
                z_index: 2000,
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
      showAddNew () {
        $('#myModal').modal()
      },
      AddNew () {
        const thisVue = this
        if (this.form.username === '' ||
          this.form.password === '') {
          swal(
            'info',
            'harap isi parameter',
            'error'
          )
          return
        }
        const paramSave = {
          username: this.form.username,
          password: this.form.password
        }
        thisVue.axios({
          method: 'post',
          url: '/user/addnewuser',
          data: paramSave
        })
          .then(function (res) {
            console.log(res.data)
            // var jam = window.moment().format('hh:mm:ss')
            // var tanggal = window.moment().format('DD-MM-YYYY')
            if (res.data.status === 'success') {
              $.notify({
                message: res.data.message
              }, {
                z_index: 2000,
                delay: 400,
                type: 'success'
              })
              thisVue.getAlluser()
            } else {
              $.notify({
                message: res.data.message
              }, {
                z_index: 2000,
                delay: 400,
                type: 'danger'
              })
            }
          })
          .catch(function (error) {
            // alert(error)
            console.error(error)
          })
      }

    }
  }

</script>
