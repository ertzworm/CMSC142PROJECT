import java.io.*;
import java.util.*;
import javax.swing.*;

public class BackTrackCode {
	public BackTrackCode(String args1, String args2, JTextArea textArea) {
		System.out.println("Hello World!");

		int N = args1.length(); // gets the length of the first argument
		String fileName = "./words.txt"; // fileName of the words.txt
    	char[] completeWord = args1.toCharArray(); //get the charArray equivalent of argument 1; this is the one w/o underscores
    	char[] wordToFind = args2.toCharArray();  // get the charArray equivalent of argument 2; this the one w/ underscores
		int wordToFindLength = wordToFind.length; // length of the string that we have to find
		int completeWordLength = completeWord.length; // length of the string that is complete
		int toCompareLength;
		String startingLetter;
		String stringToCompare;

		int indices = countUnderscores(wordToFind, wordToFindLength); //number of underscores in the wordToFind
		int[] indexFlags = getIndexOfUnderscore(indices, wordToFind, wordToFindLength); //gets the indices of the underscores
		int fixedLength = wordToFindLength - indices; // length of the array that contains all the constant letters
		int toPermutateLength = completeWordLength - fixedLength; //length of the array that contains all underscores
		char[] fixedLetters = getFixedLetters(wordToFind, wordToFindLength, fixedLength); //array of the fixed letters
		char[] lettersToPermutate = getLettersToPermutate(fixedLength, N, fixedLetters, completeWord, toPermutateLength); // array of the letter to be used for permutation

		N = toPermutateLength;
		System.out.println("Fixed Letters:" + String.valueOf(fixedLetters));
		System.out.println("Letters to Permutate: " + String.valueOf(lettersToPermutate));

		backtrack(N,lettersToPermutate, wordToFind, toPermutateLength, indices, indexFlags, textArea);
	}

	public static Map fileReading(String fileName) {
		Map<String, NewDictionary> map = new HashMap<String, NewDictionary>();
		String line = null;
		//Babasahin yung words.txt tapos lalagay dun sa map. Naka-arrange na to in alphabetical order pero word.
		//Bale parang lahat ng starts with "a" magkakasama sa isang linkedlist tapos ganun din yung "b" and so on.
		try {
            FileReader fileReader = new FileReader(fileName);
            BufferedReader bufferedReader = new BufferedReader(fileReader);

            int counter = 0;
            while((line = bufferedReader.readLine()) != null) {
            	line = line.toLowerCase();
            	if(!map.containsKey(line.substring(0,1))) {
            		NewDictionary newD = new NewDictionary(); 
            		map.put(line.substring(0,1), newD);
            	} else {
            		map.get(line.substring(0,1)).addWord(line);
            	}
            }   

            bufferedReader.close();         
        }
        catch(FileNotFoundException ex) {
            System.out.println("Unable to open file '" + fileName + "'");                
        }
        catch(IOException ex) {
            System.out.println("Error reading file '" + fileName + "'"); 
        }
        return map;
	}

