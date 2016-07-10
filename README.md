# Insight-Coding-Challenge
Insight Data Engineering Fellows Program Coding Challenge. 
  
This Repository conists of several files such as the source code and the input and output files.   
  
Necessary Files   
  1). main.cpp  
  2). graph.h  - This is where the prototype functions of class graph, and structs node and timeStamp are stroed.  
  3). graph.cpp - This is where the implementations of class graph, and structs node and timeStamp are stored.  
  4). venmo-trans.txt - main.cpp opens this input file to read the venmotransactions. This can be found at venmo_input/venmo-trans.txt in the repository. For every line in this txt file, the above code will form an edge between the two participants and record the time the transaction took place.   
  5). output.txt - main.cpp writes the median vertex value to this file for every transaction read from the input file (venmo-trans.txt).   
Steps    
  1). Create a C++ project that has the src files in them.   
  2). Make sure that the working directory is set to whereever venmo-trans.txt and output.txt are located.   
  3). Run the program.   
  4). Look at output.txt after program is finished running and see the median vertex recorded after each transaction.   
