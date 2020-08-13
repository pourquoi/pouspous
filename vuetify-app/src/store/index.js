import Vue from 'vue';
import Vuex from 'vuex';
import makeCrudModule from './modules/crud';
import notifications from './modules/notifications';
import deviceService from '../services/device';
import eventTypeService from '../services/eventtype';
import eventService from '../services/event';
import userStore from './modules/user';
import dashboardStore from './modules/dashboard';

Vue.use(Vuex);

const store = new Vuex.Store({
  modules: {
    notifications,
    user: userStore,
    dashboard: dashboardStore,
    device: makeCrudModule({
      service: deviceService
    }),
    event: makeCrudModule({
      service: eventService
    }),
    eventtype: makeCrudModule({
        service: eventTypeService
    }),
  },
  strict: process.env.NODE_ENV !== 'production'
});

export default store;