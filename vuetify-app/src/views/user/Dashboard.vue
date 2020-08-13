<template>
    <v-container class="fill-height" fluid>

        <DCard v-for="card in cards" :key="card.id" :card="card" />

    </v-container>
</template>

<script>
import { mapActions, mapState } from "vuex";

import DCard from "@/components/dashboard/Card"

export default {
    components: {
        DCard
    },
    computed: {
        ...mapState("dashboard", ["cards"]),
    },
    mounted() {
        this.load();
    },
    methods: {
        ...mapActions("dashboard", ["load"]),
    },
};
</script>