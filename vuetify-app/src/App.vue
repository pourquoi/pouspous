<template>
    <v-app id="inspire">
        <snackbar></snackbar>

        <v-app-bar app color="primary" dark>
            <router-link
                :to="{name: 'Dashboard'}"
                v-slot="{ navigate }"
            >
                <v-toolbar-title @click="navigate">{{ title }}</v-toolbar-title>
            </router-link>

            <v-spacer></v-spacer>

            <router-link
                :to="{name: 'Dashboard'}"
                v-slot="{ navigate }"
            >
            <v-btn icon v-if="authenticated" @click="navigate">
                <v-icon>fa-tachometer-alt</v-icon>
            </v-btn>
            </router-link>

            <router-link
                :to="{name: 'Settings'}"
                v-slot="{ navigate }"
            >
            <v-btn icon v-if="authenticated" @click="navigate">
                <v-icon>fa-cog</v-icon>
            </v-btn>
            </router-link>

            <v-btn icon v-if="authenticated" @click="onLogout">
                <v-icon>fa-sign-out-alt</v-icon>
            </v-btn>
        </v-app-bar>

        <v-main>
            <router-view></router-view>
        </v-main>
    </v-app>
</template>

<script>
import { mapGetters, mapState, mapActions } from "vuex";
import Snackbar from "./components/Snackbar";

export default {
    components: {
        Snackbar,
    },

    data: () => ({
        drawer: false,
    }),

    created() {
        if (!this.authenticated) this.drawer = false;
    },

    computed: {
        ...mapGetters("user", ["authenticated"]),
        ...mapState("user", ["device"]),
        title() {
            if( !this.authenticated ) return 'PousPous';

            return 'PousPous - #' + this.device.name;
        }
    },

    methods: {
        ...mapActions("user", ["logout"]),
        onLogout() {
            this.logout().then(() => {
                this.$router.push({name: "Login"})
            })
        }
    }
};
</script>