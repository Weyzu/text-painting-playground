<template>
  <div style="padding: 50px 50px;">
    <h5>Input some text here️</h5>
    <CustomInput/>
  </div>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import CustomInput from "@/components/CustomInput.vue"

export default defineComponent({
  components: {
    CustomInput
  },
  setup() {
    return {};
  }
});
</script>

<style lang="scss">
#app {
  font-family: "Helvetica Neue", Helvetica, "PingFang SC", "Hiragino Sans GB",
    "Microsoft YaHei", "微软雅黑", Arial, sans-serif;
  color: #a7a8a9;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}

h5 {
  font-size: 12px;
  line-height: 16px;
  font-weight: 600;
  text-transform: uppercase;
  color: #8f9297;
  margin: 0px;
  margin-top: 10px;
  margin-bottom: 10px;
}

</style>
