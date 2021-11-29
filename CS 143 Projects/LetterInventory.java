//Alexander Tran
//10-7-21
//TA: Arjun Singla
//The LetterInventory class represents the collection of case insensitive letters in a string
public class LetterInventory {
   private int[] letterCounts; //Array that stores the counts of each letter
   private int size;           //Int that holds the total number of letters
   
   public static final int ALPHABET_LENGTH = 26;
      
   //@post: creates an empty Letter Inventory
   public LetterInventory() {
      this("");
   }
   
 /* 
  *@param data: the string to be turned into a Letter Inventory
  *@post: creates a Letter Inventory to count the number of appearances of each letter
  *@post: will ignore any non alphabetic characters and is case insensitive
  */
   public LetterInventory(String data) {
      letterCounts = new int[ALPHABET_LENGTH];
      data = data.toLowerCase();
      for (int i = 0; i < data.length(); i++) {
         char currChar = data.charAt(i);
         if (currChar >= 'a' && currChar <= 'z') {
            letterCounts[currChar - 'a']++;
            size++;
         }
      }
   }
   
  /*   
   *@param letter: the case insensitive char that the count will be returned for
   *@pre: letter needs to be an alphabetic character
   *@throws: will throw IllegalArgumentException if letter is not an alphabetic character
   *@post: returns the number of appearances of the letter in the Letter Inventory
   */
   public int get(char letter) {
      letter = Character.toLowerCase(letter);
      if (letter < 'a' || letter > 'z') {
         throw new IllegalArgumentException();
      }
      return letterCounts[letter - 'a'];
   }
   
 /*
  *@param letter: the case insensitive char that the count will be changed for
  *@param value: the int of the new character count
  *@pre: letter needs to be an alphabetic character and value needs to be positive
  *@throws: will throw IllegalArgumentExecption if letter is not an alphabetic character
                                                  or if value is negative
  *@post: sets the number of appearances of the letter to the given value
  */
   public void set(char letter, int value) {
      letter = Character.toLowerCase(letter);
      if (letter < 'a' || letter > 'z' || value < 0) {
         throw new IllegalArgumentException();
      }
      int oldValue = letterCounts[letter - 'a'];
      letterCounts[letter - 'a'] = value;
      size += value - oldValue;   
   }
   
   //@post: returns the size of the Letter Inventory
   public int size() {
      return size;
   }
   
   //@post: returns whether or not the size is 0
   public boolean isEmpty() {
      return size == 0;
   }
   
   //@post: returns a string with the current inventory of letters
   public String toString() {
      String output = "[";
      for (int i = 0; i < ALPHABET_LENGTH; i++) {
         char currChar = (char) (i + 'a');
         for (int j = 0; j < letterCounts[i]; j++) {
            output += currChar;
         }
      }
      output += "]";
      return output;
   }
   
   /*
   @param other: the other Letter Inventory to be added
   @post: returns a new Letter Inventory with the sum of the two letter counts
   */
   public LetterInventory add(LetterInventory other) {
      LetterInventory inventorySum = new LetterInventory();
      for (int i = 0; i < ALPHABET_LENGTH; i++) {
         inventorySum.set((char) (i + 'a'), this.letterCounts[i] + other.letterCounts[i]);
      }
      return inventorySum;
   }
   
 /*
  *@param other: the other Letter Inventory to be subtracted
  *@post: returns the new Letter Inventory with the difference of the two letter counts
  *@return: null if the other inventory has any higher character counts
  */
   public LetterInventory subtract(LetterInventory other) {
      LetterInventory inventoryDif = new LetterInventory();
      for (int i = 0; i < ALPHABET_LENGTH; i++) {
         if (this.letterCounts[i] - other.letterCounts[i] < 0) {
            return null;
         }
         inventoryDif.set((char) (i + 'a'), this.letterCounts[i] - other.letterCounts[i]);
      }
      return inventoryDif;
   }
}