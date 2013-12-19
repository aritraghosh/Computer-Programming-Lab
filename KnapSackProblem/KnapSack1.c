/* 
 * File:   main.c
 * Author: aghosh
 *
 * Created on 17 September, 2012, 2:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX  60         // We decalre MAX  as a constant =  60


//We define a structure for the items that can be stolen

typedef struct it {
    char name[MAX];
    int weight;
    int value;
} ite;
//NOTE:All the variables are global .So they can directly be used in functions
ite *item;
int *pattern = NULL, *BinaryString = NULL;
int numberofitems, maxweight, max = 0, i, sum, valuetotal = 0;

//prototypes of the functions
void enumBString(int); //prototype of the function
void Findmax(int);

/*
 * 
 */
int main(int argc, char** argv) {


    FILE *fp;
    if (argc == 2) {
        fp = fopen(argv[1], "r"); //Use of command line,Note the the file name is replaced by argv[1]
        if (fp == NULL) {
            printf("The file could not be opened");
            exit(-1);
        }
    } else if (argc == 1)
        fp = stdin;
    fscanf(fp, "%d", &maxweight);

    fscanf(fp, "%d", &numberofitems);
    pattern = (int*) malloc(numberofitems * (sizeof (int))); // allocating memory dynamically    
    item = (ite*) malloc(numberofitems * sizeof (ite));
    BinaryString = (int*) malloc(numberofitems * (sizeof (int)));



    for (i = 0; i < numberofitems; i++) {
        fscanf(fp, "%s", item[i].name);
        fscanf(fp, "%d", &item[i].weight); //accepting the inputs
        fscanf(fp, "%d", &item[i].value);
    }


    enumBString(0); //Function call
    if (max)
        printf(" %d  ", max);
    for (i = 0; i < numberofitems; i++) {
        if (pattern[i] == 1) { //prints only when the item is taken i.e pattern is 1 

            printf("%s  ", item[i].name);
        }

    }
    printf("\n");

    if (max == 0)

        printf("Such a robbery is not feasible\n");

    free(BinaryString);
    free(pattern); //freeing the memory allocated dynamically
    free(item);



    fclose(fp);



    return (EXIT_SUCCESS);
}

//Function to ennumerate the n bits of string and calls Find max function 

void enumBString(int pos) {
    if (numberofitems == pos) {
        sum = 0;
        for (i = 0; i < numberofitems; i++) {
            sum += item[i].weight * BinaryString[i];
        }
        if (sum <= maxweight) {
            valuetotal = 0;
            for (i = 0; i < numberofitems; i++)

                valuetotal += BinaryString[i] * item[i].value;
            Findmax(valuetotal);


        }
    }
    if (pos < numberofitems) {
        BinaryString[pos] = 0;
        enumBString(pos + 1);
        BinaryString[pos] = 1;
        enumBString(pos + 1);
    }
}

//Function to find the total value that can be stolen

void Findmax(int v) {
    if (v > max) {
        max = v;


        for (i = 0; i < numberofitems; i++) {


            pattern[i] = BinaryString[i]; //stores the pattern only when total value<max       
        }
        //At last has the pattern which is necessary

    }

}
