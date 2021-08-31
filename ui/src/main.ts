import { createApp, InjectionKey } from 'vue'
import { createStore, Store, useStore as baseUseStore } from 'vuex'
import App from './App.vue'
import '@/assets/styles/styles.scss'

interface Color {
  r: Number;
  g: Number;
  b: Number;
}

export interface State {
  text: String,
  textColors: Array<Color>
}

export const key: InjectionKey<Store<State>> = Symbol()

export function useStore() {
  return baseUseStore(key);
}

const store = createStore({
  state () {
    return {
      text: '',
      textColors: []
    }
  },
  mutations: {
    set_text(state : State, newState : State)
    {
      state.text = newState.text;
      state.textColors = newState.textColors;
    }
  },
  getters: {
    text(state : State) { return state.text; },
    textColors(state : State) { return state.textColors; }
  }
})

const app = createApp(App);
app.use(store, key).mount('#app');

// @ts-ignore
app.config.globalProperties.$OnInputEvent = (inputData: any) => { window.OnInputEvent(inputData) };
