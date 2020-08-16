<template>
    <v-container
        class="fill-height"
        fluid
      >
        <v-row
          align="center"
          justify="center"
        >
          <v-col
            cols="12"
            sm="8"
            md="4"
          >
            <v-card class="elevation-12">
              <v-toolbar
                color="primary"
                dark
                flat
              >
                <v-toolbar-title>Login</v-toolbar-title>
                <v-spacer></v-spacer>
                <v-tooltip bottom>
                  <template v-slot:activator="{ on }">
                    <v-btn
                      icon
                      large
                      target="_blank"
                      v-on="on"
                    >
                      <v-icon>fa-question-circle</v-icon>
                    </v-btn>
                  </template>
                  <span>This is the name you put in the arduino code</span>
                </v-tooltip>
              </v-toolbar>
              <v-card-text>
                <v-form @submit.prevent="submit">
                  <v-text-field
                    v-model="device"
                    label="Station"
                    name="station"
                    prepend-icon="fa-microchip"
                    type="text"
                    :error-messages="errors"
                    @input="$v.device.$touch()"
                    @blur="$v.device.$touch()"
                  ></v-text-field>

                </v-form>
              </v-card-text>
              <v-card-actions>
                <v-spacer></v-spacer>
                <v-btn color="primary" :disabled="isLoading" @click="submit">Login</v-btn>
              </v-card-actions>
            </v-card>
          </v-col>
        </v-row>
      </v-container>
</template>

<script>
import { mapActions, mapState } from "vuex";
import { mapFields } from "vuex-map-fields";
import { validationMixin } from 'vuelidate';
import { required, maxLength, email } from 'vuelidate/lib/validators'

export default {
    mixins: [validationMixin],
    data() {
        return {
            device: ''
        }
    },
    validations: {
        device: { required },
    },
    computed: {
        ...mapFields('user', {
            isLoading: 'isLoading',
            error: 'error'
        }),
        errors() {
            const errors = [];

            if (!this.$v.device.$dirty) return errors

            if(this.error) errors.push(this.error)

            return errors;
        }
    },
    methods: {
        ...mapActions("user", ["login"]),
        submit() {
            this.$v.$touch()
            this.login(this.device)
                .then(() => {
                    if (!this.$v.$invalid) {
                        this.$router.push({name: "Dashboard"});
                    }
                })
        }
    }
}
</script>