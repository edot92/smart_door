import DashView from './components/Dash.vue'
import LoginView from './components/Login.vue'
import NotFoundView from './components/404.vue'

// Import Views - Dash
// import DashboardView from './components/views/Dashboard.vue'
// import TablesView from './components/views/Tables.vue'
// import TasksView from './components/views/Tasks.vue'
// import SettingView from './components/views/Setting.vue'
// import AccessView from './components/views/Access.vue'
// import ServerView from './components/views/Server.vue'
// import ReposView from './components/views/Repos.vue'
//
// import Inputtahananbaru from './components/views/auth/Inputtahananbaru.vue'
// import Remisitahanan from './components/views/auth/Remisitahanan.vue'
// import Pencariantahanan from './components/views/auth/Pencariantahanan.vue'
// import Settingreminder from './components/views/auth/Settingreminder'
import HistoryPages from './components/views/smartdoor/History'
import RealtimePages from './components/views/smartdoor/Realtime'
import Email from './components/views/smartdoor/Email'
import User from './components/views/smartdoor/User'

// Routes
const routes = [
  {
    path: '/login',
    component: LoginView
  },
  {
    path: '/',
    component: DashView,
    children: [
      // {
      //   path: '',
      //   component: RealtimePages,
      //   name: 'Realtime',
      //   meta: { description: 'Halaman Realtime' }
      // },
      {
        path: 'history',
        component: HistoryPages,
        name: 'History',
        meta: { description: 'Halaman History', auth: true }
      },
      {
        path: 'realtime',
        component: RealtimePages,
        name: 'Realtime',
        meta: {
          description: 'Halaman Realtime', auth: true
        }
      },
      {
        path: 'email',
        component: Email,
        name: 'Email',
        meta: { description: '', auth: true }
      }, {
        path: 'user',
        component: User,
        name: 'user',
        meta: { description: '', auth: true }
      }

      // {
      //   path: 'inputtahananbaru',
      //   component: Inputtahananbaru,
      //   name: 'Inputtahananbaru',
      //   meta: { description: 'Overview of Inputtahananbaru' }
      // },
      // {
      //   path: 'potongremisitahanan',
      //   component: Remisitahanan,
      //   name: 'Potongremisitahanan',
      //   meta: { description: 'Overview of Remisitahanan' }
      // },
      // {
      //   path: 'pencariantahanan',
      //   component: Pencariantahanan,
      //   name: 'Pencariantahanan',
      //   meta: { description: 'Overview of Pencariantahanan' }
      // },
      // {
      //   path: 'settingreminder',
      //   component: Settingreminder,
      //   name: 'Settingreminder',
      //   meta: { description: 'Overview of Pencariantahanan' }
      // },
      // {
      //   path: 'dashboard',
      //   alias: '',
      //   component: DashboardView,
      //   name: 'Dashboard',
      //   meta: {description: 'Overview of environment'}
      // }, {
      //   path: 'tables',
      //   component: TablesView,
      //   name: 'Tables',
      //   meta: {description: 'Simple and advance table in CoPilot'}
      // }, {
      //   path: 'tasks',
      //   component: TasksView,
      //   name: 'Tasks',
      //   meta: {description: 'Tasks page in the form of a timeline'}
      // }, {
      //   path: 'setting',
      //   component: SettingView,
      //   name: 'Settings',
      //   meta: {description: 'User settings page'}
      // }, {
      //   path: 'access',
      //   component: AccessView,
      //   name: 'Access',
      //   meta: {description: 'Example of using maps'}
      // }, {
      //   path: 'server',
      //   component: ServerView,
      //   name: 'Servers',
      //   meta: {description: 'List of our servers'}
      // }, {
      //   path: 'repos',
      //   component: ReposView,
      //   name: 'Repository',
      //   meta: {description: 'List of popular javascript repos'}
      // }
    ]
  }, {
    // not found handler
    path: '*',
    component: NotFoundView
  }
]

export default routes
