/***
DSPD Assignment - 1
Name - Jay Puri Goswami
Enrollment Number - BT**CSE***
Question - Implement a 2D Maze solver using Priority Queue
***/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


/**
This is my Priority Queue which will decide which cell to go next
(It is a min Priority Queue and the implementation is array and not heap or tree)
**/
typedef struct Priority_queue
{
    int arr_size ;
    int capacity ;
    int *price ;
    int *arrr;
    int *arrc ;
} PQ ; ;

/* This function creates a newNode for Priority Queue*/
PQ *newNode(int capacity)
{
    PQ *root = (PQ*)malloc(sizeof(PQ)) ;

    root->capacity = capacity ;
    root->arr_size = 0 ;
    root->price = (int*)malloc(capacity) ;
    root->arrr = (int*)malloc(capacity) ;
    root->arrc = (int*)malloc(capacity) ;

    return root ;
}

/**
This utility function inserts an element into the priority queue
and simultaneously brings the min cost node in the front of queue (array and linear time implementation)
**/
PQ *insert_element(PQ *root , int cost , int row ,int column)
{
    int sz = root->arr_size ;
    root->price[sz] = cost ;
    root->arrr[sz] = row ;
    root->arrc[sz] = column ;

    sz = root->arr_size ;

    int min_ind = -1 , min_cost = 1000 ;
    for(int i = 0 ; i<=sz ; i++)
    {
        if(root->price[i] <= min_cost)
        {
            min_cost = root->price[i] ;
            min_ind = i ;
        }
    }

    int tmp = root->price[min_ind] ; root->price[min_ind] = root->price[0] ; root->price[0] = tmp ;

    tmp = root->arrr[min_ind] ; root->arrr[min_ind] = root->arrr[0] ; root->arrr[0] = tmp ;

    tmp = root->arrc[min_ind] ; root->arrc[min_ind] = root->arrc[0] ; root->arrc[0] = tmp ;

    root->arr_size += 1 ;

    return root ;
}

/**
After choosing the first element from Priority Queue , I will remove it ,
so that is what this function is doing
**/
PQ *adjust(PQ *root)
{
    int sz = root->arr_size ;
    for(int i = 1 ; i<sz ; i++)
    {
        root->arrc[i-1] = root->arrc[i] ;
        root->arrr[i-1] = root->arrr[i] ;
        root->price[i-1] = root->price[i] ;
    }

    root->arr_size -= 1 ;

    return root ;
}


/* A Utility function to print priority queue
(Though this is not used but helps in debugging)
*/
void print_PQ(PQ *root)
{
    int sz = root->arr_size ;
    for(int i = 0   ; i<sz ; i++)
    {
        printf("Price %d  Row%d   Column%d \n" ,
               root->price[i],root->arrr[i] ,root->arrc[i]) ;
    }
    printf("\n\n\n") ;
}


//This is struct for Linked List which will store the cell to be traversed
struct Node
{
    int row ;
    int column  ;
    int cost ;

    struct Node *next ;
};

// Function to create a newNode
struct Node *newnode(int row, int column , int cost)
{
    struct Node *root = (struct Node*)malloc(sizeof(Node)) ;
    root->cost = cost ;
    root->column = column ;
    root->row = row ;
    root->next = NULL ;

    return root ;
};

//Function to insert a node in Linked List
struct Node *insert_Node(struct Node *root , struct Node *node)
{
    struct Node *traverse = root ;
    while(traverse->next != NULL)
    {
        traverse = traverse->next ;
    }
    traverse->next = node ;

    return root ;
};

/*
Function to print Linked List
*/
void print_LL(struct Node *root)
{
     FILE *filepointer ;
    struct Node *traver = root ;
    printf("The info is \n") ;
    filepointer = fopen("output.txt","w") ;
    while(traver!=NULL)
    {
        /*printf("Row %d   Column %d   Cost %d\n",traver->row ,traver->column , traver->cost) ;*/



        fprintf(filepointer , "Row %d   Column %d   Cost %d\n" ,traver->row,traver->column ,traver->cost) ;

        traver = traver->next ;

    }
}


/**00
This is an utility function to check whether a given row and column is valid or not
**/
int is_Valid(int row , int column , int ROW , int COLUMN )
{
    if(row < 0 || row > (ROW -1))
    {
        return 0 ;
    }

    if(column <0 || column > COLUMN - 1)
    {
        return 0 ;
    }

    return 1 ;
}


