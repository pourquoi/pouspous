<template>
    <v-card class="mr-6 mb-6">
        <v-list-item two-line>
            <v-list-item-content>
                <v-list-item-title class="headline">{{ card.name }}</v-list-item-title>
                <v-list-item-subtitle>Mon, 12:30 PM, Mostly sunny</v-list-item-subtitle>
            </v-list-item-content>
        </v-list-item>

        <v-card-text v-if="display">
            <apexchart width="400" :type="type" :options="options" :series="series"></apexchart>
        </v-card-text>

        <v-card-text v-else>
            <v-radio-group
                :row="false"
                @change="onSelectDisplay"
            >
                <v-radio v-for="display in displays" :key="display" :label="display" :value="display"></v-radio>
            </v-radio-group>
        </v-card-text>
    </v-card>
</template>

<script>
import * as moment from "moment";
import { mapActions } from "vuex";

export default {
    props: ["card"],
    data() {
        return {
            displays: ["on/off", "line", "bar"],
        };
    },
    computed: {
        display() {
            return this.card.display ? this.card.display : null
        },
        type: function () {
            if (this.card.display == "on/off") {
                return "scatter";
            } else if (this.card.display == "bar") {
                return "bar";
            }

            return "line";
        },
        options: function () {
            let options = {
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
        series: function () {
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
        onSelectDisplay(e) {
            this.updateDisplay({...this.card, display: e})
                .then( () => {
                    
                })
        }
    }
};
</script>