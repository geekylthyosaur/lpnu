<template>
  <div class="d-flex" style="height: 540px; width: 800px;">
    <div class="col" style="max-width: 343px;">
      <div class="row d-flex justify-content-center">
        <div class="btn btn-custom d-inline-flex align-items-center" @click="changeTheme(1)">
          Фрактали
          <i class="fa fa-chevron-right right-arrow"></i>
        </div>
        <div class="btn btn-custom d-inline-flex align-items-center" @click="changeTheme(2)">
          Колірні моделі
          <i class="fa fa-chevron-right right-arrow"></i>
        </div>
        <div class="btn btn-custom d-inline-flex align-items-center" @click="changeTheme(3)">
          Афінні перетворення
          <i class="fa fa-chevron-right right-arrow"></i>
        </div>
      </div>
    </div>
    <div class="vr align-self-center" style="height: 100%; width: 3px; border: none; background-color: #bebebe;"></div>
    <div class="col align-self-center">
      <div class="row d-flex justify-content-center">
        <div class="" style="width: 400px; height: 400px;">
          <span style="font-size: 24px;">{{ currentQuestion }}</span>
          <div v-for="(answer, index) in currentAnswers" :key="index">
            <label class="answer-label"  @click="selectAnswer(index)">
              <input type="radio" :value="index">
              <span :class="answer.status" class="radio-button"></span>
              <span>
                {{ answer.t }}
              </span>
            </label>
          </div>
        </div>
      </div>
      <div class="row d-flex justify-content-center" v-if="currTheme>0">
        <div class="btn btn-switch btn-prev" @click="prev">
          <i class="fa fa-arrow-left icon-prev"></i>
        </div>
        <div class="btn btn-switch btn-next" @click="next">
          <i class="fa fa-arrow-right icon-next"></i>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  name: 'TestsA',
  data() {
    return {
      currTab: 0,
      currTest: 0,
      currTheme: 0,
      quizData: {
        1: [
            {
                q: 'Що таке фрактал?',
                a: [
                    { t: 'Математична множина з повторюваним візерунком', isCorrect: true, status: 'none' },
                    { t: 'Тип овоча', isCorrect: false, status: 'none' },
                    { t: 'Нова мова програмування', isCorrect: false, status: 'none' },
                    { t: 'Вид птаха', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Як називається фрактал, який часто порівнюють із "відбитками Бога"?',
                a: [
                    { t: 'Множина Мандельброта', isCorrect: true, status: 'none' },
                    { t: 'Крива Коха', isCorrect: false, status: 'none' },
                    { t: 'Трикутник Сєрпінського', isCorrect: false, status: 'none' },
                    { t: 'Множина Жуліа', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Хто ввів термін "фрактал" в математику?',
                a: [
                    { t: 'Ісаак Ньютон', isCorrect: false, status: 'none' },
                    { t: 'Бенуа Мандельброт', isCorrect: true, status: 'none' },
                    { t: 'Пєр Ферма', isCorrect: false, status: 'none' },
                    { t: 'Софія Ковалевськая', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Що визначає фрактальна розмірність?',
                a: [
                    { t: 'Кількість пікселів у зображенні', isCorrect: false, status: 'none' },
                    { t: 'Складність форми, яка змінюється з масштабом', isCorrect: true, status: 'none' },
                    { t: 'Кількість кольорів у зображенні', isCorrect: false, status: 'none' },
                    { t: 'Глибина зображення', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Яка галузь науки вивчає фрактали?',
                a: [
                    { t: 'Астрономія', isCorrect: false, status: 'none' },
                    { t: 'Екологія', isCorrect: false, status: 'none' },
                    { t: 'Фракталометрія', isCorrect: true, status: 'none' },
                    { t: 'Психологія', isCorrect: false, status: 'none' },
                ],
            },
        ],
        2: [
            {
                q: 'Яка основна модель кольорів, яка використовується у друці?',
                a: [
                    { t: 'RGB', isCorrect: false, status: 'none' },
                    { t: 'CMYK', isCorrect: true, status: 'none' },
                    { t: 'HSV', isCorrect: false, status: 'none' },
                    { t: 'HSL', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Що означає абревіатура "RGB" у моделі кольорів?',
                a: [
                    { t: 'Різні гамми червоного', isCorrect: false, status: 'none' },
                    { t: 'Реальний гамма-вектор', isCorrect: false, status: 'none' },
                    { t: 'Червоний, Зелений, Синій', isCorrect: true, status: 'none' },
                    { t: 'Розширені гамми відтінків', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Що представляє собою модель кольорів CMYK?',
                a: [
                    { t: 'Кольоровий колесо', isCorrect: false, status: 'none' },
                    { t: 'Кількість пікселів на екрані', isCorrect: false, status: 'none' },
                    { t: 'Червоний, Зелений, Синій, Жовтий', isCorrect: false, status: 'none' },
                    { t: 'Відтінки ціану, магенти, жовтого та чорного', isCorrect: true, status: 'none' },
                ],
            },
            {
                q: 'Що визначає параметр "яскравість" у моделі кольорів HSV?',
                a: [
                    { t: 'Інтенсивність кольору', isCorrect: false, status: 'none' },
                    { t: 'Ступінь насиченості', isCorrect: false, status: 'none' },
                    { t: 'Кількість відтінків', isCorrect: false, status: 'none' },
                    { t: 'Світлоту кольору', isCorrect: true, status: 'none' },
                ],
            },
            {
                q: 'Які основні компоненти моделі кольорів HSL?',
                a: [
                    { t: 'Червоний, синій, жовтий', isCorrect: false, status: 'none' },
                    { t: 'Відтінок, Насиченість, Легкість', isCorrect: true, status: 'none' },
                    { t: 'Гамма, Спектр, Вектор', isCorrect: false, status: 'none' },
                    { t: 'Синій, жовтий, чорний', isCorrect: false, status: 'none' },
                ],
            },
        ],
        3: [
            {
                q: 'Що таке афінні перетворення?',
                a: [
                    { t: 'Перетворення, які зберігають колінеарність та відношення відстаней', isCorrect: true, status: 'none' },
                    { t: 'Тип танцю', isCorrect: false, status: 'none' },
                    { t: 'Техніка приготування їжі', isCorrect: false, status: 'none' },
                    { t: 'Давньомовна', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Які афінні перетворення використовуються в графіці?',
                a: [
                    { t: 'Зсув', isCorrect: true, status: 'none' },
                    { t: 'Поворот', isCorrect: true, status: 'none' },
                    { t: 'Масштабування', isCorrect: true, status: 'none' },
                    { t: 'Зеркальне відображення', isCorrect: true, status: 'none' },
                ],
            },
            {
                q: 'Яке афінне перетворення змінює розміри об\'єкта, але не змінює його форму?',
                a: [
                    { t: 'Поворот', isCorrect: false, status: 'none' },
                    { t: 'Зсув', isCorrect: false, status: 'none' },
                    { t: 'Масштабування', isCorrect: true, status: 'none' },
                    { t: 'Зеркальне відображення', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Що таке матриця афінного перетворення?',
                a: [
                    { t: 'Матриця, що визначає відтінок кольору', isCorrect: false, status: 'none' },
                    { t: 'Матриця, яка визначає відстані між об\'єктами', isCorrect: false, status: 'none' },
                    { t: 'Матриця, яка представляє комбінацію зсуву, повороту і масштабування', isCorrect: true, status: 'none' },
                    { t: 'Матриця, яка визначає кут нахилу об\'єкта', isCorrect: false, status: 'none' },
                ],
            },
            {
                q: 'Які властивості зберігаються при афінних перетвореннях?',
                a: [
                    { t: 'Площа', isCorrect: false, status: 'none' },
                    { t: 'Форма', isCorrect: true, status: 'none' },
                    { t: 'Колінеарність', isCorrect: true, status: 'none' },
                    { t: 'Орієнтація', isCorrect: false, status: 'none' },
                ],
            },
        ],
    },
    };
  },
  computed: {
    currentQuestion() {
      return this.quizData[this.currTheme] ? this.quizData[this.currTheme][this.currTest].q : '';
    },
    currentAnswers() {
      return this.quizData[this.currTheme] ? this.quizData[this.currTheme][this.currTest].a : [];
    },
  },
  mounted() {
    this.$emit('help', 'Переконайтеся, що обираєте тему тесту, яка вам на даний момент потрібна або яка вас цікавить найбільше. Це дозволить вам систематизувати свої знання. Перед тим, як обирати відповідь, уважно прочитайте питання та всі варіанти відповідей. Це допоможе уникнути непорозумінь та забезпечить точність результатів.');
  },
  methods: {
    changeTheme(theme) {
      this.currTheme = theme;
      this.currTest = 0;
    },
    selectAnswer(index) {
      this.currentAnswers.forEach(answer => {
        answer.status = 'none';
      });

      const selectedAnswer = this.currentAnswers[index];
      selectedAnswer.status = selectedAnswer.isCorrect ? 'correct' : 'incorrect';
    },
    prev() {
      if (this.currTest > 0) {
        this.currTest--;
      }
    },
    next() {
      if (this.currTest < this.quizData[this.currTheme].length - 1) {
        this.currTest++;
      }
    },
  },
  
};
</script>

<style scoped>
.btn-playpause {
  width: 60px;
  height: 45px;
  background-color: #ebebeb;
  border: 3px solid #ebebeb;
  border-radius: 12px;
  font-size: 28px;
  margin-top: 13px;
}
.correct {
  background-color: #8bc34a;
}
.incorrect {
  background-color: #ff5252;
}
.answer-label {
  display: flex;
  align-items: center;
  margin-bottom: 10px;
}

.radio-button {
  min-width: 20px;
  min-height: 20px;
  border-radius: 50%;
  border: 2px solid #bebebe;
  margin-right: 10px;
  display: inline-block;
  vertical-align: middle;
}
input[type="radio"] {
  display: none;
}

.right-arrow {
  color: #bebebe;
  font-size: 32px;
  margin-left: auto;
}
.btn-custom {
  font-size: 22px;
  margin-top: 13px;
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
.btn-switch {
  width: 60px;
  height: 45px;
  background-color: #ebebeb;
  border: 3px solid #ebebeb;
  border-radius: 0;
  margin-top: 13px;
}
.btn-next {
  margin-right: auto;
  border-top-right-radius: 12px;
  border-bottom-right-radius: 12px;
}
.btn-prev {
  margin-left: auto;
  border-top-left-radius: 12px;
  border-bottom-left-radius: 12px;
}
.btn-zoom:active {
  background-color: #ebebeb;
  border: 3px solid #bebebe;
}
.icon-next, .icon-prev {
  font-size: 28px;
}

.btn-custom-i {
  font-size: 22px;
  margin-bottom: 13px;
  border-radius: 24px;
  height: 56px;
  width: 306px;
  background-color: #bebebe; 
  background-image: linear-gradient(to right, #ebebeb 85%, rgba(0,0,0,0) 20%); 
  border: 3px solid #ebebeb;
}
.btn-i:active {
  border: 3px solid #bebebe;
  background-color: #bebebe;
  background-image: linear-gradient(to right, #ebebeb 85%, rgba(0,0,0,0) 20%); 
}
</style>
