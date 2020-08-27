<template>
    <v-container class="fill-height" fluid>
        <div class="cards-container">
            <div class="card-container" v-for="(setting, idx) in items" :key="setting.id">
                <SettingCard :setting="setting" @update:setting="update" @remove="deleteItem" />
            </div>
        </div>

        <v-row align="center" justify="end">
            <v-col>
                <SettingCard :setting="new_setting" @update:setting="create" @remove="deleteItem" />
            </v-col>
        </v-row>

        <v-snackbar v-model="snackbar" top right light>
            {{ snackbar_text }}
            <template v-slot:action="{ attrs }">
                <v-btn color="grey" text v-bind="attrs" @click="snackbar = false">Close</v-btn>
            </template>
        </v-snackbar>
    </v-container>
</template>
        
<script>
import { mapState, mapGetters, mapActions } from "vuex";
import SettingCard from "@/components/setting/Card";

export default {
    data() {
        return {
            new_setting: {},
            snackbar: false,
            snackbar_text: "",
        };
    },
    components: {
        SettingCard,
    },
    computed: {
        ...mapGetters("settings", {
            items: "list",
        }),
        ...mapState("user", ["device"]),
    },
    created() {
        this.getPage();
    },
    methods: {
        ...mapActions("settings", {
            getPage: "fetchAll",
            deleteItem: "del",
            retrieve: "load",
            updateItem: "update",
            createItem: "create",
        }),
        update(item) {
            this.updateItem(item).then(() => {
                this.snackbar = true;
                this.snackbar_text = "Setting updated";
            });
        },
        create(setting) {
            this.createItem({ device: this.device.name, ...setting }).then(
                () => {
                    this.new_setting = {};
                    this.snackbar = true;
                    this.snackbar_text = "New setting created";
                }
            );
        },
    },
};
</script>
        
<style>
</style>