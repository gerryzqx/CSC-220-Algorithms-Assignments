// Name: Gerry Xu
// CSC 220 Algorithms Section C
// Homework 2

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *grid, *grid1;
int v1, v2, tmpv;

int left(int i);
int right(int i);
int up(int i);
int down(int i);
void visit(int i);
int DFS(int start);


int main(void)
{
    int *grid2, *tmp;
    int i,j1,j2,k1,k2; int count1, count2;
    grid =  (int *) malloc( 1000000*sizeof(int));
    grid1=  (int *) malloc( 1000000*sizeof(int));
    grid2=  (int *) malloc( 1000000*sizeof(int));
    /* initially: all accessible */
    for( i=0; i< 1000000; i++ )
    {  *(grid + i) = 1;
        *(grid1+ i) = 0;
        *(grid2+ i) = 0;
    }
    /* then block some vertices 10% probability blocked */
    for( i=0; i< 1000000; i++ )
    {  if( (rand()%10) < 1)
        *(grid + i) = 0;
    }
    /* then put in 100 square obstacles 10 by 10 */
    for( i=0; i< 100; i++)
    {  j1= rand()%990;
        j2= rand()%990;
        for( k1=j1; k1< j1+10; k1++)
        {  for( k2=j2; k2< j2+10; k2++)
            *(grid + 1000*k1 + k2) = 0;
        }
    }
    /* then put in 50 line obstacles 100 by 1 */
    for( i=0; i< 50; i++)
    {  j1= rand()%900;
        j2= rand()%1000;
        for( k1=j1; k1< j1+100; k1++)
            *(grid + 1000*k1 + j2) = 0;
    }
    /* then put in 50 line obstacles 1 by 100 */
    for( i=0; i< 50; i++)
    {  j1= rand()%900;
        j2= rand()%1000;
        for( k1=j1; k1< j1+100; k1++)
            *(grid + 1000*j2 + k1) = 0;
    }
    /* then put in 10 line connections 200 by 1 */
    for( i=0; i< 10; i++)
    {  j1= rand()%800;
        j2= rand()%1000;
        for( k1=j1; k1< j1+200; k1++)
            *(grid + 1000*k1 + j2) = 1;
    }
    /* then put in 10 line connections 1 by 200 */
    for( i=0; i< 10; i++)
    {  j1= rand()%800;
        j2= rand()%1000;
        for( k1=j1; k1< j1+200; k1++)
            *(grid + 1000*j2 + k1) = 1;
    }
    /* connect the diagonal */
    for( i=0; i< 1000; i++)
        *(grid + 1000*i + i) = 1;
    for( i=0; i< 999; i++)
        *(grid + 1000*(i+1) + i) = 1;
    /* now test */
    count1 = DFS(0);
    if( *grid1 != 1 )
    {  printf("did not visit start vertex in first run\n");
	       fflush(stdout); exit(-1);
    }
    tmp = grid1; grid1 = grid2; grid2=tmp;
    tmpv = v1; v1 = v2; v2 = tmpv;
    count2 = DFS(999999);
    if( *(grid1+999999) != 1 )
    {  printf("did not visit start vertex in second run\n");
	       fflush(stdout); exit(-1);
    }
    if( count1 != count2 || count1 != v1 || v1 != v2 )
    {  printf("counts inconsistent; failed test. count 1 %d, count2 %d, v1 %d, v2 %d\n",
              count1, count2, v1, v2); fflush(stdout); exit(-1);
    }
    else
        printf("visited %d vertices\n", count1);
    
    for(i= 0; i< 1000000; i++ )
    {  if( *(grid1 + i ) != *(grid2 + i) )
    {  printf("visited matrix inconsistent; failed test.\n");
        fflush(stdout); exit(-1);
    }
    }
    printf("passed test\n");
}

