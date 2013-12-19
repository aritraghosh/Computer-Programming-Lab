/* 
 * File:   main.c
 * Author: aghosh
 *
 * Created on 24 September, 2012, 2:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>


#define MAX  60        // We declare MAX  as a constant =  60


//We define a structure for the items that can be stolen

typedef struct it {
    char name[MAX];
    int weight;
    int value;
    float valweight;
} ite;


//NOTE:All the variables are global .So they can directly be used in functions
ite *item;
int *pattern = NULL, *BinaryString = NULL;
int numberofitems, maxweight, max = 0, i, sum, valuetotal = 0, maxmerge = 0;
int B[50];

//Prototype of the functions
void enumBString(int);
void Findmax(int);
void MergeSort(int left, int right);
void merge(int left, int mid, int right);
void GreedyAlgorithm(int W, int n);

/*
 * 
 */
int main(int argc, char** argv) {
    int numberoftimes, j;
    char filename[50];
    FILE *fp;

    numberoftimes = atoi(argv[1]); //to convert string to an integer
    for (j = 1; j <= numberoftimes; j++) {
        for (i = 0; i < 50; i++)
            B[i] = 0;//All the elements are initialized to zero initially.Then changed if the item is taken
        maxmerge = 0, max = 0;//Each time they have to be initialized to 0


        char a[5];
        sprintf(a, "%d", j);

        strcpy(filename, argv[2]);
        strcat(filename, "_"); //Editing the file name
        strcat(filename, a);
        strcat(filename, ".txt");







        fp = fopen(filename, "r");
        if (fp == NULL) {
            printf("The files could not be opened");
            exit(-1);
        }


        fscanf(fp, "%d", &maxweight);
        fscanf(fp, "%d", &numberofitems);

        pattern = (int*) malloc(numberofitems * (sizeof (int))); // allocating memory dynamically    
        item = (ite*) malloc(numberofitems * sizeof (ite));
        BinaryString = (int*) malloc(numberofitems * (sizeof (int)));




        for (i = 0; i < numberofitems; i++) {
            fscanf(fp, "%s", item[i].name);
            fscanf(fp, "%d", &item[i].weight); //accepting the inputs
            fscanf(fp, "%d", &item[i].value);
            item[i].valweight = (float) item[i].value / item[i].weight;
        }


        enumBString(0); //Function call
        //if (max)
        printf(" %d  ", max);
        for (i = 0; i < numberofitems; i++)
            if (pattern[i] == 1) { //prints only when the item is taken i.e pattern is 1 

                printf("%s ", item[i].name);
            }




        //if (max == 0)

        //printf("Such a robbery is not feasible\n");


        printf(" : "); //Required format 

        MergeSort(0, numberofitems - 1);

        GreedyAlgorithm(maxweight, numberofitems);
        printf("%d ", maxmerge);

        for (i = 0; i < numberofitems; i++)
            if (B[i] == 1)
                printf("%s ", item[i].name); //Prints only when the item is included
        printf("\n");

        free(BinaryString);
        free(pattern); //freeing the memory allocated dynamically
        free(item);



        fclose(fp);
    }//End of for loop 



    return (EXIT_SUCCESS);
}

//Function to enumerate the n bits of string and calls Find max function 

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


//Function to merge sort the Array of weight/value

void merge(int left, int mid, int right) {
    ite temparray[right - left + 1];
    int pos = 0, l = left, r = mid + 1;
    while (l <= mid && r <= right) {
        if (item[l].valweight >= item[r].valweight)

            temparray[pos++] = item[l++];
        else
            temparray[pos++] = item[r++];
    }
    while (l <= mid) temparray[pos++] = item[l++];
    while (r <= right)temparray[pos++] = item[r++];
    int i; //Merging the two sorted Arrays
    for (i = 0; i < pos; i++)
        item[i + left] = temparray[i];
}

void MergeSort(int left, int right) {
    int mid = (left + right) / 2;
    if (left < right) {
        MergeSort(left, mid); //calling recursively to sort the first half
        MergeSort(mid + 1, right); //calling recursively to sort the second half
        merge(left, mid, right); //Merging the two sorted parts
    }

}




//Function to implement the greedy algorithm

void GreedyAlgorithm(int W, int n) {
    for (i = 0; i < n; i++)
        if (item[i].weight <= W) {
            B[i] = 1; //Including in the Knapsack
            W = W - item[i].weight;
            maxmerge += item[i].value;
        }

}