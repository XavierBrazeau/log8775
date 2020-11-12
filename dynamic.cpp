#include <algorithm>
#ifndef COMMON
#define COMMON
#include "./common.cpp"
#endif

// A utility function to get minimum of two intgers 
int min (int x, int y) 
{ return (x < y)? x : y; }

// A utility function to get maximum of two intgers 
int max (int x, int y) 
{ return (x > y)? x : y; } 

int compare (const void *a, const void * b) 
{ 
    return ( (*(Box *)b).d * (*(Box *)b).w ) - 
           ( (*(Box *)a).d * (*(Box *)a).w ); 
} 

/* Returns the height of the tallest stack that can be 
   formed with give type of boxes */
int maxStackHeight( int n ) 
{ 
   /* Create an array of all rotations of given boxes 
      For example, for a box {1, 2, 3}, we consider three 
      instances{{1, 2, 3}, {2, 1, 3}, {3, 1, 2}} */
   int index = 0; 
  
   // Now the number of boxes is 3n 
   n = 3*n; 
  
   /* Sort the array 'rot[]' in non-increasing order 
      of base area */
   qsort (rot, n, sizeof(rot[0]), compare); 
  
   // Uncomment following two lines to print all rotations 
   // for (int i = 0; i < n; i++ ) 
   //    printf("%d x %d x %d\n", rot[i].h, rot[i].w, rot[i].d); 
  
   /* Initialize msh values for all indexes  
      msh[i] --> Maximum possible Stack Height with box i on top */
   int msh[n]; 
   for (int i = 0; i < n; i++ ) 
      msh[i] = rot[i].h; 
  
   /* Compute optimized msh values in bottom up manner */
   for (int i = 1; i < n; i++ ) 
      for (int j = 0; j < i; j++ ) 
         if ( rot[i].w < rot[j].w && 
              rot[i].d < rot[j].d && 
              msh[i] < msh[j] + rot[i].h 
            ) 
         { 
              msh[i] = msh[j] + rot[i].h; 
         } 
  
  
   /* Pick maximum of all msh values */
   int max = -1; 
   for ( int i = 0; i < n; i++ ) 
      if ( max < msh[i] ) 
         max = msh[i]; 
  
   return max; 
} 

