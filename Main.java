import java.io.*;
import java.util.*;

class Main {
	public static void main(String[] args) {
		System.out.println("Hello World!");

		int N = args[0].length(); // gets the length of the first argument
		String fileName = "./words.txt";
		String line = null;
		int[][] option = new int[N+2][N+2]; 
		int[] nopts = new int[N+2];

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

		//Eto yung Dictionary myDictionary sa c before
		Map<String, NewDictionary> map = new HashMap<String, NewDictionary>();


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
        // System.out.println(map.get("a").getList());
        // System.out.println(sample(3));
        // System.out.println(option[1][1]);
        nopts[start] = 1;
    	option[0][1] = 0;
    	char[] completeWord = args[0].toCharArray();
    	char[] wordToFind = args[1].toCharArray();
		char[] toCompare = new char[N];
		int wordToFindLength = wordToFind.length;
		int completeWordLength = completeWord.length;
		int toCompareLength;
		String startingLetter;
		String stringToCompare;


		int indices = countUnderscores(wordToFind, wordToFindLength);
		int[] indexFlags = getIndexOfUnderscore(indices, wordToFind, wordToFindLength);    
		int fixedLength = wordToFindLength - indices;
		int toPermutateLength = completeWordLength - fixedLength;
		char[] fixedLetters = getFixedLetters(wordToFind, wordToFindLength, fixedLength);
		char[] lettersToPermutate = getLettersToPermutate(fixedLength, N, fixedLetters, completeWord, toPermutateLength);

		N = toPermutateLength;
		System.out.println(fixedLetters);
		System.out.println(lettersToPermutate);

        // while(nopts[start] > 0) {
        // 	if(nopts[move] > 0) {
        // 		nopts[++move] = 0;

        // 		if(move == N+1) {
        // 			for(i=1;i<=N;i++) {
        // 				int indexOfString = option[i][nopts[i]];
        // 				toCompare[i-1] = completeWord[indexOfString-1];
        // 			}

        // 			toCompareLength = toCompare.length;

        // 			startingLetter = String.valueOf(toCompare[0]);
        // 			stringToCompare = String.valueOf(toCompare);
        // 			System.out.println(stringToCompare);
        // 			if(map.get(startingLetter).getList().contains(stringToCompare)) {
        // 				System.out.println("Found Match! " + stringToCompare);
        // 			}
        // 		} else {
        // 			for(c = N;c >= 1;c--) {
        // 				for(i = move;i > 0; i--) {
        // 					if(c == option[i][nopts[i]]) {
        // 						break;
        // 					}
        // 				} if(i <= 0) {
        // 					option[move][++nopts[move]] = c;
        // 				}
        // 			}
        // 		}
        // 	} else {
        // 		nopts[--move]--;
        // 	}
        // }
	}

	public static int sample(int newNum) {
		return(newNum+2);
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
	    System.out.println(counter);
	    System.out.println(indices);

	    return arrayOfIndices;
	}

	public static char[] getFixedLetters(char[] wordToFind, int wordToFindLength, int fixedLength) {
		int i = 0;
		char[] fixedLetters = new char[fixedLength];
		while(i < fixedLength) {
			for(int j = 0; j < wordToFindLength; j++) {
				if(wordToFind[j] != '_') {
					fixedLetters[i] = wordToFind[j];
					wordToFind[j] = '_';
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
		 		if(fixedLetters[i] == completeWord[j]) {
		 			tempCompleteWord[j] = '+';
		 			break;
		 		}
		 	}
		}
		return tempCompleteWord;
	}
}