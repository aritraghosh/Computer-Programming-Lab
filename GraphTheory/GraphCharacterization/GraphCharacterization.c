/* 
 * File:   main.c
 * Author: aghosh
 *
 * Created on 15 October, 2012, 2:21 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */


#define true 1
#define false 0

int **CopyMatrix;
int **Adjacencymatrix;
FILE *fp;
int numberofvertices;
int cyclic;



//Prototypes of all the functions used
void TransitiveClosure(int **);
int Allone(int **A);
void Displaymatrix(int **A);
int EdgeCheck(int *A, int size);
void ConnectedComponents(int **A);
int CheckAlreadyPresent(int i, int *A, int numberoftime);
int Bipartite(int *A, int size);
int Edgeexists(int *A, int size, int i);
int InternalEdge(int *A, int size);



int main(int argc, char** argv) {
    int i, j;
    int connected = 0;

    fp = fopen(argv[1], "r");
    fscanf(fp, "%d", &numberofvertices);
    Adjacencymatrix = (int **) malloc(numberofvertices * sizeof (int*));
    CopyMatrix = (int **) malloc(numberofvertices * sizeof (int*));

    for (i = 0; i < numberofvertices; i++) {

        Adjacencymatrix[i] = (int *) malloc(numberofvertices * sizeof (int));
        CopyMatrix[i] = (int *) malloc(numberofvertices * sizeof (int));

        for (j = 0; j < numberofvertices; j++) {
            fscanf(fp, "%d", &Adjacencymatrix[i][j]);



           
        }
        
    }

    for (i = 0; i < numberofvertices; i++) {
        Adjacencymatrix[i][i]=0;
        for (j = 0; j < numberofvertices; j++) {
            if (Adjacencymatrix[i][j] | Adjacencymatrix[j][i]) {
                Adjacencymatrix[i][j] = 1;
                Adjacencymatrix[j][i] = 1;

            }
            CopyMatrix[i][j] = Adjacencymatrix[i][j]; //We create a copy of Matrix as
                                                    //The transitive closure alters it
         



        }
       
    }

    TransitiveClosure(CopyMatrix);
    printf("The matrix after modification\n");
    Displaymatrix(Adjacencymatrix);
    
    if (Allone(CopyMatrix)) {
        printf("The graph is connected\n");
        connected = 1;
    } 
    else
        printf("The graph is not connected\n");

    //for(i=0;i<numberofvertices;i++)
    //CopyMatrix[i][i]=0;
    ConnectedComponents(CopyMatrix);
    
    
    //A connected acyclic graph is called a tree
    if (connected &!cyclic)
        printf("The graph is a tree\n");
    else
        printf("The graph is not a tree\n");








    for (i = 0; i < numberofvertices; i++) {
        free(Adjacencymatrix[i]);
        free(CopyMatrix[i]);
    }

    return (EXIT_SUCCESS);
}

/*The function computes the Transitive closure of a graph by Warshall's algorithm*/

void TransitiveClosure(int **Matrix) {

    int i, j, k;
    for (k = 0; k < numberofvertices; k++)
        for (i = 0; i < numberofvertices; i++)

            for (j = 0; j < numberofvertices; j++) {



                Matrix[i][j] = Matrix[i][j] | ((Matrix[i][k]) && (Matrix[k][j]));
            }
}

/*The function checks if all the elements in a 2-D array are one*/
int Allone(int **A) {
    int i, j;

    for (i = 0; i < numberofvertices; i++)

        for (j = 0; j < numberofvertices; j++) {


            if (!A[i][j])
                return false;
        }
    return true;
}

/*The below function is a trivial function to display the contents of a matrix*/
void Displaymatrix(int **A) {
    int i, j;

    for (i = 0; i < numberofvertices; i++) {
        for (j = 0; j < numberofvertices; j++)

            printf("%d", A[i][j]);

        printf("\n");
    }
}

