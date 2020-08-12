<template>
  <v-form>
    <v-container fluid>
      <v-row>
        <v-col cols="12" sm="6" md="6">
          <v-text-field
            v-model="item.device"
            :error-messages="deviceErrors"
            :label="$t('device')"
            @input="$v.item.device.$touch()"
            @blur="$v.item.device.$touch()"
          />
        </v-col>
      
        <v-col cols="12" sm="6" md="6">
          <v-text-field
            v-model="item.type"
            :error-messages="typeErrors"
            :label="$t('type')"
            @input="$v.item.type.$touch()"
            @blur="$v.item.type.$touch()"
          />
        </v-col>
      </v-row>
      
      <v-row>
        <v-col cols="12" sm="6" md="6">
          <v-text-field
            v-model.number="item.value"
            :error-messages="valueErrors"
            :label="$t('value')"
            step="0.1"
            @input="$v.item.value.$touch()"
            @blur="$v.item.value.$touch()"
          />
        </v-col>
      
        <v-col cols="12" sm="6" md="6">
          <v-text-field
            v-model.number="item.value"
            :error-messages="valueErrors"
            :label="$t('value')"
            step="0.1"
            @input="$v.item.value.$touch()"
            @blur="$v.item.value.$touch()"
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
  name: 'EventForm',
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
        device: null,
        type: null,
        value: null,
        value: null,
    };
  },
  computed: {

    // eslint-disable-next-line
    item() {
      return this.initialValues || this.values;
    },

    deviceErrors() {
      const errors = [];

      if (!this.$v.item.device.$dirty) return errors;

      has(this.violations, 'device') && errors.push(this.violations.device);


      return errors;
    },
    typeErrors() {
      const errors = [];

      if (!this.$v.item.type.$dirty) return errors;

      has(this.violations, 'type') && errors.push(this.violations.type);


      return errors;
    },
    valueErrors() {
      const errors = [];

      if (!this.$v.item.value.$dirty) return errors;

      has(this.violations, 'value') && errors.push(this.violations.value);


      return errors;
    },
    valueErrors() {
      const errors = [];

      if (!this.$v.item.value.$dirty) return errors;

      has(this.violations, 'value') && errors.push(this.violations.value);


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
      device: {
      },
      type: {
      },
      value: {
      },
      value: {
      },
    }
  }
};
</script>
