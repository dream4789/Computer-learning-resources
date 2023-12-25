import Vue from 'vue';
import Vuex from 'vuex';
import Student from './modules/student';
import Teacher from './modules/teacher';
 
Vue.use(Vuex);
 
export default new Vuex.Store({
    modules: {
        Student,
        Teacher
    }
});