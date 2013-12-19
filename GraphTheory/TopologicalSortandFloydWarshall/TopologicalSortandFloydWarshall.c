/* 
 * File:   main.c
 * Author: aghosh
 *
 * Created on 8 October, 2012, 2:08 PM
 */

#include<stdio.h>
#include<stdlib.h>
#define true 1
#define false 0
FILE *fp;

struct matrix {
    int size;
    int **array;
};
int *Array1, *Array2;
int counter1 = 0, counter2 = 0;
int numberofvertices;
//prototypes of all the functions
int AcceptMatrix(struct matrix *p, int);
void InputMatrix(struct matrix *p);
int Equivalence(struct matrix *p);
int PartialOrder(struct matrix*p);
void TransitiveClosure(struct matrix *p);
void WarshallAlgorithm1(struct matrix *, int);
void Equivalenceclass(struct matrix *p);
void TopologicalSort(struct matrix *p);
int CheckAllzero(struct matrix *p);
int CheckAlreadyPresent(int i, int *A, int numberoftimes);
void WarshallAlgorithm2(struct matrix*p);

int main(int argc, char** argv) {

    struct matrix Relation;
    int i, j, t = 0;



    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("The file could not be opened");
        exit(-1);
    }
    fscanf(fp, "%d", &numberofvertices);

    if (AcceptMatrix(&Relation, numberofvertices))
        InputMatrix(&Relation);

    if (Equivalence(&Relation)) {
        printf("It is a equivalence relation.The partitions are arranged as\n");
        Equivalenceclass(&Relation);
    } else
        printf("It is not an equivalence relation\n");
    printf("The transitive closure of the given adjacency matrix is\n");
    t = PartialOrder(&Relation);
    WarshallAlgorithm2(&Relation);
    if (t) {


        printf("It is a partial order.\nThe topologically sorted list from base  is\n");
        Array1 = (int *) malloc(numberofvertices * sizeof (int));
        Array2 = (int *) malloc(numberofvertices * sizeof (int));
        TopologicalSort(&Relation);
        free(Array1);
        free(Array2);
        printf("\n");
    }
    else
        printf("It is not a partial order\n");


    // WarshallAlgorithm1(&Relation,1);


    return (EXIT_SUCCESS);
}

//Function to allocate memory for the matrix

int AcceptMatrix(struct matrix *p, int ord) {
    int i;
    p->size = ord;
    p->array = (int **) malloc(ord * sizeof (int *)); //allocating memory to elements

    for (i = 0; i < ord; i++) {
        p->array[i] = (int *) malloc(ord * sizeof (int));
        if (p->array == NULL)
            return (0); //to know if the function could allocate memory
    }
    return (1);
}






//function to input elements of the matrix

void InputMatrix(struct matrix *p) {
    int i, j;
    for (i = 0; i < p->size; i++) {
        for (j = 0; j < p->size; j++) {



            fscanf(fp, "%d", &(p->array[i][j]));
            printf("%d\t", p->array[i][j]);
        }
        printf("\n");
    }
}

/*Function to check if the given relation is equivalent-reflexive,symmetric,transitive*/
int Equivalence(struct matrix *p) {
    int i, j, k;
    for (i = 0; i < p->size; i++)
        if (p->array[i][i] == 0)
            return false;
    for (i = 0; i < p->size; i++)
        for (j = 0; j < p->size; j++)
            if (p->array[i][j] != p->array[j][i])
                return false;
    for (i = 0; i < p->size; i++)
        for (j = 0; j < p->size; j++)
            for (k = 0; k < p->size; k++)
                if (p->array[i][j] && p->array[j][k])
                    if (!(p->array[i][k]))
                        return false;

    return true;

}

