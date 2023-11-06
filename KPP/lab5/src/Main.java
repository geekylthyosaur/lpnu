import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        String text = "This is a comprehensive test text that covers various aspects of language processing. It includes multiple sentences with different structures. Some sentences end with periods, others with question marks, and a few with exclamation marks! The text also contains questions that require answers. For instance, 'What is the meaning of life?' is one such question. It's an intriguing question, isn't it? This text aims to challenge your language processing capabilities. You'll find words starting with 'c' and in the second position of sentences. Additionally, you need to identify unique words of a specific length in the questions. This is a test, and the results will be interesting.";
        char targetLetter = 'i';
        int targetWordLength = 5;

        ArrayList<String> wordsWithTargetLetter = findWordsWithTargetLetter(text, targetLetter);
        ArrayList<String> uniqueWordsInQuestions = findUniqueWordsInQuestions(text, targetWordLength);

        System.out.println("Words with target letter: " + wordsWithTargetLetter);
        System.out.println("Unique words in questions: " + uniqueWordsInQuestions);
    }

    public static ArrayList<String> findWordsWithTargetLetter(String text, char targetLetter) {
        ArrayList<String> result = new ArrayList<>();
        Pattern pattern = Pattern.compile("(?:^|[.!?])\\s*(\\w+)\\w+\\s(?<word>" + targetLetter + "\\w*)[^.!?]*");
        Matcher matcher = pattern.matcher(text);

        while (matcher.find()) {
            String word = matcher.group("word");
            if (word.length() > 1 && word.toLowerCase().charAt(0) == Character.toLowerCase(targetLetter)) {
                result.add(word);
            }
        }

        return result;
    }

    public static ArrayList<String> findUniqueWordsInQuestions(String text, int wordLength) {
        ArrayList<String> result = new ArrayList<>();
        Pattern pattern = Pattern.compile("(?=\\b[^.!?]+[?]+)(?<word>\\w{" + wordLength + "})");
        Matcher matcher = pattern.matcher(text);

        while (matcher.find()) {
            String word = matcher.group("word");
            if (word.length() > 1) {
                result.add(word);
            }
        }

        return result;
    }
}
