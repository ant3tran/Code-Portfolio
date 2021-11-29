//Alexander Tran
//10-21-21
//TA: Arjun Singla
//The AssassinManager class simulates the "Assassin" game 
//that keeps track of the killRing and graveyard

import java.util.*;

public class AssassinManager {
   private AssassinNode front;          //the current front of the killRing
   private AssassinNode graveyardFront; //the current front of the graveyard

   /*
    *@param names: the list of names to be turned into a kill ring
    *@throws: will throw an IllegalArgumentException if names is empty
    *@post: creates a kill ring out of the given names and preserves order
   */
   public AssassinManager(List<String> names) {
      if(names.size() == 0) {
         throw new IllegalArgumentException();
      }
      front = new AssassinNode(names.get(0));
      AssassinNode temp = front;
      for(int i = 1; i < names.size(); i++) {
         temp.next = new AssassinNode(names.get(i));
         temp = temp.next;
      }
   }

   //@post: prints the current KillRing with each person's target
   //@post: if there is only 1 person, they will stalk themselves
   public void printKillRing() {
      AssassinNode temp = front;
      while(temp.next != null) {
         System.out.println("    " + temp.name + " is stalking " + temp.next.name);
         temp = temp.next;
      }
      System.out.println("    " + temp.name + " is stalking " + front.name);
   }

   //@post: prints the current graveyard with each person's killer
   //@post: prints the kills in reverse order of their occurrence 
   public void printGraveyard() {
      AssassinNode temp = graveyardFront;
      while(temp != null) {
         System.out.println("    " + temp.name + " was killed by " + temp.killer);
         temp = temp.next;
      }
   }

   //@param name: the case insensitive name to be searched for
   //@post: returns whether or not the name is currently contained inside the killRing
   public boolean killRingContains(String name) {
      return listContains(front, name);
   }

   //@param name: the case insensitive name to be searched for
   //@post: returns whether or not the name is currently contained inside the graveyard
   public boolean graveyardContains(String name) {
      return listContains(graveyardFront, name);      
   }
   
   /*
    *(Helper Method)
    *@param listFront: the first node of the list that is being searched
    *@param name: the case insensitive name to be searched for
    *@post: returns true if the name is contained within the list
    *@post: returns false if the name is not contained within the list
   */
   private boolean listContains(AssassinNode listFront, String name) {
      name = name.toLowerCase();
      AssassinNode temp = listFront;
      while(temp != null) {
         if(temp.name.toLowerCase().equals(name)) {
            return true;
         }
         temp = temp.next;
      }
      return false;
   }

   //@post: returns whether or not the killRing has only 1 member
   public boolean gameOver() {
      return front.next == null;
   }

   //@post: returns null if the game is not over
   //@post: returns the first person inside the killRing
   public String winner() {
      if(!gameOver()) {
         return null;
      }
      return front.name;
   }

   /*
    *@param name: the case insensitive name of the person to be killed;
    *@throws 1st: will throw an IllegalStateException if the game is over
    *@throws 2nd: will throw an IllegalArgumentException if the killRing does not contain the name
    *@post: will remove the target from the killRing into the graveyard
    *@post: will set the killer's new target to the target of the late victim
   */
   public void kill(String name) {
      name = name.toLowerCase();
      if(gameOver()) {
         throw new IllegalStateException();
      }
      if(!killRingContains(name)) {
         throw new IllegalArgumentException();
      }
      AssassinNode temp = front;
      AssassinNode graveyardTemp = graveyardFront;
      if(front.name.toLowerCase().equals(name)) {
         while(temp.next != null) {
            temp = temp.next;
         }
         graveyardTemp = front;
         front = front.next;
      } else {
         while(!temp.next.name.toLowerCase().equals(name)) {
            temp = temp.next;
         }
         graveyardTemp = temp.next;
         temp.next = temp.next.next;
      }
      graveyardTemp.killer = temp.name;
      graveyardTemp.next = graveyardFront;
      graveyardFront = graveyardTemp;
   }

}