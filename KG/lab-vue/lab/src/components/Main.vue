<template>
  <div class="d-flex" style="height: 600px; width: 800px;">
    <div class="col align-self-center" style="max-width: 343px;">
      <div class="row d-flex justify-content-center">
        <div class="btn btn-custom d-inline-flex align-items-center" :class="{ active: showPopup }" @click="showPopup = !showPopup">
          Фрактали
          <i class="fa fa-chevron-right right-arrow" v-if="!showPopup"></i>
        </div>
        <div class="btn btn-custom d-inline-flex align-items-center" @click="this.$emit('switchTo', 'Колірні схеми')">
          Колірні схеми
          <i class="fa fa-chevron-right right-arrow"></i>
        </div>
        <div class="btn btn-custom d-inline-flex align-items-center" @click="this.$emit('switchTo', 'Рухомі зображення')">
          Рухомі зображення
          <i class="fa fa-chevron-right right-arrow"></i>
        </div>
        <hr style="width: 90%; height: 3px; border: none; background-color: #bebebe;">
        <div class="btn btn-custom d-inline-flex align-items-center" @click="this.$emit('switchTo', 'Матеріали')">
          Матеріали
          <i class="fa fa-chevron-right right-arrow"></i>
        </div>
        <div class="btn btn-custom d-inline-flex align-items-center" @click="this.$emit('switchTo', 'Опитувальник')">
          Опитувальник
          <i class="fa fa-chevron-right right-arrow"></i>
        </div>
      </div>
    </div>
    <div class="vr align-self-center" style="height: 100%; width: 3px; border: none; background-color: #bebebe;"></div>
    <div class="col align-self-center">
      <div class="row d-flex justify-content-center">
        <div class="text-center" style="font-size: 32px;">
          ABC
        </div>
      </div>
    </div>
    <div class="popup" v-if="showPopup">
      <div class="btn btn-custom d-inline-flex align-items-center" style="background-color: white;" @click="this.$emit('switchTo', 'Фрактал Мандельброта')">
        Фрактал Мандельброта
        <i class="fa fa-chevron-right right-arrow"></i>
      </div>
      <div class="btn btn-custom d-inline-flex align-items-center" style="background-color: white;margin-bottom:0px;" @click="this.$emit('switchTo', 'Броунівський рух')">
        Броунівський рух
        <i class="fa fa-chevron-right right-arrow"></i>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'MainWindow',
  data() {
    return {
      showPopup: false,
    };
  },
};
</script>

<style scoped>
.btn-custom {
  font-size: 22px;
  margin-bottom: 13px;
  border-radius: 24px;
  height: 56px;
  width: 306px;
  background-color: #ebebeb;
  border: 3px solid #ebebeb;
}
.btn:active {
  border: 3px solid #bebebe;
  background-color: #ebebeb;
}
.active {
  border: 3px solid #bebebe;
  background-color: #ebebeb;
}
.right-arrow {
  color: #bebebe;
  font-size: 32px;
  margin-left: auto;
}
.popup {
  position: absolute;
  top: 70px;
  right: 129px;
  width: 332px;
  background-color: #ebebeb;
  padding: 13px;
  border-radius: 24px;
}
.popup::before {
  content: '';
  position: absolute;
  top: 50%;
  right: 100%;
  transform: translateY(-50%);
  border: solid transparent;
  border-width: 8px;
  border-right-color: #ebebeb;
}
</style>
