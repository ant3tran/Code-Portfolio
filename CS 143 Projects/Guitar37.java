//Alexander Tran
//10-14-21
//TA: Arjun Singla
//The Guitar37 class models a 37 string guitar

import java.util.*;

public class Guitar37 implements Guitar {
   //GuitarString array that holds all the strings in the guitar
   private GuitarString[] strings; 
   //int that holds the number of times the guitar has been tic'ed
   private int numTics;

   public static final String KEYBOARD = 
      "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";  // keyboard layout
   public static final int STRING_COUNT = 37;
   
   //@post: creates a guitar with STRING_COUNT number of strings
   public Guitar37() {
      strings = new GuitarString[STRING_COUNT];
      numTics = 0;
      for(int i = 0; i < STRING_COUNT; i++) {
         double frequency = 440 * Math.pow(2, (i - 24) / 12.0);
         strings[i] = new GuitarString(frequency);
      }
   }
   
 /*
  *@param pitch: int that holds the pitch value to be played
  *@ignores: will ignore all invalid pitch values
  *@post: plucks the string that corresponds to the pitch value
  */
   public void playNote(int pitch) {
      int playPitch = pitch + 24;
      if(playPitch >= 0 && playPitch < STRING_COUNT) {
         strings[playPitch].pluck();
      }
   }
   
   //@param key: char that represents the input
   //@post: returns true if key is a designated key the guitar can play
   //@post: returns false if key is a key the guitar cannot play
   public boolean hasString(char key) {
      return KEYBOARD.indexOf(key) != -1;
   }
   
  /*
   *@pre: key must be a valid input on the keyboard
   *@param key: char that represents the string to be played
   *@throws: will throw IllegalArgumentException if the key is invalid  
   *@post: plucks the string that corresponds to the given key
   */
   public void pluck(char key) {
      if(!hasString(key)) {
         throw new IllegalArgumentException();
      }
      strings[KEYBOARD.indexOf(key)].pluck();
   }
   
   //@post: returns the sum of the samples from every string on the guitar
   public double sample() {
      double sum = 0;
      for(int i = 0; i < STRING_COUNT; i++) {
         sum += strings[i].sample();
      }
      return sum;
   }

   //@post: tic's every string on the guitar
   public void tic() {
      for(int i = 0; i < STRING_COUNT; i++) {
         strings[i].tic();
      }
      numTics++;
   }

   //@post: returns the number of times the guitar has been tic'ed
   public int time() {
      return numTics;
   }

}