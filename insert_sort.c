#include <stdio.h>
#define DEBUG 1
#define ARRAYSIZE 10


void insertion(int* A, int n)
{
   int i,j,val;
   
   for( i = 1; i < n; i++ ) 
   {
       val = A[i]; 
       j=i;  
       while ((A[j-1] >= val) && (j>=0))
       {
           A[j] = A[j-1];
           j--; 
       }
       if (j<0){
           j = 0;
       }
       A[j] = val;
   }   
} /* THIS CODE DOESN'T WORK - WHY NOT? */



int main()
{
    int i = 0;
    int A[ARRAYSIZE] = {10,9,8,7,6,5,4,3,2,1}; //10,9,8,7,6,5,4,3,2,1
    
    int start = 0;
    int end = ARRAYSIZE-1;
    
    printf("Original Array: ");
    for( i = 0; i < ARRAYSIZE; i++)
        printf(" %d", A[i]);
    printf("\n");
    
    insertion(A,ARRAYSIZE);
    
    printf("Sorted Array: ");
    for( i = 0; i < ARRAYSIZE; i++)
        printf(" %d", A[i]);

    return -1;

}
