import Vue from 'vue';
import Vuelidate from 'vuelidate';
import App from './App.vue';
import vuetify from './plugins/vuetify';
import VueApexCharts from 'vue-apexcharts'

import store from './store';
import router from './router';
import i18n from './i18n';

Vue.config.productionTip = false;

Vue.use(Vuelidate);

Vue.component('apexchart', VueApexCharts)

new Vue({
  i18n,
  router,
  store,
  vuetify,
  render: h => h(App)
}).$mount('#app');