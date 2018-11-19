#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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



//Struct for each string
typedef struct node_tag{
    int lineNumber;
    char s[50];
}NODE;

typedef struct node_tag1{
    struct node_tag1 *next;
    char word[50];
}LETTER, WORD;

typedef struct node_tag2{
    int index;
    struct node_tag1 *letter[5];
}DIRECTORY;

typedef struct node_tag3{
    struct node_tag3 *next;
}DICTIONARY;

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

//LinkedList implementation
int scanRecordsLL(DIRECTORY directory[], int size, int M, char *file) {

    LETTER *head, *temp, *ptr, *ptr2;
    head = NULL;

    char wordReceiver[50];
    int lineReceiver;

    //i -> 5
    int i = 0;
    //j -> 5
    int j = 0;
    FILE * fp = fopen(file, "r");

    int currentValue = 97;
    int pastValue = 97;


    if (fp == NULL) {
        printf("[ERROR] File could not be found.\n");
        return 0;
    }
    else {

        //All 5 directories
        for(i=0; i<5; i++){
            //Each directory has 5 letters each except for the last one which has two
            for(j=0; j<5; j++){

                
                while(fgets(wordReceiver, size, fp) != NULL){

                    //printf("String to be copied: %s\n", wordReceiver);
                    

                    if(wordReceiver[0] % currentValue == 0){
                        //Insert to header
                        //Insert
                        if(head == NULL){
                            temp = (LETTER *)malloc(sizeof(LETTER));
                            strcpy(temp->word, wordReceiver);
                            printf("temp->word is: %s", temp->word);
                            head = temp;
                            ptr = head;
                        }else{
                
                            temp = (LETTER *)malloc(sizeof(LETTER));
                            strcpy(temp->word, wordReceiver);
                            printf("temp->word is: %s", temp->word);
                            ptr->next = temp;
                            ptr = ptr->next;
                        
                            if(fgets(wordReceiver, size, fp) == NULL) ptr->next = NULL;
                            
                        }

                       
                    }else{
                        //Moving to the next directory
                        if(j == 4 && i != 4){
                            ptr->next = NULL;
                            temp = (LETTER *)malloc(sizeof(LETTER));
                            strcpy(temp->word, wordReceiver);

                            directory[i+1].letter[0] = temp;
                            ptr = directory[i+1].letter[0];
                            head = directory[i+1].letter[0];

                            //For Y and Z // Continue
                        }else if(j == 4 && i == 4){
                            temp = (LETTER *)malloc(sizeof(LETTER));
                            strcpy(temp->word, wordReceiver);
                            ptr->next = temp;
                            ptr = ptr->next;
                        }else if(j<4 && i <4){
                            //Moving to next letter only
                            ptr->next = NULL;
                            temp = (LETTER *)malloc(sizeof(LETTER));
                            strcpy(temp->word, wordReceiver);
                            directory[i].letter[j+1] = temp;
                            ptr = directory[i].letter[j+1];
                            head = directory[i].letter[j+1];
                            
                        }

                        
                        
                        
                        currentValue += 1;
                    }
                }

               

                
            }
        }

        // for(i=0; i<5; i++){
        //     for(j=0; j<5; j++){

        //         ptr2 = directory[i].letter[j];
        //         while(ptr2 != NULL){
        //             printf("String is: %s\n", ptr2->word);
        //             ptr2 = ptr2->next = NULL;
        //         }
        //     }
        // }
        
        // ptr2 = head;
        // int m = 1;
        // while(ptr2 != NULL){
        //     printf("Word right now is: %s\n", ptr2->word);
        //     ptr2 = ptr2->next;
        //     m++;
        // }

        //printf("Number of a's: %d", m);
        return 1;
    }
}


//Print
void viewRecords(NODE arr[], int n){
    int i;
    for(i=0; i<n; i++) printf("%s\n", arr[i].s);
}


//Create Hashmap implementation
//Set to lowercase before reading
//Check if it has non-alphabet values
//a[26][a-z], insert at head

int scanRecordsHash(DICTIONARY dictionary[], int size, char *file){

    int i = 0;
    int counter = 0;
    int bookmark;

	LETTER *try[26];
	for(i=0; i<26; i++){
		try[i] = NULL;
	}

    LETTER *head, *temp, *ptr;
    head = NULL;

    FILE *fp = fopen(file, "r");
    char wordReceiver[50];

    if(fp == NULL){
        printf("[ERROR] File not found!\n");
        return 0;
    }else{
           while(fgets(wordReceiver, size, fp) != NULL){
               toLowerCase(wordReceiver);
               //This sets a mark that corresponds as a key to the first letter of the word
               bookmark = wordReceiver[0] % 97;

			   //Test bench: Create list of A
               
                   temp = (LETTER *)malloc(sizeof(LETTER));
				   strcpy(temp->word, wordReceiver);
				   temp->next = NULL;
				   
				   if(try[bookmark] == NULL){
					   try[bookmark] = temp;
				   }else{
					   head = try[bookmark];
					   temp->next = head;
					   try[bookmark] = temp;
				   }
               
               

               //Set pointer


            //    if(wordReceiver[0] == 'z'){
            //        bookmark = wordReceiver[0] % 97;
            //        counter++;
            //        printf("[%d] String is: %s saved @ [%d]\n", counter, wordReceiver, bookmark);
            //    }
           }
    }


	

	for(i=0; i<26; i++){
		ptr = try[i];
		while(ptr != NULL){
			printf("Stored string: %s\n", ptr->word);
			ptr = ptr->next;
		}
	}
	
}

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
            if (wordReceiver[strlen(wordReceiver)-1] == '\n') wordReceiver[strlen(wordReceiver)-1] = '\0';
            else wordReceiver[strlen(wordReceiver)] = '\0';
            //This sets a mark that corresponds as a key to the first letter of the word
            bookmark = wordReceiver[0] % 97;

			   //Test bench: Create list of A
               
                temp = (LETTER *)malloc(sizeof(LETTER));
				strcpy(temp->word, wordReceiver);
				temp->next = NULL;
				   
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

