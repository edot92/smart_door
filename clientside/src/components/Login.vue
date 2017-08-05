<template>
  <div class="container container-table">

    <div class="row vertical-10p">
      <div class=" text-center col-md-4 col-sm-offset-4">
        <img src="/static/img/unjft.png" class="image-responsive" style="width:400px;height:200px;">
      </div>
      <div class="container">
        <div class="text-center col-md-4 col-sm-offset-4">
          <!-- login form -->
          <!-- <form class="ui form loginForm" @submit.prevent="checkCreds">
             -->

          <div class="input-group">
            <span class="input-group-addon"><i class="fa fa-envelope"></i></span>
            <input class="form-control" name="username" placeholder="Username" type="text" v-model="form.username">
          </div>

          <div class="input-group">
            <span class="input-group-addon"><i class="fa fa-lock"></i></span>
            <input class="form-control" name="password" placeholder="Password" type="password" v-model="form.password">
          </div>
          <button type="submit" v-bind:class="'btn btn-primary btn-lg ' + loading" @click="login">Submit</button>
          </form>

          <!-- errors -->
          <div v-if=response class="text-red">
            <p>{{response}}</p>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
  import api from '../api'

  export default {
    name: 'Login',
    data (router) {
      return {
        form: {
          password: '',
          username: ''
        },
        section: 'Login',
        loading: '',
        username: '',
        password: '',
        response: ''
      }
    },
    methods: {
      login () {
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
          url: '/user/login',
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
              var jsonAuth = {
                username: thisVue.form.username
                // nama_lengkap: 'edy prasetiyo',
                // role: 'admin'
              }
              // var storageCokie = Cookies.noConflict()
              thisVue.$store.state.username = thisVue.form.username
              Cookies.set('auth', jsonAuth)
              thisVue.$router.push('/user')
            } else {
              thisVue.username = res.data.message
              $.notify({
                message: res.data.message
              }, {
                z_index: 2000,
                delay: 400,
                type: 'danger'
              })
              thisVue.response = res.data.message
            }
          })
          .catch(function (error) {
            // alert(error)
            console.error(error)
          })
      },
      checkCreds () {
        const { username, password } = this

        this.toggleLoading()
        this.resetResponse()
        this.$store.commit('TOGGLE_LOADING')

        /* Making API call to authenticate a user */
        api.request('post', '/login', { username, password })
          .then(response => {
            this.toggleLoading()

            var data = response.data
            /* Checking if error object was returned from the server */
            if (data.error) {
              var errorName = data.error.name
              if (errorName) {
                this.response = errorName === 'InvalidCredentialsError'
                  ? 'Username/Password incorrect. Please try again.'
                  : errorName
              } else {
                this.response = data.error
              }

              return
            }

            /* Setting user in the state and caching record to the localStorage */
            if (data.user) {
              var token = 'Bearer ' + data.token

              this.$store.commit('SET_USER', data.user)
              this.$store.commit('SET_TOKEN', token)

              if (window.localStorage) {
                window.localStorage.setItem('user', JSON.stringify(data.user))
                window.localStorage.setItem('token', token)
              }

              this.$router.push(data.redirect)
            }
          })
          .catch(error => {
            this.$store.commit('TOGGLE_LOADING')
            console.log(error)

            this.response = 'Server appears to be offline'
            this.toggleLoading()
          })
      },
      toggleLoading () {
        this.loading = (this.loading === '') ? 'loading' : ''
      },
      resetResponse () {
        this.response = ''
      }
    }
  }

</script>

<style>
  html,
  body,
  .container-table {
    height: 100%;
    background-color: #282B30 !important;
  }

  .container-table {
    display: table;
    color: white;
  }

  .vertical-center-row {
    display: table-cell;
    vertical-align: middle;
  }

  .vertical-20p {
    padding-top: 20%;
  }

  .vertical-10p {
    padding-top: 10%;
  }

  .logo {
    width: 15em;
    padding: 3em;
  }

  .loginForm .input-group {
    padding-bottom: 1em;
    height: 4em;
  }

  .input-group input {
    height: 4em;
  }
</style>