/**
This recursive function calculates price from the inputted cell (i.e, r and c) to all the reachable points
**/
void find_cost(int M[][1000] , int cost[][1000] , int dist[][1000] , int visited[][1000] ,
               int r , int c , int pr , int pc , int row , int column)
{
    // mr and mc helps in calculating all the 4 possible moves from a cell r and c
    int mr[4] = {1,0,-1,0} ;
    int mc[4] = {0, 1,0,-1} ;

    int R,C ;

    //cout<<r<<" "<<c<<"\n" ;

    if(is_Valid(r,c,row, column) == 1 && M[r][c] !=0)
    {
        //That is the input is neither invalid nor is a blocked cell

        //Now checking all possible 4 direction where we can move to from this cell
        for(int i = 0 ; i<4 ; i++)
        {
            R = r + mr[i] ; C = c + mc[i] ;
            int calc1 , calc2  ; calc1 = R -pr ; calc2 = C-pc ;
            /*This calc1 and calc2 make sure that we don't go back to the parent cell as there is
             no point of doing that*/

             /** Example for using calc1 and calc2  is

                    1   1   2   0
                    0   0   1   0
                    0   0   1   1
                    0   0   1   0
                    So if starting is (1,2) so to make sure that when we reach (3,2) we don't calculate for
                    (2,2) again

            **/

            //We'll enter only if the calculated R and C is valid , not parent and not blocked
            if(is_Valid(R,C,row, column) && !(calc1 ==0 && calc2 == 0) && visited[R][C] == 0 )
            {
                if(M[R][C] != 0)
                {
                    if(M[r][c] == 1) //Normal updation of cost
                    {
                        if(cost[R][C] > cost[r][c])
                        {
                            cost[R][C] = cost[r][c] ;
                            dist[R][C] = dist[r][c] + 1 ;
                        }
                        else if(cost[R][C] == cost[r][c])
                        {

                            if(dist[R][C] > 1 + dist[r][c])
                                //Now this handles when the cost is same so we go with the short path
                            {
                                dist[R][C] = 1 + dist[r][c] ;
                            }
                        }

                    }
                    else if(M[r][c] == 2) //Normal updation of cost
                    {
                        if(cost[R][C] > cost[r][c] + 1)
                        {
                            cost[R][C] = 1 + cost[r][c] ;
                            dist[R][C]  = 1 + dist[r][c] ;
                        }

                    }
                    visited[R][C] = 1 ;
                    /*Marking this cell visited so that we stop calling this recursive function
                     when we reach cell where every possible step leads to an already visited cell*/

                     /**    Example

                                1   1   2   0
                                0   0   1   0
                                0   1   1   1
                                0   1   1   0

                                Here if I start from (1,2), so the recursive function will stop at
                                (2,1) , as from here all possible moves either a blocked cell or
                                an already visited cell
                     **/

                    find_cost(M,cost,dist, visited,R,C,r,c,row , column) ;
                }
            }
            else
            {
                printf("\n\nRow is %d Column is %d and this is an Invalid Entry\n\n\n" , R,C) ;
            }


        } //End of for loop
    }
    else //i.e either the input is invalid or input is a blocked cell i.e M[r][c] = 0 ;
        //So no operation should and can be done here
    {
        printf("Row is %d Column is %d\n\n",r,c) ;
        if(M[r][c] ==0)
        {
            printf("\n\nGiven cell has 0 value\n\n") ;
        }
        else
        {
            printf("\n\nInvalid entry of the cell\n\n") ;
        }
    }

    /*
    Although a void function need no return but this is a recursive function
    so to "make sure" that something is returned at the last call , so that it can unfold
    */
    return  ;


}

