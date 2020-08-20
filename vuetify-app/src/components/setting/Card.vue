<template>
    <v-card class="mr-6 mb-6 setting-card">
        <v-toolbar flat v-if="!is_new">
            <v-toolbar-title>{{ values.name }}</v-toolbar-title>
            <v-spacer></v-spacer>
            <v-btn color="grey" icon @click="remove">
                <v-icon>fa-trash</v-icon>
            </v-btn>
        </v-toolbar>

        <v-card-text>
            <v-row>
                <v-col cols="12">
                    <v-text-field v-if="is_new" v-model="values.name" label="Name"></v-text-field>
                    <v-text-field v-model.number="values.value" type="number" label="Value"></v-text-field>
                </v-col>
            </v-row>
        </v-card-text>

        <v-card-actions>
            <v-spacer />
            <v-btn color="secondary" @click="save">{{ is_new ? 'Add Setting' : 'Update' }}</v-btn>
        </v-card-actions>
    </v-card>
</template>

<script>
export default {
    props: {
        setting: {
            type: Object,
            required: true,
        },
    },
    data() {
        return {
            values: {}
        }
    },
    computed: {
        is_new() {
            return isNaN(this.setting.id);
        }
    },
    watch: {
        setting: {
            handler: function(val) {
                this.values = { ...val }
            },
            immediate: true
        }
    },
    methods: {
        save() {
            this.$emit('update:setting', this.values)
        },
        reset() {
            this.values = { ...this.setting }
        },
        remove() {
            this.$emit('remove', this.setting)
        }
    }
};
</script>