CSC 173 Project 2
A. BASIC INFORMATION 
Yufei Zhao

<C files: main.c TreeNode.c Stack.c ParseTree.c Table.c LinkedList.c>



B. IDEAS OF BUILDING MY PROJECT
[Part 1]
The recursive-descent parser builds the tree from bottom to top. For our grammar, E is thought to be the top syntactic category, while X is thought to be the bottom syntactic category. And I create a function for each syntactic category to build the sub-tree. At first, I just call the upper level function, and this function continuously call lower level functions. At the end of recursion, we finish building the whole tree.
[Part 2]
I create a Table data structure. When I initialize a new table, I have already inserted the productions to the correct places in the table according to the grammar. Then in the Tableparser function, I just follow the table-driven parsing logic that we learned in class. In short, for terminals, I match the terminal with the lookahead-pointer of my input string; for syntactic category, I choose the correct productions and push the RHS of that production to stack. 
[Part 3]
First I read the tree node, from left to middle to right, with recursion method. I get all the operators and operands, but not syntactic category. Then I start to build the expression tree, with the operators as parents and operands as leaves. Finally I use pre-order traversal to print the expression tree. Part 3 is mainly in TreeNode.c file. 


C. HOW TO RUN THE PROJECT
type the following lines in the terminal:
Step 1:
gcc main.c Stack.c TreeNode.c LinkedList.c Table.c ParseTree.c -Wall -Werror -o main

Step 2:
./main

Step 3:
I prompt you to enter input. You just enter VALID input strings. Please go to D(4) to see explanations about VALID. And then I will print the parse tree for Part 1. And the regular expression prefix notation.

*On my computer, I put this file which contains all the C code files on my Desktop. Hence I wrote the following lines in the terminal to compile and run the file. 
RainydeMacBook-Pro:~ rainyzhao$ cd Desktop
RainydeMacBook-Pro:Desktop rainyzhao$ cd Project2
RainydeMacBook-Pro:Project2 rainyzhao$ ls
CMakeLists.txt				Stack.h
CSC173-project-2-submission-form.pdf	Table.c
LinkedList.c				Table.h
LinkedList.h				TreeNode.c
ParseTree.c				TreeNode.h
ParseTree.h				cmake-build-debug
README.txt				main
Stack.c					main.c
RainydeMacBook-Pro:Project2 rainyzhao$ gcc Stack.c main.c Table.c TreeNode.c ParseTree.c LinkedList.c -Wall -Werror -o main
RainydeMacBook-Pro:Project2 rainyzhao$ ./main


D. SOME SPECIFIC NOTES FOR MY PROJECT
**(1) I used some symbols to represent the syntactic category in my code. I have some illustration in the comments. And here I do this again. I used a different character for  syntactic category ET, CT, and ST, and also eps. Since my tree node has a label of type char, I just use one letter as the label to represent the category.
Syntactic Category     Char used in code
E		---->		E
ET		---->		M
C		---->		C
CT		---->		N
S		---->		S
ST		---->		P
A		---->		A
X		---->		X
Also: Epsilon(eps)---->	$

**(2) The requirement said we need to read successive expressions unless users choose to stop. Thanks to study sessions, I know that we can either read inputs from file or read from users. Here I choose to read from console. You just type your string (using only lowercase letter) in the console when I prompt you. And for stopping the reading, I use a trick here. Since input strings for this project do not contain some strange symbols such as %, #, and ~, I use # to represent a call for stop. That is, when you want to stop, you just enter # as the input. 

**(3) For table-driven parser, I rewrite the 8 productions to equivalent 37 productions:
<E> -> <C><ET>
<ET> -> |<E>
<ET> -> eps
<C> -> <S><CT>
<CT> -> .<C>
<CT> -> eps
<S> -> <A><ST>
<ST> -> *<ST>
<ST> -> eps
<A> -> (<E>)
<A> -> <X>
<X> -> a
<X> -> b
...
<X> -> z

**(4) For Part 1& 2& 3, you need to make sure the input is valid. Your string need to use nothing but the lowercase letters from a-z. Also, you need to have operators between operands. For example, "abcdefg" is not valid, since there are no operators between operands. If you enter an invalid input, I will print "Failed. Input invalid" and continues to ask for input from you.



E. MY SAMPLE OUTPUT
Only enter strings with lower letters and do not type space within your input)
Now enter your input (Enter # to quit): a|b.c*
Part 1 & 3--Recursive Descent Parser:
E
    C
        S
            A
                X
                    a
            ST
                eps
        CT
            eps
    ET
        |
        E
            C
                S
                    A
                        X
                            b
                    ST
                        eps
                CT
                    .
                    C
                        S
                            A
                                X
                                    c
                            ST
                                *
                                ST
                                    eps
                        CT
                            eps
            ET
                eps

Regular Expression:
(UNION (ATOMIC a)(CONCAT (ATOMIC b)(CLOSURE (ATOMIC c))))

Only enter strings with lower letters and do not type space within your input)
Now enter your input (Enter # to quit): Ab.c 
Part 1 & 3--Recursive Descent Parser:
Failed. Input invalid.

Regular Expression:
Failed. Input invalid.

Only enter strings with lower letters and do not type space within your input)
Now enter your input (Enter # to quit): #
You exit