<template>
  <v-form>
    <v-container fluid>
      <v-row>
        <v-col cols="12" sm="6" md="6">
          <v-text-field
            v-model="item.name"
            :error-messages="nameErrors"
            :label="$t('name')"
            @input="$v.item.name.$touch()"
            @blur="$v.item.name.$touch()"
          />
        </v-col>
      
        <v-col cols="12" sm="6" md="6">
          <v-text-field
            v-model="item.label"
            :error-messages="labelErrors"
            :label="$t('label')"
            @input="$v.item.label.$touch()"
            @blur="$v.item.label.$touch()"
          />
        </v-col>
      </v-row>
      
    </v-container>
  </v-form>
</template>

<script>
import has from 'lodash/has';
import { validationMixin } from 'vuelidate';
import { required } from 'vuelidate/lib/validators';
import { mapActions } from 'vuex';
import { mapFields } from 'vuex-map-fields';

export default {
  name: 'EventTypeForm',
  mixins: [validationMixin],
  props: {
    values: {
      type: Object,
      required: true
    },

    errors: {
      type: Object,
      default: () => {}
    },

    initialValues: {
      type: Object,
      default: () => {}
    }
  },
  mounted() {
  },
  data() {
    return {
        name: null,
        label: null,
    };
  },
  computed: {

    // eslint-disable-next-line
    item() {
      return this.initialValues || this.values;
    },

    nameErrors() {
      const errors = [];

      if (!this.$v.item.name.$dirty) return errors;

      has(this.violations, 'name') && errors.push(this.violations.name);


      return errors;
    },
    labelErrors() {
      const errors = [];

      if (!this.$v.item.label.$dirty) return errors;

      has(this.violations, 'label') && errors.push(this.violations.label);


      return errors;
    },

    violations() {
      return this.errors || {};
    }
  },
  methods: {
  },
  validations: {
    item: {
      name: {
      },
      label: {
      },
    }
  }
};
</script>
