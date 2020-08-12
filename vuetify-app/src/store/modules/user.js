import {getField, updateField} from 'vuex-map-fields';
import deviceService from '../../services/device';
import fetch from '../../utils/fetch';

const state = {
    device: null
}

const getters = {
    authenticated(state) {
        return !!state.device;
    },
    getField
}

const mutations = {
    updateField
}

const actions = {
    login({commit}, device) {
        fetch('devices', {params: {name: device}})
            .then(response => response.json())
            .then(retrieved => {
                if (retrieved['hydra:totalItems'] == 1) {
                    commit('updateField', {path: 'device', value: retrieved['hydra:member'][0]});
                } else {
                    throw "device not found";
                }
            })
            .catch(e => {
                console.log(e)
            });
    },
    logout({commit}) {
        commit('updateField', {path: 'device', value: null});
    }
}

export default {
    namespaced: true,
    getters,
    state,
    mutations,
    actions
}