//File reading
//Words should be sorted first in ascending order
int scanRecords(NODE arr[], int size, int M, char *file) {

   
    int i = 0;
    FILE * fp = fopen(file, "r");


    if (fp == NULL) {
        printf("[ERROR] File could not be found.\n");
        return 0;
    }
    else {

        for (i = 0; i < M && fgets(arr[i].s, size, fp) != NULL; ++i) {
            arr[i].lineNumber = i+1;

            if (arr[i].s[strlen(arr[i].s)-1] == '\n') arr[i].s[strlen(arr[i].s)-1] = '\0';
            else arr[i].s[strlen(arr[i].s)] = '\0';

            //Changes all strings to lowercase
            toLowerCase(arr[i].s);
            printf("String is: %s\n", arr[i].s);
            
        }
        return 1;
    }
}

int main(int argc, char *argv[]){

    //Read words.txt

    //printASCII();
    int N = strlen(argv[1]);
    printf("N is %d", N);

    int M = 50000;
    int option[N+2][N+2];
    int nopts[N+2];
    int i, c;
    int move = 0, start = 0;


	int k = N;
    int string_size = 50;
    char *file = "words.txt";

    //Test variables
    char test3[N];
    char toCompare[N];
    int toCompareLength;

    //printf("toCompare length %ld ", strlen(toCompare));

    NODE records[M];
    DIRECTORY directory[5];
    LETTER a[M];

    DICTIONARY dictionary[26];

    nopts[start] = 1;
    option[0][1] = 0;

	LETTER *myDictionary[26];
    LETTER *traverser;

	// for(i=0; i<26; i++){
	// 	traverser = myDictionary[i];
	// 	while(traverser != NULL){
	// 		printf("Stored string: %s\n", traverser->word);
	// 		traverser = traverser->next;
	// 	}
	// }

    //Implementations
    //if(!scanRecordsLL(directory, string_size, M, file)) return 0;
    //if(!scanRecords(records, string_size, M, file)) return 0;
    //if(!scanRecordsHash(dictionary, string_size, file)) return 0;
	if(!scanRecordsHash2(myDictionary, string_size, file)) return 0;
    //viewRecords(records, M);

    // This works!
    // for(i=0; i<26; i++){
    //     traverser = myDictionary[i];
    //     while(traverser != NULL){
    //         printf("Current word is: %s", traverser->word);
    //         traverser = traverser->next;
    //     }
    // }


    printf("Input string is: %s\n\n", argv[1]);
    strcpy(test3, argv[1]);

    

    while(nopts[start] > 0){
        if(nopts[move] > 0){
            nopts[++move] = 0;
			
            if(move == N+1){
				//If it reaches the last index, print
                for(i=1; i<=N; i++){

                //Store to an array
                int indexOfString = option[i][nopts[i]];
                toCompare[i-1] = test3[indexOfString-1];
                //printf("%c", test3[indexOfString-1]);
                //printf("%i ", option[i][nopts[i]]);
                //printf("%i ", indexOfString);
                //printf("%c ", test3[indexOfString-1]);

                }

                
                int bookmark = toCompare[0] % 97;
                traverser = myDictionary[bookmark];

                // printf("Bookmark @ %d\n", bookmark);
                // printf("toCompare value: %s\n", toCompare);
                // printf("Strlen of toCompare %ld\n", strlen(toCompare));
                
                toCompareLength = strlen(toCompare);

                while(traverser != NULL){
                    int result = strcmp(traverser->word, toCompare);
                    int wordLength = strlen(traverser->word);
                    //printf("toCompare value: %s\n", toCompare);
                    //printf("Dictionary word is: %s vs %s\n", traverser->word, toCompare);

                    if(toCompareLength == wordLength){
                        if(strcmp(traverser->word, toCompare) == 0){
                            printf("Found match! %s\n", traverser->word);
                            break;
                        }
                        
                    }
                    traverser = traverser->next;
                }
                // int indexChecker;

                // int toCompareLength = strlen(toCompare);
                // printf("String length of toCompare: %d", toCompareLength);
                // char placeHolder[N];

                // for(indexChecker=0; indexChecker<M; indexChecker++){
                //     //printf("%s\n", records[indexChecker].s);
                //     //printf("Processing: %d\n", indexChecker);

                    
                //     int wordLength = strlen(records[indexChecker].s);
                //     if(toCompareLength == wordLength){
                //         strcpy(placeHolder, records[indexChecker].s);
                //         //printf("String to be compared: %s, %s\n", toCompare, placeHolder);
                //         if(strcmp(toCompare, placeHolder) == 0){

                //             printf("Match found!\n");
                //             printf("Possible value: %s at index: %d", placeHolder, indexChecker+1);
                //             //break;
                //         }else{
                //             //printf("processing...%d\n", indexChecker);
                //         }
                //     }
                // }                
                                

                //Newline
                //printf("\n");
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

    exit(1);

    return 1;
}