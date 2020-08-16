import { getField, updateField } from 'vuex-map-fields';

import eventTypeService from '../../services/eventtype';
import eventService from '../../services/event';

import * as moment from "moment";

function parseEvent(data, card) {
    return data
}

export default {
    namespaced: true,
    state: {
        cards: [],
    },
    getters: {
        getField,
        missingDisplayCards(state) {
            return state.cards.filter(c => c.display === null)
        },
        featuredCards(state) {
            return state.cards.filter(c => c.display && c.display !== "hidden")
        },
        hiddenCards(state) {
            return state.cards.filter(c => c.display === "hidden")
        }
    },
    mutations: {
        updateField,
        updateCard(state, card) {
            let idx = state.cards.findIndex(c => c.id == card.id);
            if (idx != -1) {
                state.cards[idx] = Object.assign(state.cards[idx], card);
            }
        }
    },
    actions: {
        load({ state, commit, dispatch }, params) {

            eventTypeService
                .findAll({ params })
                .then(response => response.json())
                .then(retrieved => {
                    let types = retrieved['hydra:member'];

                    types.forEach(type => {
                        type._loading = false;
                        if (!("display" in type))
                            type.display = null;
                        type.events = [];
                    })

                    commit('updateField', { path: 'cards', value: types });

                    dispatch('loadCardsContent');

                })
                .catch(e => { console.log(e) });

        },
        updateCard({ state, commit }, data) {
            commit('updateCard', data)

            return eventTypeService.patch(data['@id'], data)
                .then(response => {
                    return response.json()
                })
                .catch(e => { console.log(e) });
        },
        loadCardsContent({ state, commit, dispatch }) {
            state.cards.forEach((card) => {
                dispatch('loadCardContent', card.id)
            })
        },
        loadCardContent({ state, commit }, id) {
            let card = state.cards.find(c => c.id == id);
            if (card) {
                eventService
                    .findAll({ params: { 'type.name': card.name, 'order[id]': 'desc' } })
                    .then(response => response.json())
                    .then(retrieved => {
                        let events = retrieved['hydra:member'].map(function(event) {
                            return parseEvent(event, card)
                        }).sort((a, b) => {
                            return moment(a.created_at).isAfter(b.created_at) ? -1 : 1;
                        });
                        commit('updateCard', { id: card.id, events: events })
                    })
                    .catch(e => { console.log(e) });
            }
        }
    }
};
