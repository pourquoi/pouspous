<template>
    <v-card class="mr-6 mb-6 dashboard-card">
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
            <apexchart :type="chart_type" :height="chart_height" :options="chart_options" :series="chart_series"></apexchart>
        </v-card-text>

        <v-card-text v-if="show_settings">
            <v-radio-group :row="true" v-model="settings.display" label="Type">
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

// map from event type to apex chart type
const chartTypesMap = {
    bar: "bar",
    line: "line",
    "on/off": "rangeBar",
};

function getSerieValues(card) {
    if (["bar", "line"].indexOf(card.display) != -1) {
        return card.events.map((event) => ({
            x: moment(event.created_at).valueOf(),
            y: event.value,
        }));
    } else if (card.display == "on/off") {
        let data = [];
        let start = null;
        let end = null;
        card.events.slice().sort((a, b) => {
            return a.id < b.id ? -1 : 1;
        }).forEach((event, idx) => {
            if (event.value == 0 && start) {
                end = moment(event.created_at).valueOf();
            } else if (event.value == 1 && !start) {
                start = moment(event.created_at).valueOf();
            }

            if (!end && idx == card.events.length-1) {
                //end = new Date()
            }

            if (start && end) {
                /*
                if (data.length) {
                    data.push({
                        x: "off",
                        y: [data[data.length - 1].y[1], start],
                    });
                }
                */
                
                data.push({
                    x: "on",
                    y: [start, end],
                });
                start = end = null;
            }
        });

        return data;
    }
}

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
        chart_height() {
            return this.card.display == "on/off" ? 120 : 200;
        },
        show_chart() {
            return !this.show_settings && this.configured && this.chart_type;
        },
        chart_type() {
            return this.card.display in chartTypesMap
                ? chartTypesMap[this.card.display]
                : undefined;
        },
        chart_options: function () {
            let options = {
                colors:['#2c699a', '#048ba8', '#0db39e', '#16db93', '#83e377', '#b9e769', '#efea5a', '#f1c453', '#f29e4c'],
                chart: {
                    height: 200,
                    type: this.chart_type,
                    toolbar: {
                        show: true,
                    },
                },
                xaxis: {
                    type: "datetime",
                    labels: {
                        datetimeUTC: false,
                    },
                },

                tooltip: {
                    x: {
                        format: 'dd MM'
                    }
                }
            };

            if (this.card.display == "on/off") {

                options.tooltip.x.format = 'HH:mm:ss';
                
                Object.assign(options, {
                    plotOptions: {
                        bar: {
                            horizontal: true,
                            barHeight: '90%'
                        },
                    },
                    stroke: {
                        width: 5,
                    },
                    fill: {
                        type: "solid",
                        opacity: 0.6,
                    },
                });
            }

            /*
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
            */

            return options;
        },
        chart_series: function () {
            if (this.card && this.card.events) {
                let series = [
                    {
                        name: this.card.name,

                        data: getSerieValues(this.card),
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

<style scoped>
    .dashboard-card {
        width: 100%;
    }
</style>