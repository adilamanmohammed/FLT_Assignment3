Name : Adil Aman Mohammed
Course : Formal language theory
Assignment no: 3
CWID : A20395630
Description: The following code is logic for implementing the Minimization of DFSM and finding the equivalence classes then grouping the given strings

Input files:

1) DFSM.txt : File which contains the Specifications of DFSM 
   example :a b	   (first line contains set of alphabets in given DFSM)
		   (empty line)
	    1 2	   (from line 3 transition table)
	    1 2
		   (last but one line is an empty line)
	    2      (last line contains set of Final states)

Note: The space between characters may be a single space or multiple spaces. Code is written in such a way that it only reads charcters other than space and empty line.


**Commands to Run the Program:**

1) To complie the code use the below command:
	
	gcc prog3.c -o run

2) To run the code and give the input file names in command line use the below command:

	./run DFSM.txt string.txt
