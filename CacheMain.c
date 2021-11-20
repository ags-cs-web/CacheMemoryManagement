/* Author: Prasun Biswas & Anustup Ganguly of GCETTS */
/* The given program tries to simulate the cache and main memory workings simultaneously with verboseness */
/* It is very basic and doesn't delve deep into the caching mechanisms or memory mechanisms or other advanced concepts*/
/* We also don't take into a/c the multilevel cache that are available name L1, L2, L3...*/
/* We use the LIFO cache replacement mechanism to illustrate */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


/* This allows us to introduce pause between execution of our program */
unsigned int sleep(unsigned int seconds);

/* Our main Data variable, i.e the memory block */
typedef struct Data {
    int value;
    int bit;
} data;

static int j = 0;  //For storing the last index in cache.
static int k = 0;  //For storing the last index in main memory.

void replace(data *arr,data *cache, int arr_index) {   //How to replace the FIFO block?!
    arr_index = sizeof(int)*arr_index - sizeof(int);
    for (register int i=0; i<sizeof(int); ++i){
        (cache + j)->value = (arr + arr_index)->value;
        (cache + j)->bit = 1;
        ++j;
        ++arr_index;
    }
    if (j == 13)
        j = 0;
}

void output(data *word, data *cache) {   //Output both the cache and main memory.
    printf("\n      Main Memory                    Cache Memory:\n ");
    printf("\n\n    Value  Address                  Value  Address\n\n");
    int j = 0;
    for (register int i=0; i<4; ++i) {
        int count = 0;
        while (count < 4) {
            if (i < 3) {
                printf("   %5d   %p         %5d   %p\n", (word + j)->value, (void *) &((word +j)->value), (cache+j)->value, (void *) &((cache+j)->value));
                ++j;
                ++count;
            } else {
                printf("   %5d   %p\n", (word + j)->value, (void *) &((word+j)->value));
                ++j;
                ++count;
            }
        }
        printf("\n");
        sleep(1);
    }
    printf("\n   (Main Memory printed upto 4 blocks......)\n\n");
}


void memory(data *word) {    //To insert elements in the main memory.
    printf("\n________________________________________________________________________\n\n");
    printf("\n     Enter the no of elements that you want to enter:> ");
    int n;
    fscanf(stdin,"%d",&n);
    printf("\n     Enter the elements one by one:> ");
    for (register int i=0; i<n && k<100; ++i) {
        fscanf(stdin, "%d", &(word+k)->value);
        (word + k)->bit = 1;
        ++k;
    }
    if (k==100){
        sleep(1);
        printf("\n\n     Sorry! No space available in main memory!\n\n");
    }
    else {
        sleep(1);
        printf("\n\n     Thank you!! All the values are safely stored in the main memory.\n");
        printf("\n________________________________________________________________________\n\n");
    }
}

void search(data *arr,int key, data *cache) { //Search in the main memory for the key.
    bool search_i = false;
    for (int i=0; i<100; ++i) {
        if (((arr+i)->value) == key && ((arr + i)->bit)) {
            search_i = true;
            sleep(4);
            printf("\n\n    Element found in main memory!!!!");
            printf("\n      The element is at location : %p\n", (void *) &((arr + i)->value));
            printf("\n      Modifying the cache memory.......\n\n");
            printf("\n      Done!\n\n");
            printf("\n________________________________________________________________________");
            replace(arr, cache, (int)ceilf((float)(i+1)/sizeof(int)));
            break;
        }
    }
    if (!search_i){
        sleep(4);
        printf("\n\n     Sorry!! Element not found at main memory!\n\n");
    }

}

void cache_search(data *cache, int key, data *word) {   //Search in the cache memory for the key.
    printf("\n\n------------------------------------------------------------\n");
    printf("    Enter the element you want to search for :> ");
    fscanf(stdin, "%d", &key);
    bool search_found = false;
    int i=0;
    for (i=0; i<12; ++i) {
        if(((cache + i)->value) == key && ((cache + i)->bit)){
            search_found = true;
            break;
        }
    }
    if (!search_found){
        sleep(2);
        printf("\n\n     MISS!! Element not found in cache memory!");
        sleep(1);
        printf("\n      Searching in Main Memory..................!");
        search(word, key, cache);
    }
    else {
        sleep(1);
        printf("\n\n      HIT!! Element found in cache memory!");
        printf("\n      The element is at location : %p\n", (void *) &((cache + i)->value));
    }
}


int main() {

    data *arr = (data *) calloc(100, sizeof(data));
    data *cache = (data *) calloc(12, sizeof(data));

    printf("\n ******************************************************\n\n");
    printf("       MEMORY VISUALIZATION TOOL:-      \n\n");
    printf("  N.B > Maximum Value of main memory=100 elements.\n\n");
    printf("  N.B > By default each value of main memory and cache is set to zero !!!\n\n");
    LOOP: printf("\n ******************************************************\n");
    printf("  1. View the current memory\n");
    printf("  2. Add elements in main memory\n");
    printf("  3. Search for an element\n");
    printf("  4. Quit the tool.\n");
    printf("\n  Your choice :> ");
    int choice,go_back = 0 ;
    fscanf(stdin, "%d", &choice);
    switch(choice) {
        case 1:
            output(arr, cache);
            printf("\n\n  Do you want to go back to Menu? (1/0) :> ");
            fscanf(stdin,"%d",&go_back);
            if (go_back)
                goto LOOP;
            else
                goto EX;
        case 2:
            memory(arr);
            printf("\n\n  Do you want to go back to Menu? (1/0) :> ");
            fscanf(stdin,"%d",&go_back);
            if (go_back)
                goto LOOP;
            else
                goto EX;
        case 3:
            cache_search(cache, 0, arr);
            printf("\n\n  Do you want to go back to Menu? (1/0) :> ");
            fscanf(stdin,"%d",&go_back);
            if (go_back)
                goto LOOP;
            else
                goto EX;
        EX:case 4:
            printf("\n\n   Exiting.................\n\n\n");
            free(arr);
            free(cache);
            sleep(2);
            exit(0);
        default:
            printf("\n\n   Sorry! Wrong choice provided!\n\n");
            printf("\n\n  Do you want to go back to Menu? (1/0) :> ");
            fscanf(stdin,"%d",&go_back);
            if (go_back)
                goto LOOP;
            else
                goto EX;
    }
    return EXIT_SUCCESS;
}