	public static void backtrack(int N, char[] lettersToPermutate, char[] wordToFind, int toPermutateLength, int indices, int[] indexFlags, JTextArea textArea) {
		String fileName = "./words.txt";
		int[][] option = new int[N+2][N+2]; 
		int[] nopts = new int[N+2];
		char[] output = new char[toPermutateLength];
		String stringToCompare;
		String lettersToFillUnderscores;
		String startingLetter;
		String newString;
		LinkedList<String> lettersForUnderscore = new LinkedList<String>();
		
		Map<String, NewDictionary> map  = fileReading(fileName);

		int i, c;
		int move = 0, start = 0;

		//Fill the 2d array option with negative 1
		for(i = 0; i < option.length; ++i) {
			for(int j = 0; j < option[i].length; ++j) {
	    		option[i][j] = -1;
			}
		}

		//Fill the 1d array nopts with negative 1
		for(i = 0; i < nopts.length; ++i) {
			nopts[i] = -1;
		}

		nopts[start] = 1;
		option[0][1] = 0;

		textArea.setText("");
		while(nopts[start] > 0) {
	    	if(nopts[move] > 0) {
	    		nopts[++move] = 0;

	    		if(move == N+1) {
	    			for(i=1;i<=N;i++) {
	    				int indexOfString = option[i][nopts[i]];
	    				output[i-1] = lettersToPermutate[indexOfString-1];
	    			}

	    			stringToCompare = String.valueOf(output);
	    			lettersToFillUnderscores = stringToCompare.substring(0,indices);

	    			//checks if the new permuatation has already been used
	    			if(!lettersForUnderscore.contains(lettersToFillUnderscores)) { //if not:
	    				lettersForUnderscore.add(lettersToFillUnderscores); //Add it to the list of strings to replace the underscores
	    				newString = getNewWord(wordToFind,lettersToFillUnderscores); //create a new string using the lettersToFiilUnderscores
	    				startingLetter = newString.substring(0,1); //get the first letter of the new string;
	    				// System.out.println("New String: " + newString + " Starting Letter: " + startingLetter);
	    				if(map.get(startingLetter).getList().contains(newString)) {
		    				// System.out.println("Found Match! " + newString);
		    				textArea.append("Found Match! " + newString + "\n");
		    			}
	    			}
	    			
	    		} else {
	    			for(c = N;c >= 1;c--) {
	    				for(i = move;i > 0; i--) {
	    					if(c == option[i][nopts[i]]) {
	    						break;
	    					}
	    				} if(i <= 0) {
	    					option[move][++nopts[move]] = c;
	    				}
	    			}
	    		}
	    	} else {
	    		nopts[--move]--;
	    	}
	    } System.out.println(lettersForUnderscore);
	}

	public static int sample(int newNum) {
		return(newNum+2);
	}

	public static String getNewWord(char[] wordToFind, String lettersToFillUnderscores) {
		char[] wordToFindComplete = wordToFind.clone();
		char[] charLettersForUn = lettersToFillUnderscores.toCharArray();
		int i, j;
		// System.out.println()
		for(i = 0, j = 0; i < wordToFind.length;i++) {
			if(wordToFindComplete[i] == '_') {
				wordToFindComplete[i] = charLettersForUn[j];
				j++;
			}
		}
		String finalWord = String.valueOf(wordToFindComplete);
		return finalWord;
	}

	public static int countUnderscores(char[] word, int length) {
		int indices = 0;
		for(int i=0; i<length; i++){
	        if(word[i] == '_'){
	            indices++;   
	        }
	    }
	    return indices;
	}

	public static int[] getIndexOfUnderscore(int indices, char[] word, int length) {
		int counter = 0;
		int[] arrayOfIndices = new int[indices];
		 while(counter != indices){
	        for(int i=0; i<length; i++){
	            if(word[i] == '_'){
	                arrayOfIndices[counter] = i;
	                counter++;
	            }
	        }
	    }
	    return arrayOfIndices;
	}

	public static char[] getFixedLetters(char[] wordToFind, int wordToFindLength, int fixedLength) {
		int i = 0;
		char[] fixedLetters = new char[fixedLength];
		char[] tempWordToFind = wordToFind.clone();
		while(i < fixedLength) {
			for(int j = 0; j < wordToFindLength; j++) {
				if(tempWordToFind[j] != '_') {
					fixedLetters[i] = tempWordToFind[j];
					tempWordToFind[j] = '_';
					break;
				}
			} i++;
		}
		return fixedLetters;
	}

	public static char[] getLettersToPermutate(int fixedLength, int N, char[] fixedLetters, char[] completeWord, int toPermutateLength) {
		char[] tempCompleteWord = getTempCompleteWord(fixedLength,N,fixedLetters, completeWord);
		char[] lettersToPermutate = new char[toPermutateLength];
		for(int i=0; i<toPermutateLength; i++) {
		 	for(int j=0; j<N; j++) {
		 		if(tempCompleteWord[j] != '+') {
		 			lettersToPermutate[i] = tempCompleteWord[j];
		 			tempCompleteWord[j] = '+'; 
		 			break;
		 		}
		 	}
		}
		return lettersToPermutate;
	}

	public static char[] getTempCompleteWord(int fixedLength, int N, char[] fixedLetters, char[] completeWord) {
		char[] tempCompleteWord = completeWord.clone();
		for(int i=0; i<fixedLength; i++) {
		 	for(int j=0; j<N; j++) {
		 		if(fixedLetters[i] == tempCompleteWord[j]) {
		 			tempCompleteWord[j] = '+';
		 			break;
		 		}
		 	}
		}
		return tempCompleteWord;
	}
}