<template>
  <div class="d-flex" style="height: 540px; width: 800px;">
    <div class="col" style="max-width: 343px;">
      <div class="row d-flex justify-content-center">
        <div class="btn btn-custom d-inline-flex align-items-center" @click="changeTheme(1)">
          Тема 1
          <i class="fa fa-chevron-right right-arrow"></i>
        </div>
        <!-- Add buttons for other themes as needed -->
      </div>
    </div>
    <div class="vr align-self-center" style="height: 100%; width: 3px; border: none; background-color: #bebebe;"></div>
    <div class="col align-self-center">
      <div v-if="currTest === 0">
        <p>Please select a theme to start the quiz.</p>
      </div>
      <div v-else>
        <h3>Quiz for Theme {{ currTheme }}</h3>
        <div v-for="(question, index) in quizData[currTheme]" :key="index">
          <p>{{ question.text }}</p>
          <div v-for="(option, optionIndex) in question.options" :key="optionIndex">
            <input type="radio" :id="`option-${index}-${optionIndex}`" :name="`question-${index}`" @change="selectAnswer(index, optionIndex)">
            <label :for="`option-${index}-${optionIndex}`">{{ option }}</label>
          </div>
        </div>
        <button @click="submitQuiz">Submit Quiz</button>
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
      currTheme: null,
      quizData: {
        1: [
          {
            text: 'What is the capital of France?',
            options: ['Paris', 'Berlin', 'London', 'Madrid'],
            correctAnswer: 0,
          },
          // Add more questions for Theme 1 as needed
        ],
        // Add more themes and questions as needed
      },
      userAnswers: [],
    };
  },
  mounted() {
    this.$emit('help', 'Переконайтеся, що обираєте тему тесту, яка вам на даний момент потрібна або яка вас цікавить найбільше. Це дозволить вам систематизувати свої знання. Перед тим, як обирати відповідь, уважно прочитайте питання та всі варіанти відповідей. Це допоможе уникнути непорозумінь та забезпечить точність результатів.');
  },
  methods: {
    changeTheme(theme) {
      this.currTheme = theme;
      this.currTest = 1; // Reset the quiz for the selected theme
      this.userAnswers = [];
    },
    selectAnswer(questionIndex, optionIndex) {
      this.$set(this.userAnswers, questionIndex, optionIndex);
    },
    submitQuiz() {
      // Process userAnswers array to check correctness and show results
      // You can implement this based on your specific requirements
      console.log('User Answers:', this.userAnswers);
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
.right-arrow {
  color: #bebebe;
  font-size: 32px;
  margin-left: auto;
}
.btn-custom {
  font-size: 22px;
  margin-bottom: 13px;
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