/*The function breaks the transitive closure into connected components and for 
 each connected component we check if the number of edges is greater than the number of
 vertices then it is cyclic(self loops excluded)*.It also checks if Graph is bipartite*/
void ConnectedComponents(int **A) {
    int i, j, k, bipartite;
    cyclic = 0;
    bipartite = 1;
    int *Array1, *Array2;
    int counter1 = 0;
    int counter2 = 0;
    Array1 = (int *) malloc(numberofvertices * sizeof (int));
    Array2 = (int *) malloc(numberofvertices * sizeof (int));
    printf("Connected component(s) of the graph\n");
    for (i = 0; i < numberofvertices; i++) {
        if (!CheckAlreadyPresent(i, Array2, counter2)) {
            counter1 = 0;
            Array1[counter1++] = i;
            Array2[counter2++] = i;
            for (j = 0; j < numberofvertices; j++) {
                if (A[i][j] && !(i == j)) {
                    Array1[counter1++] = j;
                    Array2[counter2++] = j;
                }
            }
            for (k = 0; k < counter1; k++)
                printf("%c ", Array1[k] + 97);
            printf("\n");

            if (EdgeCheck(Array1, counter1)) {
               
                cyclic = 1;
                if (Bipartite(Array1, counter1)) {
                    bipartite = 0;
                }
               

            }
        }








    }

    if (cyclic) {
        printf("The graph is cyclic\n");
        if (bipartite)
            printf("The graph is bipartite\n");
        else
            printf("The graph is not bipartite\n");
    } 
    else {
        printf("The graph is not cyclic\n");

        printf("The graph is bipartite\n");
    }
    free(Array1);
    free(Array2);

}

/*The function checks if the number of edges in a graph is greater than number
 of vertices*/
int EdgeCheck(int *A, int size) {
    int i, j, count;
    count = 0;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (Adjacencymatrix[A[i]][A[j]] && !(i == j))
                count++;
    //  printf("%d",count);
    if ((count / 2) < size)
        return false;

    return true;
}

/*The function checks if i is present in The Array A*/
int CheckAlreadyPresent(int i, int *A, int numberoftime) {
    int j;
    for (j = 0; j < numberoftime; j++)
        if (A[j] == i)return true;
    return false;



}
/*This function checks if a given connected component is bipartite.We first assign
 * the first element to the first matrix and then check it's neighbours.We continue till
 * we have made a possible bipartiton.Then we check if there are internal edges in 
 * the partition 2.If there is atleast one edge then it is not bipartite else
 * the component is biparite
 */
int Bipartite(int *A, int size) {
    int *Arrayx, *Arrayy;
    int counter1 = 0;
    int counter2 = 0;
    Arrayx = (int *) malloc(numberofvertices * sizeof (int));
    Arrayy = (int *) malloc(numberofvertices * sizeof (int));
    int i, j, k;
    Arrayx[counter1++] = A[0];

    while (counter1 + counter2 < size) {
       
        for (j = 1; j < size; j++) {
            if (Edgeexists(Arrayx, counter1, A[j]) && !CheckAlreadyPresent(A[j], Arrayy, counter2))
                Arrayy[counter2++] = A[j];
            else if (Edgeexists(Arrayy, counter2, A[j]) && !CheckAlreadyPresent(A[j], Arrayx, counter1))
                Arrayx[counter1++] = A[j];
        }
    }
    free(Arrayx);
    if (InternalEdge(Arrayy, counter2)) {
        free(Arrayy);
        return true;
    } else {
        free(Arrayy);
        return false;
    }



}
/*The function checks if there is a edge between the vertex i and Matix A*/
int Edgeexists(int *A, int size, int i) {
    int j;
    for (j = 0; j < size; j++)
        if (Adjacencymatrix[A[j]][i] && !(A[j] == i))
            return true;
    return false;
}
/*This function checks if there are internal edges in the partition*/
int InternalEdge(int *A, int size) {
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (!(i == j) && Adjacencymatrix[A[i]][A[j]])
                return true;
    return false;
}

