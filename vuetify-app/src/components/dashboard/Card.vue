<template>
    <v-card class="mr-6 mb-6">
        <v-list-item two-line>
            <v-list-item-content>
                <v-list-item-title class="headline">{{ card.name }}</v-list-item-title>
                <v-list-item-subtitle>Mon, 12:30 PM, Mostly sunny</v-list-item-subtitle>
            </v-list-item-content>
        </v-list-item>

        <v-card-text>

            <apexchart width="400" type="line" :options="options" :series="series"></apexchart>

        </v-card-text>
    </v-card>
</template>

<script>

import * as moment from "moment";

export default {
    props: ["card"],
    computed: {
        options: () => {
            return {
                xaxis: {
                    type: "datetime"
                },
                stroke: {
                    curve: 'stepline',
                },
                markers: {
                    size: [6, 0],
                },
                fill: {
                    type: "solid"
                }
            }
        },
        series: function() {
            if (this.card && this.card.events) {
                let series = [{
                    name: this.card.name,
                    type: 'scatter',

                    data: this.card.events.map(event => {
                        let p = {
                            x: moment(event.created_at).valueOf(),
                            y: event.value
                        }
                        return p;
                    })}
                ];

                console.log(series);

                return series;
            } else {
                return {data:[]}
            }
        }
    }
}
</script>