import java.io.*;
import java.util.*;

public class NewDictionary {
   	LinkedList<String> wordsStartingWith;

   public NewDictionary() {
  	this.wordsStartingWith = new LinkedList<String>();
   }

   public void addWord(String word) {
   	this.wordsStartingWith.add(word);
   }

   public LinkedList getList() {
   	return this.wordsStartingWith;
   }
}