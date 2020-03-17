# 2D-Maze-Solver

Implemented a 2D Maze Solver in C programming Language. The code file is well documented and commented  .

The input format is such that ->



        1) If value is 0 means the given cell is blocked to move
        2) If value is 1  means the given cell is free to move without a cost
        3) If value is 2 means the given is free to move with a cost of 1 buck/cell
        


For an example I have also attached an input and output file with input.txt and output.txt

Input file has the format ->

        1) First line has row and column number 
        2) Then the next row number of lines has column number of elements (i.e , it is nothing but matrix input)
        3) Then the next line has 2 numbers the row and column number of starting point ( it is 1 indexed input)
        4) Then the final line has 2 numbers , the row and column number of the ending point (it is 1 indexed input) 

Output file contains ->

         The path that needs to be traversed and every time how the cost is updated 
         
         
         
The process.txt file contains -> 
          
          How to the process of traversal occurs through the algorithm . It is printing all the invalid and blocked cell whenever it reaches there. Actually this is helpful to understand how the algorithms works .    




Though the code is optimized but still some optimization which cyou can try and is not in the code is -> 

        
        1) I've upper bounded all the 2d arrays with max column size as 1000, becuase it helps me in passing the matrix with any dimension specification in the function .  Instead you can use a integer pointer array i.e int *(cost[row]) , so here the column size becomes variable so passing it in the function will not require any size specification . Use can even use  int **cost , but I think that will make the things complicated . 
        
        2) Now I've used a 2-D Array to store the input Maze , but if you know beforehand or usually the case where most of the cell in the maze are blocked , so instead of wasting a lot of space in the matrix which you know you won't travel use a Sparse Matrix will not only save a lot of space but also help you in not calculating or checking is_Valid on the blocked cell 
        

        
