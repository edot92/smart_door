<template>
  <ul class="sidebar-menu">
    <li class="header">MENU</li>
    <li class="active pageLink" v-on:click="toggleMenu">
      <router-link to="/realtime"><i class="fa fa-pencil-square-o"></i>
        <span class="page">Realtime</span>
      </router-link>
    </li>
    <!-- <li class="active pageLink" v-on:click="toggleMenu">
        <router-link to="/history"><i class="fa fa-pencil-square-o"></i>
          <span class="page">History</span>
        </router-link>
      </li> -->
    <li class="active pageLink" v-on:click="toggleMenu">
      <router-link to="/email"><i class="fa fa-pencil-square-o"></i>
        <span class="page">Email</span>
      </router-link>
    </li>
    <li class="active pageLink" v-on:click="toggleMenu">
      <router-link to="/user"><i class="fa fa-pencil-square-o"></i>
        <span class="page">User</span>
      </router-link>
    </li>
    <li class="active pageLink" @click.prevent="logout">
      <router-link to="/login"><i class="fa fa-pencil-square-o"></i>
        <span class="page">LOGOUT</span>
      </router-link>
      <!-- <router-link to="#"><i class="fa fa-pencil-square-o"></i>
        <span class="page">Logout</span>
      </router-link> -->
    </li>
    <!-- <li class="header">PAGES</li>
    <li class="pageLink" v-on:click="toggleMenu">
      <router-link to="/login">
        <i class="fa fa-circle-o text-yellow"></i>
        <span class="page"> Login</span>
      </router-link>
    </li>
    <li class="pageLink" v-on:click="toggleMenu">
      <router-link to="/404"><i class="fa fa-circle-o text-red"></i>
        <span class="page"> 404</span>
      </router-link>
    </li> -->
  </ul>
</template>
<script>
  export default {
    name: 'SidebarName',
    mounted () {
      var log = this.$store.state.username
      var user = Cookies.get('auth')
      if (log === '' || user === '') {
        this.$router.push('/login')
      } else {
        this.$router.push('/user')
      }
    },
    methods: {
      logout () {
        this.$store.state.username = ''
        Cookies.remove('auth')
        this.$router.push('/login')
      },
      toggleMenu (event) {
        // remove active from li
        var active = document.querySelector('li.pageLink.active')

        if (active) {
          active.classList.remove('active')
        }
        // window.$('li.pageLink.active').removeClass('active')
        // Add it to the item that was clicked
        event.toElement.parentElement.className = 'pageLink active'
      }
    }
  }

</script>
<style>
  /* override default */

  .sidebar-menu>li>a {
    padding: 12px 15px 12px 15px;
  }

  .sidebar-menu li.active>a>.fa-angle-left,
  .sidebar-menu li.active>a>.pull-right-container>.fa-angle-left {
    animation-name: rotate;
    animation-duration: .2s;
    animation-fill-mode: forwards;
  }

  @keyframes rotate {
    0% {
      transform: rotate(0deg);
    }

    100% {
      transform: rotate(-90deg);
    }
  }
</style>
