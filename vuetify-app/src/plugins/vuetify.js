import '@fortawesome/fontawesome-free/css/all.css';
import Vue from 'vue';
import Vuetify from 'vuetify/lib';

Vue.use(Vuetify);

const opts = {
    icons: {
        iconfont: 'fa'
    },
    theme: {
        themes: {
            light: {
                primary: '#8ac926',
                secondary: '#1982c4',
                accent: '#6a4c93',
                error: '#ff595e',
            },
            dark: {
                primary: '#8ac926',
            }
        },
    },
};

export default new Vuetify(opts);