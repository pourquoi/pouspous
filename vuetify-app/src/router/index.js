import Vue from 'vue';
import VueRouter from 'vue-router';
import deviceRoutes from './device';
import eventTypeRoutes from './eventtype';
import eventRoutes from './event';

import Dashboard from '../views/user/Dashboard';
import Login from '../views/user/Login';

import store from "@/store";

Vue.use(VueRouter);

let router = new VueRouter({
    mode: 'history',
    routes: [
        {
            path: '',
            name: 'Dashboard',
            component: Dashboard,
            meta: {
                authRequired: true
            }
        },
        {
            path: '/login',
            name: 'Login',
            component: Login
        },
        deviceRoutes,
        eventTypeRoutes,
        eventRoutes
    ]
});


router.beforeEach((to, from, next) => {
    if (to.matched.some(record => record.meta.authRequired)) {
        if (store.getters["user/authenticated"]) {
            next();
        } else {
            console.log(store.state.user.device);
            console.log(store.getters["user/authenticated"]);
            console.log("user not authenticated for route", to);
            next({
                name: "Login",
                query: { redirect: to.fullPath }
            });
        }
    } else {
        next();
    }
});

export default router;