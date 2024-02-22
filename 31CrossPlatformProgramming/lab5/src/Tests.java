import org.junit.Test;

import java.util.ArrayList;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class Tests {
    @Test
    public void testFindWordsWithTargetLetter() {
        String text1 = "This text is a sample text. It to contains words with target letters.";
        char targetLetter1 = 't';
        ArrayList<String> result1 = Main.findWordsWithTargetLetter(text1, targetLetter1);
        assertEquals(2, result1.size());
        assertTrue(result1.contains("text"));
        assertTrue(result1.contains("to"));

        String text2 = "";
        char targetLetter2 = 'a';
        ArrayList<String> result2 = Main.findWordsWithTargetLetter(text2, targetLetter2);
        assertTrue(result2.isEmpty());

        String text3 = "No words in this text have the target letter.";
        char targetLetter3 = 'z';
        ArrayList<String> result3 = Main.findWordsWithTargetLetter(text3, targetLetter3);
        assertTrue(result3.isEmpty());

        String text4 = "This TEXT is a case-sensitive test.";
        char targetLetter4 = 'T';
        ArrayList<String> result4 = Main.findWordsWithTargetLetter(text4, targetLetter4);
        assertEquals(1, result4.size());
        assertTrue(result4.contains("TEXT"));

        String text5 = "A t.";
        char targetLetter5 = 't';
        ArrayList<String> result5 = Main.findWordsWithTargetLetter(text5, targetLetter5);
        assertTrue(result5.isEmpty());
    }

    @Test
    public void testFindUniqueWordsInQuestions() {
        // Test case 1: Basic scenario
        String text1 = "What is the capital of Franc? Who wrote Hamlet?";
        int wordLength1 = 5;
        ArrayList<String> result1 = Main.findUniqueWordsInQuestions(text1, wordLength1);
        assertEquals(2, result1.size());
        assertTrue(result1.contains("Franc"));
        assertTrue(result1.contains("wrote"));

        // Test case 2: Empty text
        String text2 = "";
        int wordLength2 = 3;
        ArrayList<String> result2 = Main.findUniqueWordsInQuestions(text2, wordLength2);
        assertTrue(result2.isEmpty());

        // Test case 3: No questions
        String text3 = "This is a statement. So is this.";
        int wordLength3 = 5;
        ArrayList<String> result3 = Main.findUniqueWordsInQuestions(text3, wordLength3);
        assertTrue(result3.isEmpty());

        // Test case 4: Case sensitivity
        String text4 = "What is the meaning of life?";
        int wordLength4 = 4;
        ArrayList<String> result4 = Main.findUniqueWordsInQuestions(text4, wordLength4);
        assertEquals(2, result4.size());
        assertTrue(result4.contains("What"));
        assertTrue(result4.contains("lifessssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss"));

        // Test case 5: Words with one character should be ignored
        String text5 = "Is Java fun?";
        int wordLength5 = 1;
        ArrayList<String> result5 = Main.findUniqueWordsInQuestions(text5, wordLength5);
        assertTrue(result5.isEmpty());
    }
}
