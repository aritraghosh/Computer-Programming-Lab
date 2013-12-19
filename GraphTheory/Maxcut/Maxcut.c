/* 
 * File:   main.c
 * Author: aghosh
 *
 * Created on 29 October, 2012, 2:10 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
#define true 1
#define false 0
FILE *fp;
int **CopyMatrix;
int **Adjacencymatrix;
int numberofvertices;
int maxcrossedges=0;
int *Array1,*Array2,*Arrayx,*Arrayy;
int counterx=0,countery=0;
int *array1,*array2;
int isPresent(int i,int *A,int size);
int a=0;
int b;
int counter=0;
void Displaymatrix(int **A);
void TryBruteForce(int pos,int *bstring);
int findedges(int *ArrayA,int *ArrayB,int size1,int size2);
void Copy(int *A,int *B,int size );
void Displaymatrix1(int *A,int size);
void DisplayBruteForceAnswer(int *);
void DisplayMaxEdges(int *Arrayx,int *Arrayy,int counterx,int countery);
void GreedyAlgorithm(int *A,int *B);
int edgefind(int j,int *Array,int size);
void ChangeB(int i,int *Array,int size);
void GreedyAlgorithm2(int *A,int *B);
void QuickSort(int *array, int from, int to);

void DisplayGreedyAlgorithm();

int main(int argc, char** argv) {

    int i,j;
    int *bstring;
    
    
    fp = fopen(argv[1], "r");
    if(fp==NULL)
    {
        printf("File could not be opened\n");
        exit(-1);
    }
    fscanf(fp, "%d", &numberofvertices);
    bstring=(int *)malloc(numberofvertices*sizeof(int));
    Adjacencymatrix = (int **) malloc(numberofvertices * sizeof (int*));
    CopyMatrix = (int **) malloc(numberofvertices * sizeof (int*));//Copy of the matrix
    array1=(int *)malloc(numberofvertices*sizeof(int));
    array2=(int *)malloc(numberofvertices*sizeof(int));
      for(i=0;i<numberofvertices;i++)
          array2[i]=i;
      b=numberofvertices;
    for (i = 0; i < numberofvertices; i++) {

        Adjacencymatrix[i] = (int *) malloc(numberofvertices * sizeof (int));
        CopyMatrix[i] = (int *) malloc(numberofvertices * sizeof (int));
        Arrayx=(int *)malloc(numberofvertices*sizeof(int));
       Arrayy=(int *)malloc(numberofvertices*sizeof(int));

        for (j = 0; j < numberofvertices; j++) {
            fscanf(fp, "%d", &Adjacencymatrix[i][j]);



           
        }
        
    }

    for (i = 0; i < numberofvertices; i++) {
        Adjacencymatrix[i][i]=0;
        for (j = 0; j < numberofvertices; j++) {
            if (Adjacencymatrix[i][j] | Adjacencymatrix[j][i]) {
                Adjacencymatrix[i][j] = 1;//The graph is undirected
                Adjacencymatrix[j][i] = 1;

            }
            CopyMatrix[i][j] = Adjacencymatrix[i][j]; 
                                                   
         



        }
       
    }
    
    
    //printf("The matrix after modification\n");
   // Displaymatrix(Adjacencymatrix);
    
     //DisplayBruteForceAnswer(bstring);//For the correct answer
       for(i=0;i<6;i++)
       {
      GreedyAlgorithm(array1,array2);
    GreedyAlgorithm(array1,array2);
    GreedyAlgorithm(array1,array2);
       }
    
    for(i=0;i<6;i++)
    {
     GreedyAlgorithm2(array1,array2);
     GreedyAlgorithm2(array1,array2);
     GreedyAlgorithm2(array1,array2);
     GreedyAlgorithm2(array1,array2);
    }
    
       QuickSort(array1,0,a-1);
       DisplayGreedyAlgorithm();
    
     
   
    for (i = 0; i < numberofvertices; i++) {
        free(Adjacencymatrix[i]);
        free(CopyMatrix[i]);
    }
     free(array1);
     free(array2);
     free(Array1);
     free(Array2);
     free(Arrayx);
     free(Arrayy);
    return (EXIT_SUCCESS);
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


/*The function implements the Brute Force algorithm by taking every possible cut
 and checking the number of edges and searching for the maximum case*/
void TryBruteForce(int pos,int *bstring)
{
    
Array1=(int *)malloc(numberofvertices*sizeof(int));
Array2=(int *)malloc(numberofvertices*sizeof(int));

    int i,counter1,counter2,crossedges;
    
    if(pos==numberofvertices)
    {
        counter1=0;
        counter2=0;
        //Displaymatrix1(bstring,numberofvertices);
    
    for(i=0;i<numberofvertices;i++)
        
    {
      if(bstring[i])
          Array1[counter1++]=i;
      else
          Array2[counter2++]=i;
     
    }
       
       // Displaymatrix1(Array1,counter1);
       // Displaymatrix1(Array2,counter2);
        
    crossedges=findedges(Array1,Array2,counter1,counter2);
    //printf("CE %d\n",crossedges);
    if(maxcrossedges<crossedges)
    {
        maxcrossedges=crossedges;
        counterx=counter1;
        countery=counter2;
        //printf("\t %d %d \n",counterx,countery);
        //Displaymatrix1(Arrayx,counterx);
        Copy(Array1,Arrayx,counterx);
       // Displaymatrix1(Arrayx,counterx);
        Copy(Array2,Arrayy,countery);
        
        
    }
    
    }
     if(pos<numberofvertices)
    {
        
        bstring[pos]=0;
        TryBruteForce(pos+1,bstring);
        bstring[pos]=1;
        TryBruteForce(pos+1,bstring);
        
    }
    
           
    
  // Displaymatrix1(Arrayx,counterx); 
    
}
/*The function finds the number of edges between ArrayA and ArrayB*/
int findedges(int *ArrayA,int * ArrayB,int size1,int size2)
{
    int edges=0;
    int i,j;
    for(i=0;i<size1;i++)
        for(j=0;j<size2;j++)
            if(Adjacencymatrix[ArrayA[i]][ArrayB[j]])
            {
                edges++;
               
            }
    //printf("%d",edges);
        return(edges);
}
/*the function is used to copy a matrix A to B*/
void Copy(int *A,int *B,int size)
{
    int i;
    for(i=0;i<size;i++)
        B[i]=A[i];
         
}

