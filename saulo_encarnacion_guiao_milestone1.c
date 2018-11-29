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
        //printf("newNode->word: %s\n", newNode->word);
       // printf("TRUEEEEEEE\n");
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
        //printf("newWord: %s\n", newWord);
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
            //printf("newWord: %s\n", newWord);
        } else {
            //Do nothing
        }
    }

    // LETTER *ptr;
    // ptr = *permutated;
    // printf("Words: \n");
    // while(ptr != NULL){
    //     printf("%s\n", ptr->word);
    //     ptr = ptr->next;
    // }
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

    printf("Letters To Permutate(L): %ld\n", strlen(lettersToPermutate));
    printf("=============================\n");

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
                //toCompare[i-1] = firstArgument[indexOfString-1];
                output[i-1] = lettersToPermutate[indexOfString-1];
                // printf("%c ", output[i-1]);
                
                //printf("%c", firstArgument[indexOfString-1]);
                //printf("%i ", option[i][nopts[i]]);
                //printf("%i ", indexOfString);
                //printf("%c ", firstArgument[indexOfString-1]);
                }

                // printf("strlen of output: %ld\n", strlen(output));
                // printf("Permutated Word: %s\n", output);
                char subString[strlen(output)+1];
                subString[strlen(output)] = 0;
                getSubstring(subString, output, indices);

                //printf("Substring is: %s\n", subString);

                
                char testVar[strlen(wordToGuess)];
                strcpy(testVar, wordToGuess);

                addToPermutated(&permutated, subString, testVar);

                
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

    LETTER *myDictionary[26];
    LETTER *traverser;
    int string_size = 50;
    char *file = "words.txt";

    if(!scanRecordsHash2(myDictionary, string_size, file)) return 0;

    // printf("============= DICTIONARY =============");
    // for(i=0; i<26; i++){
    //     traverser = myDictionary[i];
    //     printf("Bookmark [%d]\n", i);
    //     while(traverser != NULL){
    //         printf("%s\n", traverser->word);
    //         traverser = traverser->next;
    //     }
    // }

    LETTER *temp = permutated;
    int counter = 0;
    printf("Words to check in dictionary: \n");
    while(temp != NULL) {
        printf("[%d] %s\n", counter, temp->word);
        temp = temp->next;
        counter++;
    }

    temp = permutated;
    while(temp != NULL){
        
        char bookmark = temp->word[0];
        int index = bookmark % 97;
        traverser = myDictionary[index];
        while(traverser != NULL){
            if(strcmp(temp->word, traverser->word) == 0){
                printf("Found match at index [%d]: %s\n", index, temp->word);
                break;
            }
            traverser = traverser->next;
        }
        temp = temp->next;
    }



    

    return 0;
}

int main(int argc, char *argv[]){

    //Initialization of values
    int N = strlen(argv[1]);

    printf("=========== STATS ===========\n");
    printf("Starting N: %d\n", N);
    
    int option[N+2][N+2];
    int nopts[N+2];

    int i, c, j;
    int move = 0, start = 0;


    int k = N;
    int string_size = 50;
    char *file = "words.txt";

    //Test variables
    char firstArgument[N];
    char toCompare[N];
    int toCompareLength;
    int testVarLength;

    nopts[start] = 1;
    option[0][1] = 0;

    //Array of pointers + pointer for traversal
    // LETTER *myDictionary[26];
    // LETTER *traverser;
    
    //Assignment of arguments to variable
    int test4Length = strlen(argv[2]);
    char secondArgument[test4Length];

    strcpy(firstArgument, argv[1]);
    strcpy(secondArgument, argv[2]);

    
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
    for(i=0; i<strlen(secondArgument); i++){
        if(secondArgument[i] == '_'){
            indices++;   
        }
    }

    //Marks underscores' positions
    int indexFlags[indices];
    
    int fixedLength = strlen(secondArgument) - indices;
    int toPermutateLength = strlen(firstArgument) - fixedLength;

    printf("To Permutate Length : %d\n", toPermutateLength);
    printf("Fixed Length: %d\n", fixedLength);


    //fixedLetters - cross-referencing sustained letters to argv[1] to get remaining letters to permutate
    char lettersToPermutate[toPermutateLength];
    char fixedLetters[fixedLength];

    char s4[strlen(secondArgument)];
    char s3[strlen(firstArgument)];
    char s5[strlen(firstArgument)];

    //S4 - copy of argv[2]
    strcpy(s4, secondArgument);
    // printf("before ever N: %d\n", N);

    
    //This outputs lettersToPermutate
    if(fixedLength == 0){
        for(i=0; i<N; i++){
            lettersToPermutate[i] = firstArgument[i];
        }
    }else{

        

        //Gets fixed letters in the 2nd argument
        i=0;
        while(i<fixedLength){
            for(j=0; j<test4Length; j++){
                if(s4[j] != '_'){
                    fixedLetters[i] = s4[j];
                    s4[j] = '_';
                    break;
                }
            }
        i++;
        }
        fixedLetters[fixedLength] = '\0';

        //S3 - copy of argv[1]
        strcpy(s3, firstArgument);

        for(i=0; i<fixedLength; i++){
        for(j=0; j<N; j++){
            if(fixedLetters[i] == s3[j]){
                s3[j] = '+';
                break;
            }
        }
        }

        strcpy(s5, s3);
        printf("s5 is: %s\n", s5);
        printf("N is: %d\n", N);
        for(i=0; i<toPermutateLength; i++){
            for(j=0; j<N; j++){
                if(s5[j] != '+'){
                    lettersToPermutate[i] = s5[j];
                    s5[j] = '+';
                    break;
                }
            }
        }
    }

    

    

    
    // printf("Strlen of lettersToPermutate is: %ld\n", toPermutateLength);
    lettersToPermutate[toPermutateLength] = '\0';

    printf("Strlen of fixed is: %ld\n", strlen(fixedLetters));
    printf("Fixed Letters: %s\n", fixedLetters);


    printf("Letters to permutate are %s\n", lettersToPermutate);
    printf("N : %d\n ", N);
    // printf("============\n");

    //Stores the indices of the underscores
    while(counter != indices){
        for(i=0; i<strlen(secondArgument); i++){
            if(secondArgument[i] == '_'){
                indexFlags[counter] = i;
                counter++;
            }
        }
    }


    printf("Letters to permutate : %s\n", lettersToPermutate);

    backtrack(toPermutateLength, lettersToPermutate, secondArgument);

    
    exit(1);
    return 1;
}