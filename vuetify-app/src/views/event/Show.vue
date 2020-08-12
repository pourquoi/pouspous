<template>
  <div>
    <Toolbar :handle-delete="del">
      <template slot="left">
        <v-toolbar-title v-if="item">{{
          `${$options.servicePrefix} ${item['@id']}`
        }}</v-toolbar-title>
      </template>
    </Toolbar>

    <br />

    <div v-if="item" class="table-event-show">
      <v-simple-table>
        <template slot="default">
          <thead>
            <tr>
              <th>Field</th>
              <th>Value</th>

              <th>Field</th>
              <th>Value</th>
            </tr>
          </thead>
          <tbody>
            <tr>
              <td><strong>{{ $t('device') }}</strong></td>
              <td>
                                    {{ item['device'] }}
              </td>
            
              <td><strong>{{ $t('type') }}</strong></td>
              <td>
                                    {{ item['type'] }}
              </td>
            </tr>
            
            <tr>
              <td><strong>{{ $t('value') }}</strong></td>
              <td>
                {{ $n(item['value']) }}              </td>
            
              <td><strong>{{ $t('value') }}</strong></td>
              <td>
                {{ $n(item['value']) }}              </td>
            </tr>
            
            <tr>
              <td><strong>{{ $t('type') }}</strong></td>
              <td>
                                    {{ item['type'].name }}
              </td>
            
              <td><strong>{{ $t('created_at') }}</strong></td>
              <td>
                {{ formatDateTime(item['created_at'], 'long') }}              </td>
            </tr>
            
            <tr>
              <td><strong>{{ $t('updated_at') }}</strong></td>
              <td>
                {{ formatDateTime(item['updated_at'], 'long') }}              </td>
            
              <td></td>
            </tr>
            
          </tbody>
        </template>
      </v-simple-table>
    </div>

    <Loading :visible="isLoading" />
  </div>
</template>

<script>
import { mapActions, mapGetters } from 'vuex';
import { mapFields } from 'vuex-map-fields';
import Loading from '../../components/Loading';
import ShowMixin from '../../mixins/ShowMixin';
import Toolbar from '../../components/Toolbar';

const servicePrefix = 'Event';

export default {
  name: 'EventShow',
  servicePrefix,
  components: {
      Loading,
      Toolbar
  },
  mixins: [ShowMixin],
  computed: {
    ...mapFields('event', {
      isLoading: 'isLoading'
    }),
    ...mapGetters('event', ['find'])
  },
  methods: {
    ...mapActions('event', {
      deleteItem: 'del',
      reset: 'reset',
      retrieve: 'load'
    })
  }
};
</script>