/*This function is used to display a 1-D matrix*/
void Displaymatrix1(int *A,int size)
{
    int i;
    for(i=0;i<size;i++)
        printf("%d ",A[i]+1);
    printf("\n");
}
void DisplayMaxEdges(int *Arrayx,int *Arrayy,int counterx,int countery)
{
  int i,j;
for(i=0;i<counterx;i++)
    for(j=0;j<countery;j++)
        if(Adjacencymatrix[Arrayx[i]][Arrayy[j]])
        {
            printf("%d-%d\n",Arrayx[i]+1,Arrayy[j]+1);
            counter++;
        }
}

void DisplayBruteForceAnswer(int *bstring)
{
     
    
    
    
    TryBruteForce(0,bstring);
    printf("The two partitions are \nPartition1\n");
    
    Displaymatrix1(Arrayx,counterx);
   printf("Partition2\n");
    Displaymatrix1(Arrayy,countery);
    printf("Max bridges=%d\n",maxcrossedges);
    printf("The bridges are\n");
    DisplayMaxEdges(Arrayx,Arrayy,counterx,countery);
    
}

/*The function is implementation of the Greedy Algorithm.It checks if for a vertex
 if the number of internal edges is greater than cross edges it is transferred to
 other set and this is continued until this can no more be done*/
void GreedyAlgorithm(int *A,int *B)
{
    int i,flag=0;
    int internaledges,crossedges;
    for(i=0;i<numberofvertices;i++)
    {
    internaledges=edgefind(i,B,b);
    crossedges=edgefind(i,A,a);
    if(internaledges>crossedges)
    {
      
        if(isPresent(i,B,b))
            
        {
              flag=1;
        A[a++]=i;
        ChangeB(i,B,b);
        b--;
        }
        
        
        
    }
    
    
    
    }
    if(flag==1)
        GreedyAlgorithm(A,B);
    else return;
    
   
        
    
  
}


void GreedyAlgorithm2(int *A,int *B)
{
    int i,flag=0;
    int internaledges,crossedges;
    for(i=0;i<numberofvertices;i++)
    {
    internaledges=edgefind(i,A,b);
    crossedges=edgefind(i,B,a);
    if(internaledges>crossedges)
    {
      
        if(isPresent(i,A,a))
            
        {
              flag=1;
        B[b++]=i;
        ChangeB(i,A,a);
        a--;
        }
        
        
        
    }
    
    
    
    }
    if(flag==1)
        GreedyAlgorithm(A,B);
    else return;
    
   
        
    
  
}


/*The function finds the number of edges from j to Array*/
int edgefind(int j,int *Array,int size)
{
    int edges=0,i;
    for(i=0;i<size;i++)
        if(Adjacencymatrix[j][Array[i]]&&!(j==Array[i]))
            edges++;
    return(edges);
}
/*The function makes alterations to Matrix after removing element i*/
void ChangeB(int i,int *Array,int size)
{
    int index,j;
    for(j=0;j<size;j++)
        if(Array[j]==i)
            index=j;
    for(j=index+1;j<size;j++)
        Array[j-1]=Array[j];
    
}
/*This function checks if elemnt i is present in an Array A*/
int isPresent(int i,int *A,int size)
{
    int j;
    for(j=0;j<size;j++)
        if(A[j]==i)
            return(true);
    return false;
}
void QuickSort(int *array, int from, int to)
{
        if(from>=to)return;
        int pivot = array[from]; /*Pivot I am chosing is the starting element */
        /*Here i and j are such that in the array all elements a[from+1...i] are less than pivot,
          all elements a[i+1...j] are greater than pivot and the elements a[j+1...to] are which 
          we have not seen which is like shown below.
       
          
          If the new element we encounter than >=pivot the above variant is still satisfied.
          If it is less than pivot we swap a[j] with a[i+1].
         */
        int i = from, j, temp;
        for(j = from + 1;j <= to;j++)
        {
                if(array[j] < pivot) 
                {
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
        QuickSort(array,from,i-1);
        QuickSort(array,i+1,to);
}
void DisplayGreedyAlgorithm()
{
    printf("The partition is  \n");
    Displaymatrix1(array1,a);
    //printf("Partition2\n");
   // Displaymatrix1(array2,b);
  
    
    printf("The bridges are\n");
     DisplayMaxEdges(array1,array2,a,b);
     printf("Max bridges=%d\n",counter);
}


