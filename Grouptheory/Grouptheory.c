/* 
 * File:   main.c
 * Author: aghosh
 *
 * Created on 5 November, 2012, 3:13 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define true 1
#define false 0
#define infinity -100//To indicate the number cannot be generated
#define largenumber 1000//to make a reference for the least steps.We assume a large value
/*
 * 
 */
int numberofgeneratingelements, numbertogenerate;
int *generatingset, counter1 = 0;
int *Sequencegenerate, counter = 0, *constructarray;
int **findsequence;
int flag = 0;
//Prototypes of all the functions
void Generate(int togenerate, int generatingelement);
void QuickSort(int *array, int from, int to);
int CheckAlreadyPresent(int i, int *A, int numberoftime);
int CheckPath(int number1, int number2);
void GenerateSeq(int togenerate);
void DisplayGeneration();

int main(int argc, char** argv) {
    Sequencegenerate = (int *) malloc(100 * sizeof (int));
    int i, j, k = 0;
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("The file could not be opened\n");
        exit(-1);
    }

    fscanf(fp, "%d", &numberofgeneratingelements);
    generatingset = (int *) malloc(numberofgeneratingelements * sizeof (int)); //Allocating memory for generating set
    constructarray = (int *) malloc(100 * sizeof (int));
    for (i = 0; i < numberofgeneratingelements; i++) {
        fscanf(fp, "%d", &generatingset[i]);

    }


    fscanf(fp, "%d", &numbertogenerate);
    findsequence = (int**) malloc((numbertogenerate + 1) * sizeof (int*));
    for(i=0;i<numbertogenerate+1;i++)
        findsequence[i]=(int *)malloc(3*sizeof(int));


    if (numberofgeneratingelements == 1) {
        if (numbertogenerate % generatingset[0] != 0)
            printf("The element %d cannot be generated from %d", numbertogenerate, generatingset[0]);
        else {
            printf("The number %d has been generated \n", numbertogenerate);
            printf("The numbers generated to generate the given number are\n");
            for (i = 0; i <= log2(numbertogenerate / generatingset[0]); i++) {
                printf("%d", (int) pow(2, i) * generatingset[0]);
                if (i != 0)
                    printf("(%d +%d)", (int) pow(2, i - 1) * generatingset[0], (int) pow(2, i - 1) * generatingset[0]);
                if (i != (int) (log2(numbertogenerate / generatingset[0])))
                    printf(",");
                k++;
            }
            printf("\n");
            printf("The generating sequence is \n");
            Generate(numbertogenerate / generatingset[0], 2);
            for (i = counter - 1; i >= 0; i--) {
                printf(" %d ", Sequencegenerate[i] * generatingset[0]);
                if (i != 0)
                    printf("+");
            }
            printf("=%d", numbertogenerate);


            printf("\nThe number of times + operator is used is(the number of times addition is required)= %d", counter + k - 2);

        }

    }
    else {
        QuickSort(generatingset, 0, numberofgeneratingelements - 1); //to sort the generating set
        
        for (i = 0; i <= numbertogenerate; i++)
        {
            if (CheckAlreadyPresent(i, generatingset, numberofgeneratingelements)) {
           
            findsequence[i][2] = 0;

        }else
            findsequence[i][2] = infinity;
        }
            

        GenerateSeq(numbertogenerate); //Function to find the generating sequence

        if (findsequence[numbertogenerate][2] == infinity)
            printf("The number %d cannot be generated from the given generating set\n", numbertogenerate);
        else {
            printf("The number of times + operator is  used to generate %d from the given generating set is %d\n", numbertogenerate, findsequence[numbertogenerate][2]);
            printf("The sequence of generation in the reverse order is \n");
            DisplayGeneration(numbertogenerate);

        }


    }
    //Freeing all the allocated memory and closing the file pointer
    free(Sequencegenerate);
    free(generatingset);
    free(constructarray);
    
    for(i=0;i<numbertogenerate+1;i++)
    free(findsequence[i]);
    fclose(fp);
    return (EXIT_SUCCESS);
}

/*The function finds the numbers used to generate the given number if there is a single
 generating element.It makes use of a simple Binary number concept.The complexity is logn
 .We find basically all the powers of two required to generate this number.We should
 however note that this is not the most optimal method(Eg:It fails for 15)
 */
