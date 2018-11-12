#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 3


//Struct for each string
typedef struct node_tag{
    int lineNumber;
    char s[50];
}NODE;

typedef struct node_tag1{
    int lineNumber;
    struct node_tag1 *next;
    char word[50];
}LETTER;

typedef struct node_tag2{
    int index;
    struct node_tag1 *letter[5];
}DIRECTORY;

void toLowerCase(char s[]){
    int i = 0;

    while(s[i] != '\0'){
        if(s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
        i++;
    }
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

                    printf("String to be copied: %s\n", wordReceiver);

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

                            if(fgets(wordReceiver, size, fp) == NULL){
                                ptr->next = NULL;
                            }else{
                                temp = (LETTER *)malloc(sizeof(LETTER));
                                strcpy(temp->word, wordReceiver);
                                ptr->next = temp;
                                ptr = ptr->next;
                            }
                            
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

                ptr->next = NULL;

                
            }
        }


        for(i=0; i<5; i++){
            for(j=0; j<5; j++){

                ptr2 = directory[i].letter[j];
                while(ptr2 != NULL){
                    printf("String is: %s\n", ptr2->word);
                    ptr2 = ptr2->next = NULL;
                }
            }
        }
        
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


int main(int argc, char *argv[]){

    //Read words.txt

    printASCII();

    int M = 50000;
    int option[N+2][N+2];
    int nopts[N+2];
    int i, c;
    int move = 0, start = 0;


	int k = N;
    int string_size = 50;
    char *file = "output.txt";
    char test3[N];
    char toCompare[N];

    NODE records[M];
    DIRECTORY directory[5];
    LETTER a[M];

    nopts[start] = 1;
    option[0][1] = 0;

    if(!scanRecordsLL(directory, string_size, M, file)) return 0;
    //if(!scanRecords(records, string_size, M, file)) return 0;

    //viewRecords(records, M);

    printf("Input string is: %s\n", argv[1]);
    strcpy(test3, argv[1]);


    //Read wordtxt

    

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
                printf("%i ", option[i][nopts[i]]);

                }

                printf("toCompare value: %s", toCompare);

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
                printf("\n");
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
           //Backtracking part
            nopts[--move]--;
        }
    }
}