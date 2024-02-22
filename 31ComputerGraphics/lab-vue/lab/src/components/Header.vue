<template>
  <div class="">
    <div class="row d-flex justify-content-center" style="height: 60px; width: 800px;">
      <div class="col align-self-center" style="max-width: 343px;">
        <div class="btn btn-custom d-inline-flex align-items-center" @click="this.$emit('switchTo', 'Головна')">
          <i class="fa fa-chevron-left left-arrow"></i>
          <span style="margin-right: auto; font-size: 22px;">Повернутись</span>
        </div>
      </div>
      <div class="col d-flex" style="max-width: 30px;">
        <div class="vr" style="height: 100%; width: 3px; border: none; background-color: #bebebe;"></div>
      </div>
      <div class="col d-flex align-self-center">
        <span class="title align-self-center">{{ title }}</span>
        <i class="question fa fa-question" style="margin-left: auto;" @click="isHelp=!isHelp"></i>
      </div>
      <div class="row">
        <hr style="min-width: 800px; height: 3px; border: none; background-color: #bebebe;">
      </div>
    </div>
    <div v-if="isHelp" class="row" style="z-index: 10; position: absolute; left: 12px; top: 63px; width: 800px; background-color: white;">
      <span style="margin: 13px;">{{ help }}</span>
      <div class="row">
        <hr style="min-width: 800px; height: 3px; border: none; background-color: #bebebe;">
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'HeaderBar',
  props: {
    title: String,
    help: String,
  },
  data() {
    return {
      isHelp: false,
    }
  }
};
</script>

<style scoped>
.btn-custom {
  border: none;
  width: 343px;
  height: 60px;
}
.title {
  font-size: 30px;

}
.question {
  font-size: 32px;
  color: #aaaaaa;
  margin-right: -5px;
  border-radius: 32px;
  background-color: #ebebeb;
  padding: 10px;
}
.left-arrow {
  color: #bebebe;
  font-size: 32px;
  margin-right: auto;
}
</style>
  