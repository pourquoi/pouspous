import {getField, updateField} from 'vuex-map-fields';
import deviceService from '../../services/device';
import fetch from '../../utils/fetch';
import storage from '../../utils/storage';

const STORAGE_KEY = 'user';

const state = {
    device: null,
    error: null,
    isLoading: false
}

function loadFromStorage(state) {
    const savedState = storage.load(STORAGE_KEY)
    if (savedState) {
        state.device = savedState.device;
    }
}

function saveToStorage(state) {
    storage.save(STORAGE_KEY, {
        device: state.device
    });
}

loadFromStorage(state);

const getters = {
    authenticated(state) {
        return !!state.device;
    },
    getField
}

const mutations = {
    setDevice(state, device) {
        state.device = device;

        saveToStorage(state);
    },
    updateField
}

const actions = {
    login({commit}, device) {

        commit('updateField', {path: 'error', value: null});
        commit('updateField', {path: 'isLoading', value: true});

        return fetch('devices', {params: {name: device}})
            .then(response => response.json())
            .then(retrieved => {
                if (retrieved['hydra:totalItems'] == 1) {
                    commit('setDevice', retrieved['hydra:member'][0]);
                } else {
                    commit('updateField', {path: 'error', value: "Device not found"});
                }
                commit('updateField', {path: 'isLoading', value: false});
            })
            .catch(e => {
                console.log(e)
                commit('updateField', {path: 'isLoading', value: false});
            });
    },
    logout({commit}) {
        commit('setDevice', null);

        return Promise.resolve(true);
    }
}

export default {
    namespaced: true,
    getters,
    state,
    mutations,
    actions
}