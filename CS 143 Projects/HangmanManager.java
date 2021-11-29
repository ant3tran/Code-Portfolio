//Alexander Tran
//10-28-21
//TA: Arjun Singla
//The HangmanManager class simulates a game of evil hangman

import java.util.*;
public class HangmanManager {
   private int numGuesses;         //int that holds the current number of guesses left
   private Set<String> currSet;    //set of strings that holds the current set of possible words
   private Set<Character> guesses; //set of chars that holds all the previous guesses
   private String pattern;         //string that holds the current pattern of the possible words

/*
 *@param dictionary: the list of all possible initial words
 *@param length: the length of the target word
 *@param max: the maximum number of guesses
 *@throws: will throw IllegalArgumentExecption if length is less than 1 or if max is negative
 *@post: initializes the base pattern and the number of guesses
 *@post: creates the set of possible words that are the correct length, ignoring duplicates
 */
   public HangmanManager(Collection<String> dictionary, int length, int max) {
      if(length < 1 || max < 0) {
         throw new IllegalArgumentException();
      }
      numGuesses = max;
      guesses = new TreeSet<Character>();
      currSet = new TreeSet<String>();
      for(String currWord : dictionary) {
         if(currWord.length() == length) {
            currSet.add(currWord);  
         }
      }
      pattern = "-";
      for(int i = 1; i < length; i++) {
         pattern += " -";
      }
   }
   
   //@post: returns the current set of possible words
   public Set<String> words() {
      return currSet;
   }
   
   //@post: returns the number of guesses left
   public int guessesLeft() {
      return numGuesses;   
   }
   
   //@post: returns the set of all previous guesses
   public Set<Character> guesses() {
      return guesses;
   }
   /*
   @throws: will throw an IllegalStateException if the set of possible words is empty
   @post: returns the current pattern of possible words
   */
   public String pattern() {
      if(currSet.isEmpty()){
         throw new IllegalStateException();
      }
      return pattern;
   }
   /*
    *@param guess: the char that has been guessed
    *@pre: guess is a lowercase letter
    *@throws 1: will throw an IllegalStateException if the number of guesses left is less than 1
    *@throws 1: will throw an IllegalStateException if the set of possible words is empty
    *@throws 2: will throw an IllegalArgumentException if a guess is repeated
    *@post: chooses the largest set of possible words that allign with the guess as the new set
    *@post: updates the pattern to reflect the new pattern and updates the number of guesses
    *@post: returns the number of appearances of the guess in the updated pattern

   */
   public int record(char guess) {
      if(numGuesses < 1 || currSet.isEmpty()){
         throw new IllegalStateException();
      }
      if(guesses.contains(guess)) {
         throw new IllegalArgumentException();
      }
      String key = "";
      Map<String, Set<String>> currMap = new TreeMap<String, Set<String>>();
      guesses.add(guess);
      for(String currWord : currSet) {
         key = pattern;
         for(int i = 0; i < currWord.length(); i++) {
            if(currWord.charAt(i) == guess) {
               key = key.substring(0, 2 * i) + guess + key.substring(2 * i + 1);
            }
         }
         if(!currMap.containsKey(key)){
            currMap.put(key, new TreeSet<String>());
         }
         currMap.get(key).add(currWord);
      }
      return generateLargestSet(currMap, guess);
   }
   /*
    *@Helper Method
    *@param currMap: the map of all possible words and their respective patterns
    *@param guess: the char that has been guessed
    *@post: finds the largest set of possible words from the map
    *@post: properly decrements the number of guesses and updates the pattern
    *@post: returns the number of appearances of the guess in the updated pattern
    */
   public int generateLargestSet(Map<String, Set<String>> currMap, char guess){
      String maxKey = "";
      int max = 0;
      for(String currKey : currMap.keySet()){
         if(currMap.get(currKey).size() > max) {
            maxKey = currKey;
            max = currMap.get(currKey).size();
            pattern = currKey;
         }
      }
      int count = 0;
      for(int i = 0; i < pattern.length(); i++) {
         if(pattern.charAt(i) == guess) {
            count++;
         }
      }
      if(count == 0) {
         numGuesses--;
      }
      currSet = currMap.get(maxKey);
      return count;
   }
}