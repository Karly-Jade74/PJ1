# PJ1
Project 1 from Data Structures and algarithms

CSE310 Project 1: Linux, C++, Command Line Argument, stdin/stdout/stderr,
File I/O, Formatted Output, Memory Management, Linked List, Modular Design

** DESCRIPTION

1 Modular Design
Each module consists of a header file and its corresponding implementation file (the main
module does not need a header file). The header file has extension .h and the implementation file
has extension .cpp. Other than the extensions, the header file and its corresponding implementation
file of a module should have the same file name. The header file defines the data structures and
prototypes of the functions. The implementation file implements the functions.
For this project, you should have four modules, with the header files named structs.h, util.h,
list read.h, list write.h, and the implementation files list read.cpp, list write.cpp, main.cpp,
and util.cpp. Seven of these eight files are provided to you. You are required to write list write.cpp,
following the prototype defined in list write.h. You need to understand everything in these files
provided to you and be able to modify them as needed in future projects.

**2 Makefile
A Makefile is provided to you. You should use the provided Makefile to compile your project. We
will grade your project using the provided Makefile.

**3 Command Line Arguments
In main.cpp, the function main takes two parameters argc and argv, in that order. Here argc
is the number of commandline arguments, and argv[0], argv[1], . . . , argv[argc-1] are the
commandline arguments. The following example illustrates some basics.
2
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
printf("argc=%d\n", argc);
for (int i=0; i<argc; i++){
printf("The str value of argv[%d] is %s\n", i, argv[i]);
printf("The int value of argv[%d] is %d\n\n", i, atoi(argv[i]));
}
return 1;
}
If you are not familiar with command line arguments, you may type the above text in a file named
test.cpp, and use g++ test.cpp to produce the executable file named a.out. You may then try
the following example executions to learn about the meanings of argc and argv[].
./a.out
./a.out SCAI @ ASU 2025S

**4 File I/O, Formatted Output
The function main shows you how to perform proper file I/O operations and use formatted output.
Special attention should be paid to the functions fopen and fclose. The following example can
help you to understand these.
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
FILE *fp1, *fp2;
int n, v1, v2, v3; float x; double y;
if (argc < 3){
printf("Usage: %s input_file output_file\n", argv[0]);
exit (0);
}
fp1 = fopen(argv[1], "r");
if (fp1 == NULL) {
fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
3
exit (0);
}
fp2 = fopen(argv[2], "w");
if (fp2 == NULL) {
fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
exit (0);
}
v1=fscanf(fp1, "%d", &n); v2=fscanf(fp1, "%f", &x); v3=fscanf(fp1, "%lf", &y);
fprintf(fp2, "v1=%d, v2=%d, v3=%d\n", v1, v2, v3);
fprintf(fp2, "n=%d, n=%4d\n", n, n);
fprintf(fp2, "x=%f, x=%8.3f\n", x, x);
fprintf(fp2, "y=%lf, y=%8.3lf\n", y, y);
fclose(fp1); fclose(fp2);
return 1;
}

**5 Memory Management
The provided files also have examples for dynamic memory allocation and release. Pay attention to
calloc, malloc, and free. The following example may be helpful to you.
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
FILE *fp;
int i, n, *A;
fp = fopen("INPUT.txt", "r");
if (fp == NULL) {
fprintf(stderr, "Error: cannot open file INPUT.txt\n");
exit (0);
}
fscanf(fp, "%d", &n);
A = (int *) malloc(n*sizeof(int));
if (A == NULL) {
4
fprintf(stderr, "Error: cannot allocate memory\n");
exit (0);
}
for (i=0; i<n; i++) fscanf(fp, "%d", &A[i]);
for (i=0; i<n-1; i++) printf("%d ", A[i]); printf("%d\n", A[n-1]);
free(A);
return 1;
}

**6 Data Structures
The following defines the data structures NODE and LIST
#ifndef _structs_h
#define _structs_h 1
typedef struct TAG_NODE{
double key;
TAG_NODE *next;
}NODE;
typedef struct TAG_LIST{
NODE *head;
NODE *tail;
int length;
}LIST;
#endif
You should use these two data structures as defined in the above. In LIST, head is a pointer to the
first node of the list; tail is a pointer to the last node of the list; length is the number of nodes
on the list. Both head and tail are NULL when length is 0.
5

**7 nextInstruction
Please carefully study the function nextInstruction defined in util.h and implemented in util.cpp,
and its application in main.cpp. You will need to fully understand it, and be able to modify it as
needed in future projects. While each instruction is a string of characters, some of the instructions
take an argument while others do not. Please pay attention to these.

**8 Valid Executions
A valid execution of your project has the following form:
./PJ1 <InputFile> <OutputFile> <flag>
where
• PJ1 is the executable file of your project,
• <InputFile> is the name of the input file,
• <OutputFile> is the name of the intended output file,
• flag is a non-zero integer.
Your program should check whether the execution is valid. If the execution is not valid, your
program should print out an error message to stderr and stop. Note that your program should
not crash when the execution is not valid.


