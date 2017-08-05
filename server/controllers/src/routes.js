import DashView from './components/Dash.vue'
// import LoginView from './components/Login.vue'
import NotFoundView from './components/404.vue'
import Pendaftaranpasien from './components/views/umjrs/Pendaftaranpasien'
import Riwayatpasien from './components/views/umjrs/Riwayatpasien'
import Realtimesensor from './components/views/umjrs/Realtimesensor'
import Recordsetting from './components/views/umjrs/Recordsetting'

// Routes
const routes = [

  //
  // {
  //   path: '/login',
  //   component: LoginView
  // },
  {
    path: '/',
    component: DashView,
    children: [

      {
        path: 'pendaftaranpasien',
        component: Pendaftaranpasien,
        name: 'Pendaftaranpasien',
        meta: { description: '' }
      }, {
        path: 'riwayatpasien',
        component: Riwayatpasien,
        name: 'Riwayatpasien',
        meta: { description: '' }
      }, {
        path: 'realtimesensor',
        component: Realtimesensor,
        name: 'Realtimesensor',
        meta: { description: '' }
      },
      {
        path: 'recordsetting',
        component: Recordsetting,
        name: 'Recordsetting',
        meta: { description: '' }
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