int left(int i)
{  int x,y, j;
    x= i/1000; y= i%1000;
    if( x==0 )
        return(-1);
    else
    {  j= 1000*(x-1) + y ;
        if( *(grid +j) == 1 )
            return(j);
        else
            return(-1);
    }
}
int right(int i)
{  int x,y, j;
    x= i/1000; y= i%1000;
    if( x==999 )
        return(-1);
    else
    {  j= 1000*(x+1) + y ;
        if( *(grid +j) == 1 )
            return(j);
        else
            return(-1);
    }
}
int up(int i)
{  int x,y, j;
    x= i/1000; y= i%1000;
    if( y==999 )
        return(-1);
    else
    {  j= 1000*x + (y+1) ;
        if( *(grid +j) == 1 )
            return(j);
        else
            return(-1);
    }
}
int down(int i)
{  int x,y, j;
    x= i/1000; y= i%1000;
    if( y==0 )
        return(-1);
    else
    {  j= 1000*x + (y-1) ;
        if( *(grid +j) == 1 )
            return(j);
        else
            return(-1);
    }
}
void visit(int i)
{  if ( *(grid+i) != 1 )
{  printf("visited inaccessible vertex. failed test.\n");
    fflush(stdout); exit(-1);
}
else if ( *(grid1+i) != 0 )
{  printf("revisited vertex. failed test.\n");
    fflush(stdout); exit(-1);
}
    *(grid1+i) = 1; /* mark vertex visited */
    v1++;
}

int DFS(int start)
{
    int totalVertices = 1; // use to count the total number of vertices that were visited in the grid graph
    int *graph = (int*)malloc(1000000*sizeof(int)); // create an array of size 1000000
    int graphSize = 1; // used to insert value at the given index in the array
    visit(start); // mark start as visited
    graph[graphSize - 1] = start; // graph at index 0 is set to start value

    while(graphSize != 0)
    {
        start = graph[graphSize]; // start value is set to the value at index of graphSize
        int up_check = up(start); // obtain the value of up neighbor vertex of start
        int down_check = down(start); // obtain the value of down neighbor vertex of start
        int left_check = left(start); // obtain the value of left neighbor vertex of start
        int right_check = right(start); // obtain the value of right neighbor vertex of start
        bool check = false;

        // if there exist a neighbor vertex up of start
        if(up_check != -1)
        {
            // if the vertex up of start is not visited
            if(grid1[up_check] != 1)
            {
                visit(up_check); // mark the neighbor up of start as visited
                graphSize++;
                graph[graphSize] = up_check; // insert up neighbor value to graph at index graphSize
                totalVertices++;
                check = true;
            }
        }
        // if there exist a neighbor vertex down of start
        if(down_check != -1)
        {
            // if the vertex down of start is not visited
            if(grid1[down_check] != 1)
            {
                visit(down_check); // mark the neighbor down of start as visited
                graphSize++;
                graph[graphSize] = down_check; // insert down neighbor value to graph at index graphSize
                totalVertices++;
                check = true;
            }
        }
        // if there exist a neighbor vertex left of start
        if(left_check != -1)
        {
            // if the vertex left of start is not visited
            if(grid1[left_check] != 1)
            {
                visit(left_check); // mark the neighbor left of start as visited
                graphSize++;
                graph[graphSize] = left_check; // insert left neighbor value to graph at index graphSize
                totalVertices++;
                check = true;
            }
        }
        // if there exist a neighbor vertex right of start
        if(right_check != -1)
        {
            // if the vertex right of start is not visited
            if(grid1[right_check] != 1)
            {
                visit(right_check); // mark the right neighbor of start as visited
                graphSize++;
                graph[graphSize] = right_check; // insert right neighbor value to graph at index graphSize
                totalVertices++;
                check = true;
            }
        }
        // if there do not exist a neighbor vertex and is already visited
        if(check == false)
        {
            graph[graphSize--] = start; // go back to the previous vertex
        }
    }
    return totalVertices; // return the total number of vertices that were visited in the grid graph
}