**9 Flow of the Project
9.1 Open the Output File and Create an Empty List
Upon a valid execution, your program should open the output file. In this document, we will assume
that the output file is pointed to by fp2. Your program should also allocate memory for an object
of type LIST. We will assume that pLIST points to this object. Initially, we have pLIST->head =
pLIST->tail = NULL, and pLIST->length = 0. In other words, pLIST points to an empty list.6
9.2 Loop over the Instructions
Your program should expect the following instructions from stdin and act accordingly:
(a) Stop
On reading Stop, the program closes the output file and stops.
(b) Print
On reading the Print instruction, your program should do the following:
(b-i) Write the content of the list to stdout, using the
%lf\n
format for each key value. The function listPrint provided to you performs this func-
tion.
(b-ii) If |flag| > 1, the program also writes the content of the list to the output file.
(b-iii) Wait for the next instruction from stdin.
(c) Write
On reading the Write instruction, your program should do the following:
(c-i) Write the content of the list to the output file, using the
%lf\n
format for each key value.
(c-ii) Wait for the next instruction from stdin.
(d) Max
On reading the Max instruction, your program should do the following:
(d-i) Write to stdout the maximum key on the list (if the list is not NULL and contains at
least one node). Refer to test cases for the output format.
(d-ii) If |flag| > 1, the program also writes the above to the output file.
(d-iii) Wait for the next instruction from stdin.
(e) Min
On reading the Min instruction, your program should do the following:
7
(e-i) Write to stdout the minimum key on the list (if the list is not NULL and contains at least
one node). Refer to test cases for the output format.
(e-ii) If |flag| > 1, the program also writes the above to the output file.
(e-iii) Wait for the next instruction from stdin.
(f) Sum
On reading the Sum instruction, your program should do the following:
(f-i) Write to stdout the sum of the keys on the list (if the list is not NULL and contains at
least one node). Refer to test cases for the output format.
(f-ii) If |flag| > 1, the program also writes the above to the output file.
(f-iii) Wait for the next instruction from stdin.
(g) Length
On reading the Length instruction, your program should do the following:
(g-i) Write to stdout the length of the list. Refer to test cases for the output format.
(g-ii) If |flag| > 1, the program also writes the above to the output file.
(g-iii) Wait for the next instruction from stdin.
(h) Release
On reading the Release instruction, your program should do the following:
(h-i) Delete and free all the nodes on pLIST.
(h-ii) Wait for the next instruction from stdin.
(i) Append <KEY>
On reading the Append instruction, your program should do the following:
(i-i) Allocate memory for a new node. Set the key field of the new node to the value of
<KEY> associated with the Append instruction. Append the new node at tail of pLIST
and update pLIST->length accordingly. Write a message to stdout (refer to test cases
for format).
(i-ii) If |flag| > 1, the program also writes the above to the output file.
(i-iii) Wait for the next instruction from stdin.
8
(j) Insert <KEY>
On reading the Insert instruction, your program should do the following:
(j-i) Allocate memory for a new node. Set the key field of the new node to the value of
<KEY> associated with the Insert instruction. Insert the new node at head of pLIST
and update pLIST->length accordingly. Write a message to stdout (refer to test cases
for format).
(j-ii) If |flag| > 1, the program also writes the above to the output file.
(j-iii) Wait for the next instruction from stdin.
(k) Search <KEY>
On reading the Search instruction, your program should do the following:
(k-i) Search for the first node on the list whose key field is equal to the value of <KEY>
associated with the Search instruction. If such a node exists, return a pointer to this
node. If such a node does not exist, return NULL. Write a message to stdout (refer to
test cases for format).
(k-ii) If |flag| > 1, the program also writes the above to the output file.
(k-iii) Wait for the next instruction from stdin.
(l) Delete <KEY>
On reading the Delete instruction, your program should do the following:
(l-i) Search for the first node on the list whose key field is equal to the value of <KEY>
associated with the Delete instruction. If such a node exists, delete it, and return a
pointer to the deleted node to the caller. The caller will release the memory of the
deleted node. Write a message to stdout (refer to test cases for format).
(l-ii) If |flag| > 1, the program also writes the above to the output file.
(l-iii) Wait for the next instruction from stdin.
(m) Read
On reading the Read instruction, your program should do the following:
(m-i) Delete and free the nodes on pLIST.
(m-ii) Open the input file for reading.
9
(m-iii) If flag > 0, append each of the key values in the input file to pLIST. If flag < 0,
insert each of the key values in the input file to pLIST. Refer to the posted test cases for
examples.
(m-iv) Wait for the next instruction from stdin.
(n) Invalid instruction
On reading an invalid instruction, your program should do the following:
(n-i) Write the following to stderr:
Invalid instruction: <Instruction>
where <Instruction> is the instruction returned.
(n-ii) Wait for the next instruction from stdin.