/**
This is the main called function which calls the cells and find_cost from that cell
**/
void cell_caller(int M[][1000] , int cost[][1000] ,int dist[][1000] ,
                 int visited[][1000], int r, int c , int ROW, int COLUMN)
{


    int mr[4] = {1,0,-1,0} ; int R[4] ,C[4] ;
    int mc[4] = {0, 1,0,-1} ;

    int sum = 0 ;

    for(int i = 0 ; i<4 ; i++)
    {
        R[i] = r + mr[i] ; C[i] = c + mc[i];
        //If calculated Row is invalid or is blocked
        if(is_Valid(R[i],C[i],ROW,COLUMN) == 0 || M[R[i]][C[i]] ==0)
        {
            sum+=1 ;
        }
        else if(M[r][c] == 1)
        {
            //If calculated cell is free to move but cost there is aready less so no point of there from this cell
            if(cost[R[i]][C[i]] < cost[r][c])
            {
                sum+=1;
            }
        }
        else if(M[r][c] == 2)
        {
            /*If calculated cell is free to move with some cost but cost there is already less
            so no point of there from this cell */
            if(cost[R[i]][C[i]] <  1  +cost[r][c])
            {
                sum+=1;
            }
        }
    }

    /*
    If sum is 4 means from this given cell (r,c) there is no point of going to any of its adjacent cell
    */
    if(sum == 4)
    {
        return  ;
    }

    else
    {

         for(int i = 0 ; i< 4 ; i++)
         {
            if(is_Valid(R[i],C[i],ROW,COLUMN) == 0 || M[R[i]][C[i]] ==0)
            {

            }
            else if(M[R[i]][C[i]] == 1 && (cost[R[i]][C[i]] < cost[r][c]))
            {
            }
            else if(M[R[i]][C[i]] == 2 && (cost[R[i]][C[i]] <  1  +cost[r][c]))
            {

            }
            /*
            This above 3 condition are just skipping of the sum part
            and is written for debugging purpose
            */
            else
            {

                visited[R[i]][C[i]] = 1 ;
                //Marking the moved cell as visited and then calling the find_cost function

                find_cost(M,cost,dist,visited,r,c,r,c,ROW,COLUMN) ;

                for(int i = 0 ; i<ROW ; i++)
                {
                    for(int j = 0 ; j<COLUMN ; j++)
                    {
                        visited[i][j] = 0 ; //0 means not visited , 1 means visited ;
                    }
                }

                visited[R[i]][C[i]] = 1 ;
                //cell_caller(M,cost,dist,visited,R[i],C[i]) ;

            }

         } //End of the for loop ;
    }



}

/**
This is just an utility function called in the very end just to make sure that the cost are calculated
correctly and if not it corrects it

Example -> It may so happen that after all the calculation the cost matrix we get is

                1 0 2
                1 2 2
                1 3 2

                Now we can clearly see that at (2,1) the cost can be 2 instead of 3
                So with the help of this function we do that only

**/
void polishing(int cost[][1000] , int M[][1000], int ROW , int COLUMN)
{
    for(int i = 0 ; i<ROW ; i++)
    {
        for(int j = 0 ; j<COLUMN ; j++)
        {
            int mr[4] = {1,0,-1,0} ; int R[4] ,C[4] ;
            int mc[4] = {0, 1,0,-1} ;

            for(int k = 0 ; k<4 ; k++)
            {
                R[k] = i + mr[k] ; C[k] = j + mc[k] ;
                if(is_Valid(R[k],C[k],ROW,COLUMN) && M[R[k]][C[k]] !=0)
                {
                    if(M[i][j] == 1)
                    {
                        if(cost[R[k]][C[k]] > cost[i][j])
                        {
                            cost[R[k]][C[k]] = cost[i][j] ;
                         }
                    }
                    else if(M[i][j] ==2)
                    {
                        if(cost[R[k]][C[k]] > cost[i][j] + 1)
                        {
                            cost[R[k]][C[k]] = cost[i][j] + 1 ;
                        }
                    }
                }
            }

        }
    }
}

//Again this is just a cost printing function
void print(int cost[][1000] , int ROW , int COLUMN)
{
    for(int i = 0 ; i<ROW ; i++)
    {
        for(int j = 0 ; j<COLUMN ; j++)
        {
            //printf("%d ",cost[i][j]) ;
            if(cost[i][j] == 100)
            {
                printf("%d\t",-1) ;
            }
            else
            {
                printf("%d\t",cost[i][j]) ;
            }
        }
        printf("\n") ;
    }
}


