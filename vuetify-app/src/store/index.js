import Vue from 'vue';
import Vuex from 'vuex';
import makeCrudModule from './modules/crud';
import notifications from './modules/notifications';
import deviceService from '../services/device';
import eventTypeService from '../services/eventtype';
import eventService from '../services/event';
import userStore from './modules/user';

Vue.use(Vuex);

const store = new Vuex.Store({
  modules: {
    notifications,
    user: userStore,
    device: makeCrudModule({
      service: deviceService
    }),
    event: makeCrudModule({
      service: eventService
    }),
    eventType: makeCrudModule({
        service: eventTypeService
    }),
  },
  strict: process.env.NODE_ENV !== 'production'
});

export default store;