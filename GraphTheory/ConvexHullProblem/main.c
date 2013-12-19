/* 
 * File:   main.c
 * Author: aghosh
 *
 * Created on 24 November, 2008, 5:06 PM
 */

#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

//We use a structure for each point 

typedef struct pointattribute {
    int xcord;
    int ycord;
} poin;
//this structure is used for sorting distances

typedef struct Dist {
    int x;
    int y;
    int dista;
} dist;


//Prototypes of All functions used
void ConvexHullFind(poin*);
int AllPointstoRight(poin p1, poin p2);
int SignedArea(poin, poin, poin);
int structcomp(poin p1, poin p2);
void merge(int left, int mid, int right);
void MergeSort(int left, int right);
int Inline(poin p1, poin p2, poin check);
/*
 * 
 */
poin point[100];
int numberofpoints = 0, noofsets = 0, currentindex = 0;
dist Distance[100];

int main(int argc, char** argv) {
    poin *Convexhull;
    int i, j, count, k;
    FILE *fp;
    char p[50] = "Check";
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("The file could not be opened");
        exit(-1);
    }

    //Accepting the inputs
    while (strcmp(p, "TheEnd") != 0 && numberofpoints < 100) {
        fscanf(fp, "%s", p);
        if (strcmp(p, "NewCase") == 0) {

            numberofpoints = 0;

            while (fscanf(fp, "%d", &point[numberofpoints].xcord) == 1) {
                fscanf(fp, "%d", &point[numberofpoints].ycord);
                //printf("%d ",point[numberofpoints].xcord);
                //printf("%d",point[numberofpoints].ycord);
                //printf("\n");

                numberofpoints++;
            }

            Convexhull = (poin *) malloc(numberofpoints * sizeof (poin));
            ConvexHullFind(Convexhull);
            if (numberofpoints == 1) {
                printf("%d ", point[0].xcord);
                printf("%d", point[0].ycord);

            }


            for (i = 0; i < currentindex; i++) {
                count = 0;
                printf("%d %d ", Convexhull[i].xcord, Convexhull[i].ycord);
                for (j = 0; j < numberofpoints; j++) {
                    if (structcomp(Convexhull[i], point[j]) || structcomp(Convexhull[i + 1], point[j])) {
                        continue;
                    }
                    if (Inline(Convexhull[i], Convexhull[i + 1], point[j])) {

                        Distance[count].x = point[j].xcord;
                        Distance[count].y = point[j].ycord;

                        Distance[count].dista = (point[j].xcord - Convexhull[i].xcord)*(point[j].xcord - Convexhull[i].xcord)+(point[j].ycord - Convexhull[i].ycord)*(point[j].ycord - Convexhull[i].ycord);
                        count++;
                    }
                }
                MergeSort(0, count - 1);
                for (k = 0; k < count; k++) {
                    printf("%d %d ", Distance[k].x, Distance[k].y);
                }



            }
            printf("\n");
            free(Convexhull);

        }
        //printf("\n");


    }









    fclose(fp);
    return (EXIT_SUCCESS);
}

/*The function OnvexHullFind populates the COnvexHull by finding if all
 *   points lie to the right of the line joining the current point and the
 * point to check...If this is true the point is included.And the 
termination 
 * is checked if convex hull reaches the the first convex hull find.We
 * start the Convex Hull by the point with lowest abscissa

 */
void ConvexHullFind(poin* Convexhull) {
    currentindex = 0;
    int done, i;
    poin startpoint, currentvertex, pointcheck;
    startpoint = point[0];


    for (i = 1; i < numberofpoints; i++) {
        if (startpoint.xcord > point[i].xcord)
            startpoint = point[i];
    }

    Convexhull[0] = startpoint;
    /*thefirst point in the Convex Hull is 
     * the left most point*/
    currentvertex = Convexhull[currentindex];


    if (numberofpoints == 1) {
        done = true;
    } else done = false;
    while (!done) {
        for (i = 0; i < numberofpoints; i++) {
            pointcheck = point[i];
            if (!(structcomp(pointcheck, currentvertex))) {
                if (AllPointstoRight(currentvertex, pointcheck)) {

                    break;
                }
            }
        }



        if (structcomp(Convexhull[0], pointcheck))
 {
            currentindex++;
            Convexhull[currentindex] = pointcheck;
            done = true;
        }
        else {
            //printf("HI ");
            currentindex++;
            Convexhull[currentindex] = pointcheck;
            currentvertex = pointcheck;
        }




    }
}

/*The function checks if all points of the input lie right of the line 
 * joining p1  to p2(directed)*/
int AllPointstoRight(poin p1, poin p2) {
    int i;
    for (i = 0; i < numberofpoints; i++) {
        //Checking all points to see if they lie right of the line joining 
        //p1 to p2
        if (SignedArea(p1, p2, point[i]) > 0)
            return false;

    }
    return true;

}

/*This function finds the twice the signed area of three 
 * points p1,p2,p3.the Area is positive when the point 
 *p3 is to the left of line from p1 to p2 and negative 
 * when p3 is to the right of the line */
int SignedArea(poin p1, poin p2, poin p3) {
    return
    (p1.xcord * (p2.ycord - p3.ycord) - p1.ycord * (p2.xcord - p3.xcord)+(p2.xcord * p3.ycord)-(p3.xcord * p2.ycord));
}

/*This function checks if the two points p1 and p2 are the same
 * *.if they are the same,it returns
   true else it returns false*/
int structcomp(poin p1, poin p2) {
    if ((p1.xcord == p2.xcord) && (p1.ycord == p2.ycord)) return true;

    return false;
}

/*The below functions perform Merge sort on the input points in increasing 
 * order of their abscissa.This is done because of the constraint that we
 * have to display points which are collinear also */
void merge(int left, int mid, int right) {
    dist temparray[right - left + 1];
    int pos = 0, l = left, r = mid + 1;
    while (l <= mid && r <= right) {
        if (Distance[l].dista <= Distance[r].dista)

            temparray[pos++] = Distance[l++];
        else
            temparray[pos++] = Distance[r++];
    }
    while (l <= mid) temparray[pos++] = Distance[l++];
    while (r <= right)temparray[pos++] = Distance[r++];
    int i; //Merging the two sorted Arrays
    for (i = 0; i < pos; i++)
        Distance[i + left] = temparray[i];
}

void MergeSort(int left, int right) {
    int mid = (left + right) / 2;
    if (left < right) {
        MergeSort(left, mid); //calling recursively to sort the first half
        MergeSort(mid + 1, right); //calling recursively to sort the second half

        merge(left, mid, right); //Merging the two sorted parts
    }

}

/*The function checks if the point check is on the line  joining p1 to p2*/
int Inline(poin p1, poin p2, poin check) {
    int y2, x2, y1, x1;
    float m1, m2;

    y2 = check.ycord - p2.ycord;
    x2 = check.xcord - p2.xcord;
    y1 = check.ycord - p1.ycord;
    x1 = check.xcord - p1.xcord;
    m1 = (float) y1 / x1;
    m2 = (float) y2 / x2;

    if (x2 * x1 < 0)
        if (m1 == m2)
            return true;
        else if (x1 - x2 == 0)
            if (y1 * y2 < 0)
                return true;
    return false;

}