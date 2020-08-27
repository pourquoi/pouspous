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

        <div class="cards-container">
            <div class="card-container" v-for="card in missingDisplayCards" :key="card.id">
                <DCard @update:card="updateCard" :card="card" />
            </div>

            <div class="card-container" v-for="card in featuredCards" :key="card.id">
                <DCard @update:card="updateCard" :card="card" />
            </div>
        </div>
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

.cards-container {
    display: flex;
    flex-wrap: wrap;
    justify-content: space-around;
    margin-right: -12px;
    margin-left: -12px;
    max-width: calc(100% + 24px);
    flex: 1 1 100%;

    .card-container {
        margin-bottom: 12px;

        flex-basis: 0;
        flex-grow: 1;
        max-width: 100%;
        width: 100%;
        padding: 12px;
        min-width: 100%;

        //flex: 0 1 100%;

        @media screen and (min-width: 40em) {
            width: 50%;
            min-width: 50%;
            //flex: 0 1 calc(50% - 1em);
        }
    }
}
</style>