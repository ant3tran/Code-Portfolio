//Alexander Tran
//10-14-21
//TA: Arjun Singla
//The GuitarString class represents a vibrating guitar string and its ring buffer

import java.util.*;

public class GuitarString {
   private Queue<Double> ringBuffer; //queue that represents the ring buffer

   public static final double DECAY_FACTOR = 0.996;
   
  /*
   *@param frequency: double that holds the frequency of the guitar string
   *@throws: will throw IllegalArgumentException if length is less than 2
            or if frequency is not positive
   *@post: creates a ring buffer at rest from a given frequency
   */
   public GuitarString(double frequency) {
      int length = (int) (Math.round(StdAudio.SAMPLE_RATE / frequency));
      if(length < 2 || frequency <= 0) {
         throw new IllegalArgumentException();
      }
      ringBuffer = new LinkedList<Double>();
      for(int i = 0; i < length; i++) {
         ringBuffer.add(0.0);
      }
   }

   /*
   @param init: array of doubles that holds a predefined ring buffer
   @throws: will throw IllegalArgumentException if the length is less than 2
   @post: creates a ring buffer from predefined values
   */
   public GuitarString(double[] init) {
      int length = init.length;
      if(length < 2) {
         throw new IllegalArgumentException();
      }
      ringBuffer = new LinkedList<Double>();
      for(int i = 0; i < length; i++) {
         ringBuffer.add(init[i]);  
      }
   }
   
   //@post: replaces the ringBuffer with white noise random elements
   public void pluck() {
      for(int i = 0; i < ringBuffer.size(); i++) {
         ringBuffer.remove();
         ringBuffer.add(Math.random() - 0.5);
      }
   }

   /*
   @post: applies the Karplus-Strong algorithm
          adds the scaled average of the first two elements 
          removes the first element
   */
   public void tic() {
      double average = ringBuffer.remove();
      average = DECAY_FACTOR * (average + ringBuffer.peek()) / 2;
      ringBuffer.add(average);
   }
   
   //@post returns the current sample from the ring buffer
   public double sample() {
      return ringBuffer.peek();
   }
   
}