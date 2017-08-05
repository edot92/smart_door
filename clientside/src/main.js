// Import System requirements
import Vue from 'vue'
import VueRouter from 'vue-router'

import axios from 'axios'
import VueAxios from 'vue-axios'
if (process.env.NODE_ENV === 'development') {
  axios.defaults.baseURL = 'http://localhost:8080/v1'
} else {
  axios.defaults.baseURL = '/v1'
}
// axios.defaults.baseURL = 'http://localhost:8080/v1'
// axios.defaults.headers.common['Authorization'] = AUTH_TOKEN
// axios.defaults.headers.post['Content-Type'] =
// 'application/x-www-form-urlencoded'
// axios.defaults.headers.post['Access-Control-Allow-Origin'] = '*'
Vue.use(VueAxios, axios)

import { sync } from 'vuex-router-sync'
import routes from './routes'
import store from './store'
// Import Helpers for filters
import { domain, count, prettyDate, pluralize } from './filters'

// Import Views - Top level
import AppView from './components/App.vue'

import { ClientTable } from 'vue-tables-2'
// Vue.use(ServerTable)
Vue.use(ClientTable)
// Import Install and register helper items
Vue.filter('count', count)
Vue.filter('domain', domain)
Vue.filter('prettyDate', prettyDate)
Vue.filter('pluralize', pluralize)

Vue.use(VueRouter)

// Routing logic
var router = new VueRouter({
  routes: routes,
  mode: 'history',
  scrollBehavior: function (to, from, savedPosition) {
    return savedPosition || {
      x: 0,
      y: 0
    }
  }
})
var temp = Cookies.get('auth')
if (typeof temp !== 'undefined') {
  try {
    temp = JSON.parse(temp)
    store.state.username = temp
  } catch (error) {
    console.log(error)
  }
}
import ToggleButton from 'vue-js-toggle-button'
Vue.use(ToggleButton)

// Some middleware to help us ensure the user is authenticated.
router.beforeEach((to, from, next) => {
  // window.console.log('Transition', transition)

  // if (to.auth && (to.router.app.$store.state.username === 'null')) {
  //   window
  //     .console
  //     .log('Not authenticated')
  //   next({
  //     path: '/login',
  //     query: {
  //       redirect: to.fullPath
  //     }
  //   })
  // else if (to.path === '/') {
  //   next({
  //     path: 'realtime',
  //     query: {
  //       redirect: to.fullPath
  //     }
  //   })
  // }
  console.log(store.state.username)
  console.log(to.path)
  if (to.meta.auth === true) {
    if (to.path !== '/login') {
      if (store.state.username !== '') {
        next()
      } else {
        next({
          path: '/login',
          query: {
            redirect: to.fullPath
          }
        })
      }
    }
  } else {
    next()
    // next({
    //   path: '/login',
    //   query: {
    //     redirect: to.fullPath
    //   }
    // })
  }
})

sync(store, router)

// Start out app!
// eslint-disable-next-line no-new
new Vue({
  el: '#root',
  router: router,
  store: store,
  render: h => h(AppView)
})

// Check local storage to handle refreshes
if (window.localStorage) {
  var localUserString = window
    .localStorage
    .getItem('user') || 'null'
  var localUser = JSON.parse(localUserString)

  if (localUser && store.state.user !== localUser) {
    store.commit('SET_USER', localUser)
    store.commit('SET_TOKEN', window.localStorage.getItem('token'))
  }
}

// cokkie
// var jsonAuth = {
//   username: 'edot92',
//   nama_lengkap: 'edy prasetiyo',
//   role: 'admin'
// }
// var storageCokie = Cookies.noConflict()

