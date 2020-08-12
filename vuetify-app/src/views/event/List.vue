<template>
  <div class="event-list">
    <Toolbar :handle-add="addHandler" />

    <v-container grid-list-xl fluid>
      <v-layout row wrap>
        <v-flex sm12>
          <h1>Event List</h1>
        </v-flex>
        <v-flex lg12>
          <DataFilter :handle-filter="onSendFilter" :handle-reset="resetFilter">
            <EventFilterForm
              ref="filterForm"
              :values="filters"
              slot="filter"
            />
          </DataFilter>

          <br />

          <v-data-table
            v-model="selected"
            :headers="headers"
            :items="items"
            :items-per-page.sync="options.itemsPerPage"
            :loading="isLoading"
            :loading-text="$t('Loading...')"
            :options.sync="options"
            :server-items-length="totalItems"
            class="elevation-1"
            item-key="@id"
            show-select
            @update:options="onUpdateOptions"
          >
                <template slot="item.value" slot-scope="{ item }">
                  {{ $n(item['value']) }}
                </template>
                <template slot="item.value" slot-scope="{ item }">
                  {{ $n(item['value']) }}
                </template>
                <template slot="item.created_at" slot-scope="{ item }">
                  {{ formatDateTime(item['created_at'], 'long') }}
                </template>
                <template slot="item.updated_at" slot-scope="{ item }">
                  {{ formatDateTime(item['updated_at'], 'long') }}
                </template>

            <ActionCell
              slot="item.action"
              slot-scope="props"
              :handle-show="() => showHandler(props.item)"
              :handle-edit="() => editHandler(props.item)"
              :handle-delete="() => deleteHandler(props.item)"
            ></ActionCell>
          </v-data-table>
        </v-flex>
      </v-layout>
    </v-container>
  </div>
</template>

<script>
import { mapActions, mapGetters } from 'vuex';
import { mapFields } from 'vuex-map-fields';
import ListMixin from '../../mixins/ListMixin';
import ActionCell from '../../components/ActionCell';
import EventFilterForm from '../../components/event/Filter';
import DataFilter from '../../components/DataFilter';
import Toolbar from '../../components/Toolbar';

export default {
  name: 'EventList',
  servicePrefix: 'Event',
  mixins: [ListMixin],
  components: {
    Toolbar,
    ActionCell,
    EventFilterForm,
    DataFilter
  },
  data() {
    return {
      headers: [
        { text: 'device', value: 'device' },
        { text: 'type', value: 'type' },
        { text: 'value', value: 'value' },
        { text: 'value', value: 'value' },
        { text: 'type', value: 'type' },
        { text: 'created_at', value: 'created_at' },
        { text: 'updated_at', value: 'updated_at' },
        {
          text: 'Actions',
          value: 'action',
          sortable: false
        }
      ],
      selected: []
    };
  },
  computed: {
    ...mapGetters('event', {
      items: 'list'
    }),
    ...mapFields('event', {
      deletedItem: 'deleted',
      error: 'error',
      isLoading: 'isLoading',
      resetList: 'resetList',
      totalItems: 'totalItems',
      view: 'view'
    })
  },
  methods: {
    ...mapActions('event', {
      getPage: 'fetchAll',
      deleteItem: 'del'
    })
  }
};
</script>
