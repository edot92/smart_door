<template>
  <div id="app">
    <div class="wrapper">

    </div>
    <router-view></router-view>
  </div>
</template>

<script>
// import sidebar from '@/componenets/views/SidebarMenu'
// import header from '@/componenets/views/HeaderTop'
  export default {
    name: 'App',
    data () {
      return {
        section: 'Head'
      }
    },
    methods: {
      logout () {
        this.$store.commit('SET_USER', null)
        this.$store.commit('SET_TOKEN', null)

        if (window.localStorage) {
          window.localStorage.setItem('user', null)
          window.localStorage.setItem('token', null)
        }

        this.$router.push('/login')
      }
    }
  }
</script>
