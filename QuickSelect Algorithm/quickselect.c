// Name: Gerry Xu
// CSC 220 Algorithms Section C
#include<stdio.h>
#include<stdlib.h>
/*
int main()
{   int A[8] = {5,9,2,7,13,17,20,1};
    printf("The array is: ");
    for(int i = 0; i < 8; i++)
    {   printf("%d\t",A[i]);
    }
    int k;
    printf("\n");
    printf("Enter the k-th entry to find the k-th smallest value in the array: ");
    scanf("%d", &k);
    printf("%d\n", quickselect(A, k, 8));
    return 0;
}

*/

#include <stdio.h>
#include <stdlib.h>

int quickselect( int *A, int k, int n);

int main(void)
{
    long i;
    int *space; int tmp;
    space =  (int *) malloc( 1000000*sizeof(int));
    for( i=0; i< 500000; i++ )
    {  *(space + i) = ((139*i)%500000);
        *(space + i + 500000) = 1000000 + ((141*i)%500000);
    }
    if( (tmp = quickselect(  space, 500001, 1000000)) != 1000000 )
    {  printf(" Failed test 1. Returned %d instead of 1000000\n", tmp);
        fflush(stdout); exit(-1);
    }
    else printf("passed test1\n");
    for( i=0; i< 500000; i++ )
    {  *(space + i) = ((139*i)%500000);
        *(space + i + 500000) = 1000000 + ((141*i)%500000);
    }
    if( (tmp = quickselect(  space, 1, 1000000)) != 0 )
    {  printf(" Failed test 2. Returned %d instead of 0\n", tmp);
        fflush(stdout); exit(-1);
    }
    else printf("passed test2\n");
    for( i=0; i< 500000; i++ )
    {  *(space + i) = ((139*i)%500000);
        *(space + i + 500000) = 1000000 + ((141*i)%500000);
    }
    if( (tmp = quickselect(  space, 124, 1000000)) != 123 )
    {  printf(" Failed test 3. Returned %d instead of 123\n", tmp);
        fflush(stdout); exit(-1);
    }
    else printf("passed test3\n");



    printf("Quickselect successful\n");
    exit(0);
    
}

void swap(int *a, int *b) // swap elements a and b
{
    int temp = *a; // set temp to element a
    *a = *b; // set element a to element b
    *b = temp; // set element b to a
}
int randomIndex(int index)
{
    return (rand() % index); // generate a random number from 0 to index - 1
}
/* An algorithm that returns the k-th smallest element in a unsorted array of n elements */
int quickselect(int *A, int k, int n)
{
    int randomPivot = randomIndex(n); /* set randomPivot to a random number from 0 to n - 1 */
    swap(&A[randomPivot], &A[n-1]); /* swap randomPivot with the last element, so randomPivot becomes the last element */
    int pivot = A[n-1]; /* set pivot to the last element which is the randomPivot */
    int pivotPosition = 0; /* position of pivot in the array */
    for (int i = 0; i < n - 1; i++) /* loop through the array from the first element to the last element */
    {
        if (A[i] <= pivot)
        {
            swap(&A[pivotPosition], &A[i]); /* swap the element at A[pivotPosition] with the element at A[i] */
            pivotPosition++; /* increment pivotPosition when A[i] <= pivot */
        }
    }
    swap(&A[pivotPosition], &A[n-1]); /* swap the pivotPosition element with the last element */
    if (k - 1 == pivotPosition) /* when k equals pivotPosition, return the element at the pivotPosition */
    {
        return A[pivotPosition];
    }
    else if (k - 1 < pivotPosition) /* recursive call when k is less than pivotPosition */
    {
        return quickselect(A, k, pivotPosition);
    }
    else            //if(k - 1 > pivotPosition) /* recursive call when k is greater than pivotPosition */
    {
        return quickselect(A + pivotPosition, k - pivotPosition, n - pivotPosition);
    }
}
