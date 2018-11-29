#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*
    Encarnacion, Guiao, Saulo
*/

/*
    Number of words:
    a: 30850
    b: 24332
    c: 38933
    d: 22777
    e: 16815
    f: 15870
    g: 14466
    h: 18662
    i: 15220
    j: 4158
    k: 6167
    l: 14093
    m: 25194
    o: 15061
    p: 40956
    q: 3218
    r: 21286
    s: 50569
    t: 25219
    u: 23791
    v: 6816
    w: 11672
    x: 609
    y: 1740
    z: 1823
*/


typedef struct node_tag1{
    struct node_tag1 *next;
    char word[50];
}LETTER;

void toLowerCase(char s[]){
    int i = 0;

    while(s[i] != '\0'){
        if(s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
        i++;
    }
}

void printASCII(){
    int i=0;

    for(i=97; i<97+26; i++){
        printf("Letter: %c\tValue: %d\n", i, i);
    }
}

void getSubstring(char out[], char in[], int x){
    int i;

    for(i=0; i<x; i++){
        out[i] = in[i];
    }
}

//Create Hashmap implementation
//Set to lowercase before reading
//Check if it has non-alphabet values
//a[26][a-z], insert at head
int scanRecordsHash2(LETTER *myDictionary[], int size, char *file){

    int i = 0;
    int counter = 0;
    int bookmark;

    LETTER *head, *temp, *ptr;
    //Set dictionary and head to NULL;
    for(i=0; i<26; i++){
        myDictionary[i] = NULL;
    }
    head = NULL;

    FILE *fp = fopen(file, "r");
    char wordReceiver[50];

    

    if(fp == NULL){
        printf("[ERROR] File not found!\n");
        return 0;
    }else{
        while(fgets(wordReceiver, size, fp) != NULL){
            toLowerCase(wordReceiver);

            //Trim wordReceiver
            if (wordReceiver[strlen(wordReceiver)-1] == '\n') wordReceiver[strlen(wordReceiver)-1] = '\0';
            else wordReceiver[strlen(wordReceiver)] = '\0';
            
            //This sets a mark that corresponds as a key to the first letter of the word
            bookmark = wordReceiver[0] % 97;
            
            //Creation of node
            temp = (LETTER *)malloc(sizeof(LETTER));
            strcpy(temp->word, wordReceiver);
            temp->next = NULL;
            
            //Insert at head
            if(myDictionary[bookmark] == NULL){
                myDictionary[bookmark] = temp;
            }else{
                head = myDictionary[bookmark];
                temp->next = head;
                myDictionary[bookmark] = temp;
                head = NULL;
            }
        }
    }
    return 1;
}

//Gets number of underscores
int getIndices(char wordToGuess[]){

    int indices = 0;
    int i;

    for(i=0; i<strlen(wordToGuess); i++){
        if(wordToGuess[i] == '_'){
            indices++;   
        }
    }

    return indices;
}

void getUnderscoreIndices(int underscoreIndices[], int indices, char wordToGuess[]){

    int counter = 0;
    int i;

     while(counter != indices){
        for(i=0; i<strlen(wordToGuess); i++){
            if(wordToGuess[i] == '_'){
                underscoreIndices[counter] = i;
                counter++;
            }
        }
    }
}

void addToPermutated(LETTER **permutated, char allowedPermutations[], char testVar[]){

    LETTER *head = NULL;
    LETTER *temp; //traverse
    LETTER *newNode; //holds the new WOrd

    head = *permutated;
    
    newNode = (LETTER *)malloc(sizeof(LETTER));
    strcpy(newNode->word, allowedPermutations);
    //Trim newNode->word
    if (newNode->word[strlen(newNode->word)-1] == '\n') newNode->word[strlen(newNode->word)-1] = '\0';
    else newNode->word[strlen(newNode->word)] = '\0';

    newNode->next = NULL;

    if(*permutated == NULL){
        printf("newNode->word: %s\n", newNode->word);
        printf("TRUEEEEEEE\n");
        *permutated = newNode;

        char newWord[strlen(testVar)];
        strcpy(newWord, testVar);
        int i=0, j=0;
        while(i<strlen(newNode->word)){
            for(j=0; j<strlen(newWord); j++){
                if(testVar[j] == '_'){
                    newWord[j] = newNode->word[i];
                    testVar[j] = newWord[j];
                    break;
                }
            }
            i++;
        }
        printf("newWord: %s\n", newWord);
    }else{
        temp = *permutated;
        while(temp != NULL) {
            if(strcmp(temp->word, allowedPermutations) == 0) {
                break;
            } else {
                temp = temp->next;
            }
        }
        if(temp == NULL) {
            newNode->next = *permutated;
            *permutated = newNode;

            char newWord[strlen(testVar)];
            strcpy(newWord, testVar);
            int i=0, j=0;
            while(i<strlen(newNode->word)){
                for(j=0; j<strlen(newWord); j++){
                    if(testVar[j] == '_'){
                        newWord[j] = newNode->word[i];
                        testVar[j] = newWord[j];
                        break;
                    }
                }
                i++;
            }
            printf("newWord: %s\n", newWord);
        } else {
            printf("HAHAHA\n");
        }
    }

    LETTER *ptr;
    ptr = *permutated;
    printf("Words: \n");
    while(ptr != NULL){
        printf("%s\n", ptr->word);
        ptr = ptr->next;
    }
}

int backtrack(int N, char lettersToPermutate[], char wordToGuess[]){
    printf("letters to Permutate initial %s\n", lettersToPermutate);

    int option[N+2][N+2];
    int nopts[N+2];

    int i,c;
    int move = 0, start = 0;
    int k = N;
    
    nopts[start] = 1;
    option[0][1] = 0;

    int outputLength = strlen(lettersToPermutate);
    char output[outputLength+1];

    printf("Output length: %d\n", outputLength);
    output[outputLength] = 0;

    int indices = getIndices(wordToGuess);
    int underscoreIndices[indices];

    getUnderscoreIndices(underscoreIndices, indices, wordToGuess);

    printf("Letters To Permutate(L): %ld", strlen(lettersToPermutate));

    LETTER *permutated = NULL;

    char toCompare2[N];

    while(nopts[start] > 0){
        if(nopts[move] > 0){
            nopts[++move] = 0;
            
            if(move == N+1){
                //If it reaches the last index, print
                for(i=1; i<=N; i++){

                //Store to an array
                int indexOfString = option[i][nopts[i]];
                //toCompare[i-1] = test3[indexOfString-1];
                output[i-1] = lettersToPermutate[indexOfString-1];
                // printf("%c ", output[i-1]);
                
                //printf("%c", test3[indexOfString-1]);
                //printf("%i ", option[i][nopts[i]]);
                //printf("%i ", indexOfString);
                //printf("%c ", test3[indexOfString-1]);
                }

                printf("strlen of output: %ld\n", strlen(output));
                printf("Permutated Word: %s\n", output);
                char subString[strlen(output)+1];
                subString[strlen(output)] = 0;
                getSubstring(subString, output, indices);

                printf("Substring is: %s\n", subString);

                
                char testVar[strlen(wordToGuess)];
                strcpy(testVar, wordToGuess);

                addToPermutated(&permutated, subString, testVar);

                LETTER *temp = permutated; 
                while(temp != NULL) {
                    printf("temp->word: %s\n", temp->word);
                    temp = temp->next;
                }
                // for(i=0; i<indices; i++){
                //     testVar[indexFlags[i]] = output[i]; 
                // }

                //Bookmark notes the index of the first letter in our dictionary
                //For example, if the word is ant, a is noted as 97 in ASCII
                //97 % 97 will yield 0, thus searches it in myDictionary[0]

                //For testVar
                // int bookmark = testVar[0] % 97;
                // traverser = myDictionary[bookmark];

                // testVarLength = strlen(testVar);

                // while(traverser != NULL){
                //     int wordLength = strlen(traverser->word);
                    
                //     //printf("toCompare value: %s\n", toCompare);
                //     //printf("Dictionary word is: %s vs %s\n", traverser->word, toCompare);

                //     //Comparison only done between strings of equal length
                //     if(testVarLength == wordLength){
                //         if(strcmp(traverser->word, testVar) == 0){
                //             printf("Found match! %s\n", traverser->word);
                //             break;
                //         }
                //     }
                //     traverser = traverser->next;
                // }

            }else{
                for(c = N; c>=1; c--){
                    for(i=move; i>0; i--){
                        if(c==option[i][nopts[i]])
                            break;
                    }
                    if(i<=0){
                        option[move][++nopts[move]] = c;
                    }
                    
                }
                
            }
        }else{
            nopts[--move]--;
        }
    }

    

    return 0;
}

int main(int argc, char *argv[]){

    //Initialization of values
    int N = strlen(argv[1]);

    printf("Starting N: %d\n", N);
    
    int option[N+2][N+2];
    int nopts[N+2];

    int i, c, j;
    int move = 0, start = 0;


    int k = N;
    int string_size = 50;
    char *file = "words.txt";

    //Test variables
    char test3[N];
    char toCompare[N];
    int toCompareLength;
    int testVarLength;

    nopts[start] = 1;
    option[0][1] = 0;

    //Array of pointers + pointer for traversal
    LETTER *myDictionary[26];
    LETTER *traverser;

    if(!scanRecordsHash2(myDictionary, string_size, file)) return 0;
    
    //Assignment of arguments to variable
    int test4Length = strlen(argv[2]);
    char test4[test4Length];

    strcpy(test3, argv[1]);
    strcpy(test4, argv[2]);

    
    // Thought process for milestone 2:
    // 1. Note the indices of the underscores
    // 2. Note the remaining letters
    // 3. Permutate the remaining letters
    // 4. Assign them to their corresponding index
    // 5. Begin search
    

    int indices=0;
    int remainingLettersIndices[N];
    int remainingLetters=0;
    int counter=0;

    //Finds number of underscores
    for(i=0; i<strlen(test4); i++){
        if(test4[i] == '_'){
            indices++;   
        }
    }

    //Marks underscores' positions
    int indexFlags[indices];
    
    int fixedLength = strlen(test4) - indices;
    int toPermutateLength = strlen(test3) - fixedLength;
    printf("TPL : %d\n", toPermutateLength);
    printf("Fixed Length: %d\n", fixedLength);


    //fixedLetters - cross-referencing sustained letters to argv[1] to get remaining letters to permutate
    char lettersToPermutate[toPermutateLength];
    char fixedLetters[fixedLength];

    char s4[strlen(test4)];
    char s3[strlen(test3)];
    char s5[strlen(test3)];

    //S4 - copy of argv[2]
    strcpy(s4, test4);
    // printf("before ever N: %d\n", N);

    i=0;
    while(i<fixedLength){
        printf("Entered fixed");s
        for(j=0; j<test4Length; j++){
            if(s4[j] != '_'){
                fixedLetters[i] = s4[j];
                s4[j] = '_';
                break;
            }
        }
        i++;
    }

    // //S3 - copy of argv[1]
    // strcpy(s3, test3);
    // for(i=0; i<fixedLength; i++){
    //    for(j=0; j<N; j++){
    //        if(fixedLetters[i] == s3[j]){
    //            s3[j] = '+';
    //            break;
    //        }
    //    }
    // }

    // strcpy(s5, s3);
    // printf("s5 %s\n", s5);
    // printf(" N: %d\n", N);
    // for(i=0; i<toPermutateLength; i++){
    //     for(j=0; j<4; j++){
    //         if(s5[j] != '+'){
    //             lettersToPermutate[i] = s5[j];
    //             s5[j] = '+';
    //             break;
    //         }
    //     }
    // }

    // fixedLetters[fixedLength] = '\0';
    // // printf("Strlen of lettersToPermutate is: %ld\n", toPermutateLength);
    // lettersToPermutate[toPermutateLength] = '\0';
    // printf("Strlen of fixed is: %ld\n", strlen(fixedLetters));
    // printf("Fixed Letters: %s\n", fixedLetters);
    // printf("s3 is %s\n", s3);
    printf("Letters to permutate are %s\n", lettersToPermutate);
    printf("N : %d ", N);
    // printf("============\n");

    //Stores the indices of the underscores
    while(counter != indices){
        for(i=0; i<strlen(test4); i++){
            if(test4[i] == '_'){
                indexFlags[counter] = i;
                counter++;
            }
        }
    }

    // for(i=0; i<indices; i++){
    //     printf("Underscores @ %d\n", indexFlags[i]);
    // }

    //Important variables!
    //indexFlags[] - contains indices of underscores
    //indices - total number of underscores

    N = toPermutateLength;
    char toCompare2[N];

    printf("Letters to permutate : %s!!!\n", lettersToPermutate);

    //backtrack(N, lettersToPermutate, test4);
    
    
    // while(nopts[start] > 0){
    //     if(nopts[move] > 0){
    //         nopts[++move] = 0;
            
    //         if(move == N+1){
    //          //If it reaches the last index, print
    //             for(i=1; i<=N; i++){

    //             //Store to an array
    //             int indexOfString = option[i][nopts[i]];
    //             //toCompare[i-1] = test3[indexOfString-1];
    //             toCompare2[i-1] = lettersToPermutate[indexOfString-1];
                
    //             //printf("%c", test3[indexOfString-1]);
    //             //printf("%i ", option[i][nopts[i]]);
    //             //printf("%i ", indexOfString);
    //             //printf("%c ", test3[indexOfString-1]);
    //             }

    //             //printf("Permutated Word: %s\n", toCompare2);
    //             char testVar[strlen(test4)];
    //             strcpy(testVar, test4);

    //             for(i=0; i<indices; i++){
    //                 testVar[indexFlags[i]] = toCompare2[i]; 
    //             }

    //             //Bookmark notes the index of the first letter in our dictionary
    //             //For example, if the word is ant, a is noted as 97 in ASCII
    //             //97 % 97 will yield 0, thus searches it in myDictionary[0]

    //             //For testVar
    //             int bookmark = testVar[0] % 97;
    //             traverser = myDictionary[bookmark];

    //             testVarLength = strlen(testVar);

    //             while(traverser != NULL){
    //                 int wordLength = strlen(traverser->word);
                    
    //                 //printf("toCompare value: %s\n", toCompare);
    //                 //printf("Dictionary word is: %s vs %s\n", traverser->word, toCompare);

    //                 //Comparison only done between strings of equal length
    //                 if(testVarLength == wordLength){
    //                     if(strcmp(traverser->word, testVar) == 0){
    //                         printf("Found match! %s\n", traverser->word);
    //                         break;
    //                     }
    //                 }
    //                 traverser = traverser->next;
    //             }

    //         }else{
    //             for(c = N; c>=1; c--){
    //                 for(i=move; i>0; i--){
    //                     if(c==option[i][nopts[i]])
    //                         break;
    //                 }
    //                 if(i<=0){
    //                  option[move][++nopts[move]] = c;
    //              }
                    
    //             }
                
    //         }
    //     }else{
    //         nopts[--move]--;
    //     }
    // }
    exit(1);
    return 1;
}