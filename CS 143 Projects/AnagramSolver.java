//Alexander Tran
//11-18-21
//TA: Arjun Singla
//The AnagramSolver will create anagrams for a given text based off a dictionary

import java.util.*;
public class AnagramSolver {
   //List of dictionary in the given order
   private List<String> dictOrder;
   //Map of the dictionary with each words letter inventory
   private Map<String, LetterInventory> dictMap;
   
  /*
   *@param dictionary: the list of all valid words
   *@post: creates a map with each valid word with its LetterInventory.
   *@post: keeps track of the original order of the dictionary
   */
   public AnagramSolver(List<String> dictionary) {
      dictMap = new HashMap<String, LetterInventory>();
      dictOrder = dictionary;
      for(String currWord : dictionary) {
         dictMap.put(currWord, new LetterInventory(currWord)); 
      }
   }
   
  /*
   *@param text: the text to find all the anagrams of
   *@param max: the max number of words allowed. No limit if max is 0
   *@throws: throws an IllegalArgumentException if max is negative 
   *@post: prints all the anagrams of the given text
   */
   public void print(String text, int max) {
      if(max < 0) {
         throw new IllegalArgumentException();
      }
      LetterInventory currInven = new LetterInventory(text);
      List<String> prunedDict = new ArrayList<String>();
      prune(currInven, prunedDict);
      print(prunedDict, currInven, new Stack<String>(), max);
   }
   
  /*
   *(Public/Private pair)
   *@param prunedDict: the ordered list of the elements of the dictionary
   *@param currInven: the current collection of letters to make an anagram
   *@param currOutput: the current collection of output words
   *@param max: the number of words left to produce
   *@post: prints all the anagrams of the given text
   */
   private void print(List<String> prunedDict, LetterInventory currInven, 
                      Stack<String> currOutput, int max) {
      if(currInven.isEmpty()) {
         System.out.println(currOutput);  
      } else if(max != currOutput.size() || max == 0){
         for(String currWord : prunedDict) {
            LetterInventory newInven = currInven.subtract(dictMap.get(currWord));
            if(newInven != null) {
               currOutput.push(currWord);                  
               print(prunedDict, newInven, currOutput, max);
               currOutput.pop();
            }
         }
      }  
   }

  /*
   *Helper Method
   *@param currInven: the current collection of letters to make an anagram
   *@param prunedDict: the ordered list of the elements of the dictionary
   *@post: prints all the anagrams of the given text
   */
   private void prune(LetterInventory currInven, List<String> prunedDict) {
      for(String currWord : dictOrder) {
         if(currInven.subtract(dictMap.get(currWord)) != null) {
            prunedDict.add(currWord);
         }
      }
   }
}