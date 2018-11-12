#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 3

/*

    arr[5]

*/



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
    struct node_tag LETTER[5];
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

//LinkedList implementation
int scanRecordsLL(DIRECTORY directory[], int size, int M, char *file) {

    LETTER *head, *temp, *ptr, *ptr2;
    head = NULL;

    char wordReceiver[50];
    int lineReceiver;

    int i = 0;
    FILE * fp = fopen(file, "r");


    if (fp == NULL) {
        printf("[ERROR] File could not be found.\n");
        return 0;
    }
    else {

        for (i = 0; i < M && fgets(wordReceiver, size, fp) != NULL; ++i) {
            lineReceiver = i+1;

            if (wordReceiver[strlen(wordReceiver)-1] == '\n') wordReceiver[strlen(wordReceiver)-1] = '\0';
            else wordReceiver[strlen(wordReceiver)] = '\0';

            //Changes all strings to lowercase
            toLowerCase(wordReceiver);
            //printf("Word receiver is: %s\n", wordReceiver);

            if(wordReceiver[0] == 'a'){
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
                    ptr->next = temp;
                    ptr = ptr->next;
                }
                
            }else{
                break;
            }

            
            
        }

        ptr2 = head;
        int m = 1;
        while(ptr2 != NULL){
            printf("Word right now is: %s\n", ptr2->word);
            ptr2 = ptr2->next;
            m++;
        }

        printf("Number of a's: %d", m);
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

    int M = 10;
    int option[N+2][N+2];
    int nopts[N+2];
    int i, c;
    int move = 0, start = 0;


	int k = N;
    int string_size = 50;
    char *file = "words.txt";
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