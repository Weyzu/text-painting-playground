<template>
  <div>
  <div
    class="custom-textarea"
    ref="root"
    contenteditable=true
    @input="handleInput"
  >
  </div>
  <br>
  <h5>Output</h5>
  <div 
    ref="subRoot" 
    style="white-space: pre-wrap"
  >
    <span 
        v-for="(character, index) in text"
        :key="character"
        v-bind:style="{ 'color': `rgb(${ textColors[index].r }, ${ textColors[index].g }, ${ textColors[index].b })`}"
    >
        {{ character }}
    </span>
  </div>
  </div>
</template>

<script lang='ts'>
import {
  defineComponent,
  ref,
} from 'vue'
import { useStore } from '../main'
import { mapGetters } from 'vuex'

export default defineComponent({
  name: 'CustomInput',
  inheritAttrs: false,
  emits: ['input'],
  computed: mapGetters(['text', 'textColors']),

  setup(_, { emit }) {
    const root = ref(null);
    const subRoot = ref(null);
    const store = useStore();

    const handleInput = (event: Event) => {
        // @ts-ignore
        OnInputEvent(root.value.innerText);
    }

    return {
      root,
      subRoot,
      handleInput
    }
  },
})

</script>

<style scoped>
.custom-textarea {
  -webkit-appearance: textarea;
  border-top: 1px solid rgb(0, 0, 0);
  border-bottom: 1px solid rgb(0, 0, 0);
  border-left: 1px solid rgb(0, 0, 0);
  border-right: 1px solid rgb(0, 0, 0);
  background-color: #2b2b2b;
  width: 100%;
  height: 130px;
  cursor: auto;
  writing-mode: horizontal-tb;
}
</style>