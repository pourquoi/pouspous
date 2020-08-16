<template>
    <v-container class="fill-height" fluid>
        <v-speed-dial
            v-model="fab"
            bottom
            right
            direction="top"
            absolute
            transition="slide-y-reverse-transition"
        >
            <template v-slot:activator>
                <v-btn v-model="fab" color="primary" dark fab>
                    <v-icon v-if="fab">mdi-close</v-icon>
                    <v-icon v-else>mdi-plus</v-icon>
                </v-btn>
            </template>
            <v-btn
                fab
                dark
                small
                color="primary"
                class="add-event-btn"
                v-for="card in hiddenCards"
                :key="card.id"
                @click="showCard(card)"
            >{{ card.name }}</v-btn>
        </v-speed-dial>

        <v-row v-if="missingDisplayCards.length">
            <v-col cols="12">
                <v-row align="center" justify="center" class="grey lighten-5 pa-10">
                    <DCard
                        v-for="card in missingDisplayCards"
                        @update:card="updateCard"
                        :key="card.id"
                        :card="card"
                    />
                </v-row>
            </v-col>
        </v-row>

        <v-row>
            <v-col cols="12">
                <v-row align="center" justify="center" class="pa-10">
                    <DCard
                        v-for="card in featuredCards"
                        @update:card="updateCard"
                        :key="card.id"
                        :card="card"
                    />
                </v-row>
            </v-col>
        </v-row>
    </v-container>
</template>

<script>
import { mapActions, mapState, mapGetters } from "vuex";

import DCard from "@/components/dashboard/Card";

export default {
    components: {
        DCard,
    },
    data() {
        return {
            fab: false,
        };
    },
    computed: {
        ...mapState("dashboard", ["cards"]),
        ...mapGetters("dashboard", [
            "featuredCards",
            "missingDisplayCards",
            "hiddenCards",
        ]),
    },
    mounted() {
        this.load();
    },
    methods: {
        ...mapActions("dashboard", ["load", "updateCard"]),
        showCard(card) {
            this.updateCard({ ...card, display: null });
        },
    },
};
</script>

<style lang="scss">
.add-event-btn {
    .v-btn__content {
        color: black;
    }
}
</style>