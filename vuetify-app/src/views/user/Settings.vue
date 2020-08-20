<template>
    <v-container class="fill-height" fluid>

        <v-row align="center" justify="center">
            <SettingCard :setting="new_setting" @update:setting="create" @remove="deleteItem" />
        </v-row>

        <v-row>
            <v-col cols="12">
                <v-row align="center" justify="center" class="" v-for="(setting, idx) in items" :key="setting.id">

                    <SettingCard :setting="setting" @update:setting="update" @remove="deleteItem" />

                </v-row>
            </v-col>
        </v-row>

    </v-container>
</template>
        
<script>
import { mapState, mapGetters, mapActions } from 'vuex';
import SettingCard from '@/components/setting/Card';

export default {
    data() {
        return {
            new_setting: {}
        }
    },
    components: {
        SettingCard
    },
    computed: {
        ...mapGetters('settings', {
            items: 'list'
        }),
        ...mapState('user', ['device'])
    },
    created() {
        this.getPage()
    },
    methods: {
        ...mapActions('settings', {
            getPage: 'fetchAll',
            deleteItem: 'del',
            retrieve: 'load',
            update: 'update',
            createItem: 'create'
        }),
        create(setting) {
            this.createItem({device: this.device.name, ...setting}).then(() => {
                this.new_setting = {}
            })
        }
    }
};
</script>
        
<style>
</style>