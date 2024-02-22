import org.junit.Test;

import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        String text = "This is a broad trial text that spans various facets of linguistic handling. It holds multiple lines with varied setups. Some lines end with periods, others with query marks, and a few with exclamatory marks! The text also poses queries that seek replies. For example, 'What is the essence of life?' is one such query. It's a puzzling query, isn't it? This text strives to test your linguistic grasp abilities. You'll spot terms initiating with 'c' and in the second slot of sentences. Furthermore, you must pinpoint exclusive terms of a fixed length in the queries? This is a trial, and the yields will be intriguing.";
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
        Pattern pattern = Pattern.compile("(?=\\b[^.!?]+[?]+)(?<word>\\b\\w{" + wordLength + "}\\b)");
        Matcher matcher = pattern.matcher(text);

        while (matcher.find()) {
            String word = matcher.group("word");
            if (word.length() > 1 && !result.contains(word)) {
                result.add(word);
            }
        }

        return result;
    }
}
