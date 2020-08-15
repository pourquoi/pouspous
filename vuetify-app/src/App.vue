<template>
    <v-app id="inspire">
        <snackbar></snackbar>

        <!--
        <v-navigation-drawer v-model="drawer" app>
            <v-list dense>
                
                <v-list-item v-if="authenticated">
                    <v-list-item-action>
                        <v-icon>fa-tachometer-alt</v-icon>
                    </v-list-item-action>
                    <v-list-item-content>
                        <v-list-item-title>Dashboard</v-list-item-title>
                    </v-list-item-content>
                </v-list-item>

                <v-list-item v-if="authenticated">
                    <v-list-item-action>
                        <v-icon>fa-sitemap</v-icon>
                    </v-list-item-action>
                    <v-list-item-content>
                        <v-list-item-title>
                            <router-link :to="{ name: 'EventTypeList' }">Events</router-link>
                        </v-list-item-title>
                    </v-list-item-content>
                </v-list-item>

                <v-divider></v-divider>

                <v-list-item v-if="!authenticated">
                    <v-list-item-action>
                        <v-icon>fa-login</v-icon>
                    </v-list-item-action>
                    <v-list-item-content>
                        <v-list-item-title>Login</v-list-item-title>
                    </v-list-item-content>
                </v-list-item>

                <v-list-item v-if="authenticated" @click.prevent="onLogout">
                    <v-list-item-action>
                        <v-icon>fa-sign-out-alt</v-icon>
                    </v-list-item-action>
                    <v-list-item-content>
                        <v-list-item-title>Logout</v-list-item-title>
                    </v-list-item-content>
                </v-list-item>

            </v-list>
        </v-navigation-drawer>

        -->

        <v-app-bar app color="indigo" dark>
            <!--
            <v-app-bar-nav-icon v-if="authenticated" @click.stop="drawer = !drawer"></v-app-bar-nav-icon>
            -->
            <v-toolbar-title>{{ title }}</v-toolbar-title>

            <v-spacer></v-spacer>

            <v-btn icon v-if="authenticated" @click="onLogout">
                <v-icon>fa-sign-out-alt</v-icon>
            </v-btn>
        </v-app-bar>

        <v-main>
            <!--
            <Breadcrumb layout-class="pl-3 py-3" />
            -->
            <router-view></router-view>
        </v-main>
        <!--
        <v-footer color="indigo" app>
            <span class="white--text">&copy; 2020</span>
        </v-footer>
        -->
    </v-app>
</template>

<script>
import { mapGetters, mapState, mapActions } from "vuex";
import Breadcrumb from "./components/Breadcrumb";
import Snackbar from "./components/Snackbar";

export default {
    components: {
        Breadcrumb,
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