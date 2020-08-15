<template>
    <v-card class="mr-6 mb-6">
        <v-toolbar flat>
            <v-toolbar-title>{{ card.name }}</v-toolbar-title>
            <v-spacer></v-spacer>
            <v-btn color="grey" icon @click="hide">
                <v-icon>fa-eye-slash</v-icon>
            </v-btn>
            <v-btn icon v-if="configured" @click="toggleSettings">
                <v-icon>fa-cog</v-icon>
            </v-btn>
        </v-toolbar>

        <v-card-text v-if="show_chart">
            <apexchart
                width="400"
                :type="chart_type"
                :options="chart_options"
                :series="chart_series"
            ></apexchart>
        </v-card-text>

        <v-card-text v-if="show_settings">
            <v-radio-group :row="true" v-model="settings.display" label="Display mode">
                <v-radio
                    v-for="display in displays"
                    :key="display"
                    :label="display"
                    :value="display"
                ></v-radio>
            </v-radio-group>
        </v-card-text>

        <v-card-actions v-if="show_settings">
            <v-spacer />
            <v-btn color="primary" @click="saveSettings">Save</v-btn>
        </v-card-actions>
    </v-card>
</template>

<script>
import * as moment from "moment";
import { mapActions } from "vuex";

export default {
    components: {},
    props: {
        card: {
            type: Object,
            required: true,
        },
    },
    data() {
        return {
            show_settings: false,
            displays: ["on/off", "line", "bar"],
            settings: {},
        };
    },
    created() {
        this.show_settings = !this.card.display;
        this.initSettings();
    },
    computed: {
        configured() {
            return !!this.card.display;
        },
        show_chart() {
            return (
                !this.show_settings &&
                this.configured &&
                ["bar", "line"].indexOf(this.card.display) != -1
            );
        },
        chart_type() {
            return this.card.display;
        },
        chart_options: function () {
            let options = {
                chart: {
                    toolbar: {
                        show: false,
                    },
                },
                xaxis: {
                    type: "datetime",
                    labels: {
                        datetimeUTC: false,
                    },
                },
            };

            if (this.card.display == "on/off") {
                options.yaxis = {
                    tickAmount: 2,
                    labels: {
                        formatter: (val) => {
                            return val == "1" ? "on" : val == 0 ? "off" : "";
                        },
                    },
                };
            }

            return options;
        },
        chart_series: function () {
            if (this.card && this.card.events) {
                let series = [
                    {
                        name: this.card.name,

                        data: this.card.events.map((event) => {
                            let p = {
                                x: moment(event.created_at).valueOf(),
                                y: event.value,
                            };
                            return p;
                        }),
                    },
                ];

                return series;
            } else {
                return { data: [] };
            }
        },
    },
    methods: {
        ...mapActions("dashboard", ["updateDisplay"]),
        initSettings() {
            this.settings = {
                display: this.card.display,
            };
        },
        toggleSettings() {
            this.initSettings();
            this.show_settings = !this.show_settings;
        },
        saveSettings() {
            this.$emit("update:card", {
                ...this.card,
                display: this.settings.display,
            });

            this.toggleSettings();
        },
        hide() {
            this.$emit("update:card", { ...this.card, display: "hidden" });
        },
    },
};
</script>