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
        