/*Function that checks if the relation is a partial order-reflexive,antisymmetric,transitive*/
int PartialOrder(struct matrix*p) {
    int i, j, k;
    for (i = 0; i < p->size; i++)
        if (!(p->array[i][i]))
            return false;
    for (i = 0; i < p->size; i++)
        for (j = 0; j < p->size; j++)
            if (i != j)

                if (p->array[i][j] && p->array[j][i])

                    return false;
    for (i = 0; i < p->size; i++)
        for (j = 0; j < p->size; j++)
            for (k = 0; k < p->size; k++)
                if (p->array[i][j] && p->array[j][k])
                    if (!(p->array[i][k]))
                        return false;

    return true;

}

/*The function finds the transitive closure of a relation R* */
void WarshallAlgorithm1(struct matrix *p, int k) {
    int i, j;
    if (k == p->size + 1) {
        for (i = 0; i < p->size; i++) {
            for (j = 0; j < p->size; j++) {

                printf("%d", p->array[i][j]);
            }
            printf("\n");
        }
        return;

    } else {
        for (i = 1; i < p->size; i++)

            for (j = 1; j < p->size; j++) {


                p->array[i][j] = (p->array[i][j]) | ((p->array[i][k]) && (p->array[k][j]));
            }

    }

    WarshallAlgorithm1(p, k + 1); //Calling the algorithm recursively to finally evaluate R*







}

void WarshallAlgorithm2(struct matrix*p) {
    int i, j, k;
    for (k = 0; k < p->size; k++)
        for (i = 0; i < p->size; i++)

            for (j = 0; j < p->size; j++) {



                p->array[i][j] = p->array[i][j] | ((p->array[i][k]) && (p->array[k][j]));
            }

    for (i = 0; i < p->size; i++) {
        for (j = 0; j < p->size; j++) {

            printf("%d", p->array[i][j]);
        }
        printf("\n");
    }




}

/*This function finds the equivalence classes if the given relation is a equivalence relation*/
void Equivalenceclass(struct matrix *p) {
    int i, j, k = 1;
    int *partition;
    partition = (int *) malloc(numberofvertices * (sizeof (int)));
    for (i = 0; i < numberofvertices; i++)
        partition[i] = 0;
    for (i = 0; i < numberofvertices; i++) {
        if (!partition[i])//To check if the vertex has been alloted any partition
        {
            partition[i] = k;
            for (j = 0; j < numberofvertices; j++)
                if (p->array[i][j]) {
                    partition[j] = k; //Give the jth vertex same partition as i th if they are adjacent

                }
            k++;
        }
    }
    for (i = 0; i < numberofvertices; i++) {
        printf("vertex %c - parition %d ", i + 97, partition[i]);

        printf("\n");
    }
    free(partition);
}

/* The function checks if at all there are any edges in the relation*/
int CheckAllzero(struct matrix *p) {
    int i, j;
    for (i = 0; i < p->size; i++)
        for (j = 0; j < p->size; j++)
            if (p->array[i][j])return (0);
    return 1;
}

/*The function checks if the vertex i is present in the array A with size-numberoftimes*/

int CheckAlreadyPresent(int i, int *A, int numberoftimes) {
    int j;
    for (j = 0; j < numberoftimes; j++)
        if (A[j] == i)return (1);
    return 0;



}

/*The function sorts a partial order in  a topological list and displays it.*/
void TopologicalSort(struct matrix *p) {
    counter1 = 0;
    int i, j, flag;
    for (i = 0; i < p->size; i++) {
        flag = 0;
        for (j = 0; j < p->size; j++) {

            if (p->array[j][i] && (i != j)) {

                flag = 1;

                break;
            }
        }
        if (flag == 0 && !CheckAlreadyPresent(i, Array2, counter2)) {
            Array1[counter1++] = i;
            Array2[counter2++] = i;


        }

    }
    for (i = 0; i < counter1; i++)
        printf(" %c ", Array1[i] + 97);
    printf("\n");
    for (i = 0; i < counter1; i++)
        for (j = 0; j < p->size; j++)
            if (p->array[Array1[i]][j])
                p->array[Array1[i]][j] = 0; //Make it the new bottom level


    if (!CheckAllzero(p))TopologicalSort(p); //Go to the higher level
}