int main()
{
    FILE *filepointer ;

    // char data_to_be_read[1000] ;

    //filepointer = fopen("SameCost.txt","r") ;
    filepointer = fopen("Sample.txt","r") ;

    if(filepointer == NULL)
    {
        printf("\n\n\nGiven file doesn't exist\n\n\n") ;
    }
    else
    {
        int row , column  ;
         int S[2] , E[2] ;
        //row = data_to_be_read[0] - 48 ; column = data_to_be_read[2] - 48 ;

        int R[2] ;
        for(int i = 0 ; i<2 ; i++)
        {
            fscanf(filepointer , "%d" , &R[i]) ;
        }
        row = R[0] ; column = R[1] ; //printf("Row is%d Column is%d\n",row,column) ;

        int M[row][1000] ;
        for(int i = 0 ; i<row ; i++)
        {
            //fgets ( data_to_be_read, 1000, filepointer ) ;
            for(int j = 0 ; j<column ; j++)
            {
                fscanf(filepointer,"%d" , &M[i][j]) ;
                printf("%d\t",M[i][j]) ;
            }
            printf("\n") ;

        }


        /** The input format is such that ->
        1) If value is 0 means the given cell is blocked to move
        2) If value is 1  means the given cell is free to move without a cost
        3) If value is 2 means the given is free to move with a cost of 1 buck/cell

        **/




        for(int i = 0 ; i<2 ; i++)
        {
            fscanf(filepointer , "%d", &S[i]) ;
            S[i]-= 1 ;
        }

        for(int i = 0 ; i< 2 ; i++)
        {
            fscanf(filepointer,"%d" , &E[i]) ;
            E[i]-= 1 ;
        }


        if(!is_Valid(S[0],S[1],row,column) || !is_Valid(E[0],E[1],row,column) )
        {
            printf("%d  %d %d %d %d %d",row,column,S[0],S[1],E[0],E[1]) ;
            printf("Invalid entry\n\n\n") ;
        }
        else
        {
            int cost[row][1000] , dist[row][1000] , visited[row][1000]  ;


            for(int i = 0 ; i<row ; i++)
            {
                for(int j = 0 ; j<column ; j++)
                {
                    cost[i][j] = 100;
                    dist[i][j] = 100 ;
                    visited[i][j] = 0 ; //0 means not visited , 1 means visited ;

                }
            }



            if(M[S[0]][S[1]] == 1)
            {
                cost[S[0]][S[1]]= 0 ;
            }
            else
            {
                cost[S[0]][S[1]]= 1 ;
            }
            dist[S[0]][S[1]] = 0 ;
            visited[S[0]][S[1]] = 1 ;

            find_cost(M,cost,dist ,visited ,  S[0],S[1] , -1 , -1, row,column) ;








            int mr[4] = {1,0,-1,0} ; int R[4] ,C[4] ;
            int mc[4] = {0, 1,0,-1} ;

            for(int i = 0 ; i<4 ; i++)
            {
                R[i] = S[0] + mr[i] ; C[i] = S[1] + mc[i] ;
                if(is_Valid(R[i],C[i],row,column) && M[R[i]][C[i]]!=0)
                {
                    for(int i = 0 ; i<row ; i++)
                    {
                        for(int j = 0 ; j<column ; j++)
                        {
                            visited[i][j] = 0 ; //0 means not visited , 1 means visited ;
                        }
                    }

                    visited[R[i]][C[i]] = 1 ;
                    if(M[R[i]][C[i]] == 2)
                    {
                        if(cost[R[i]][C[i]] > 1 + cost[S[0]][S[1]])
                        {
                            cost[R[i]][C[i]] = 1 + cost[S[0]][S[1]] ;
                        }
                    }
                    cell_caller(M,cost,dist,visited,R[i],C[i],row,column) ;
                }
            }




            polishing(cost,M,row,column) ;
            print(cost,row,column) ;



            printf("\n\n");
            for(int i =  0 ; i<row ; i++)
            {
                for(int j = 0 ; j<column ; j++)
                {
                    printf("%d  ",M[i][j]) ;
                }
                printf("\n") ;
            }

            printf("Done with calc\n\n\n\n\n" ) ;

            PQ *root = newNode(1000) ;

            struct Node *LL = newnode(E[0],E[1],cost[E[0]][E[1]]) ;

            int x , y ; x = E[0] ; y = E[1] ;
            int final_call[row][column] ;
            for(int i = 0 ; i<row ; i++)
            {
                for(int j = 0 ; j<column ; j++)
                {
                    final_call[i][j] = 0 ;
                }
            }

            final_call[x][y] = 1 ;

            while(!(x==S[0] && y==S[1]))
            {
                for(int i = 0 ; i< 4 ; i++)
                {
                    R[i] = x + mr[i] ; C[i] = y + mc[i] ;

                    if(is_Valid(R[i],C[i],row,column))
                    {
                        if(cost[R[i]][C[i]] != 100 && final_call[R[i]][C[i]] == 0)
                        {
                            final_call[R[i]][C[i]] = 1 ;
                            root = insert_element(root,cost[R[i]][C[i]],R[i],C[i]) ;

                        }
                    }

                }

                x = root->arrr[0] ; y = root->arrc[0] ;
                root = adjust(root) ;

                struct Node *a = newnode(x,y,cost[x][y]) ;

                LL = insert_Node(LL,a) ;

            }

            /*struct Node *a = newnode(S[0],S[1],cost[S[0]][S[1]]) ;
            LL = insert_Node(LL,a) ; */

            print_LL(LL) ;

        } //End of else . All operation except fileclosing to be done here ;

    }

    fclose(filepointer) ;

    return 0 ;
}