void Generate(int togenerate, int generatingelement) {
    int n, i;

    n = (int) (log2(togenerate) / log2(generatingelement));
    if ((togenerate != (int) pow(generatingelement, n))) {
        Sequencegenerate[counter++] = (int) pow(generatingelement, n);
        Generate((togenerate - (int) pow(generatingelement, n)), generatingelement);
    } else {
        Sequencegenerate[counter++] = (int) pow(generatingelement, n);
        return;
    }

}

void QuickSort(int *array, int from, int to) {
    if (from >= to)return;
    int pivot = array[from]; /*Pivot I am chosing is the starting element */
    /*Here i and j are such that in the array all elements a[from+1...i] are less than pivot,
      all elements a[i+1...j] are greater than pivot and the elements a[j+1...to] are which 
      we have not seen which is like shown below.
       
          
      If the new element we encounter than >=pivot the above variant is still satisfied.
      If it is less than pivot we swap a[j] with a[i+1].
     */
    int i = from, j, temp;
    for (j = from + 1; j <= to; j++) {
        if (array[j] < pivot) {
            i = i + 1;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    temp = array[i];
    array[i] = array[from];
    array[from] = temp;

    /*Recursively sort the two sub arrays */
    QuickSort(array, from, i - 1);
    QuickSort(array, i + 1, to);
}

/*The function checks if i is present in The Array A*/
int CheckAlreadyPresent(int i, int *A, int numberoftime) {
    int j;
    for (j = 0; j < numberoftime; j++)
        if (A[j] == i)return true;
    return false;

}

/*The function checks if number 1 can be generated using number 2*/
int CheckPath(int number1, int number2) {
    int i;
    if (CheckAlreadyPresent(number1, generatingset, numberofgeneratingelements))
        return false;

    for (i = 0; i < 2; i++) {
        if (!CheckAlreadyPresent(findsequence[number1][i], generatingset, numberofgeneratingelements))
            if (CheckPath(findsequence[number1][i], number2))
                return true;
    }
    if (findsequence[number1][0] == number2 || findsequence[number1][1] == number2)
        return true;
    return false;


}

/*The below function finds all the possible ways to generate a number
 We try to generate all possible numbers from the smallest element to the number to
 be generated. Initially we set them all to -1 meaning we cannot generate them.The solution
 here is not the most optimal as it prefers the path near i/2 which need not be the case*/
void GenerateSeq(int togenerate) {
    int i, j, leaststeps = largenumber, k = 0, check1, check2;

    for (i = generatingset[0]; i <= togenerate; i++) 

        if (!CheckAlreadyPresent(i, generatingset, numberofgeneratingelements)) {
           
           

         
            leaststeps = largenumber;
            for (j = generatingset[0]; j <= i / 2; j++) {
                k = 0;
                if (findsequence[j][2] >= 0 && findsequence[i - j][2] >= 0) {

                    if (j == i - j || CheckPath(i - j, j)) {
                        check1 = findsequence[i - j][2] + 1;

                        if (leaststeps > check1) {

                            k = 1;
                            leaststeps = check1;
                        }


                    } else {
                        /*This  finds out the least number of steps used to generate a number x
         and stores the path too..Thus every possible number is generated using the least
         number of steps*/
                        check2 = findsequence[j][2] + findsequence[i - j][2] + 1; //Total steps to generate 
                        //is steps needed to generate both and then 1 to add them


                        if (check2 < leaststeps) {

                            leaststeps = check2;
                            k = 1;
                        }
                    }
                    if (k) {
                        findsequence[i][0] = j;
                         findsequence[i][1] = i - j; //for storing the path
                          findsequence[i][2] = leaststeps;
                    }
                }



                
                    
                    //therefore for every number we get the least number 
                
            }       //of steps to generate it
        }
}

    



/*The function displays the path through which we generate the given number*/
void DisplayGeneration(int numbertogen) {

    if (!CheckAlreadyPresent(numbertogen, generatingset, numberofgeneratingelements) && !CheckAlreadyPresent(numbertogen, constructarray, counter1)) {
        flag = 1;
        constructarray[counter1++] = numbertogen;
        printf("%d =%d +%d \n", numbertogen, findsequence[numbertogen][0], findsequence[numbertogen][1]);
        if (findsequence[numbertogen][0] > findsequence[numbertogen][1]) {
            DisplayGeneration(findsequence[numbertogen][0]);

            DisplayGeneration(findsequence[numbertogen][1]);
        } else {
            DisplayGeneration(findsequence[numbertogen][1]);

            DisplayGeneration(findsequence[numbertogen][0]);
        }
    }
    if (!flag)
        printf("%d=%d ", numbertogen, numbertogen);

}