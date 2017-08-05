<template>
  <ul class="sidebar-menu">
    <li class="header">MENU</li>
      <li class="active pageLink" v-on:click="toggleMenu">
        <router-link to="/pendaftaranpasien"><i class="fa fa-pencil-square-o"></i>
          <span class="page">Pendaftaran Pasien</span>
        </router-link>
      </li>
      <li class="active pageLink" v-on:click="toggleMenu">
        <router-link to="/riwayatpasien"><i class="fa fa-pencil-square-o"></i>
          <span class="page">Riwayat Pasien</span>
        </router-link>
      </li>
      <li class="active pageLink" v-on:click="toggleMenu">
        <router-link to="/recordsetting"><i class="fa fa-pencil-square-o"></i>
          <span class="page">Record Setting</span>
        </router-link>
      </li>
      <li class="active pageLink" v-on:click="toggleMenu">
        <router-link to="/realtimesensor"><i class="fa fa-pencil-square-o"></i>
          <span class="page">Realtime</span>
        </router-link>
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
  methods: {
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

  .sidebar-menu li.active>a>.fa-angle-left, .sidebar-menu li.active>a>.pull-right-container>.fa-angle-left {
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
