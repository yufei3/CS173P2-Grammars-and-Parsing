//
// Created by Rainy ZHAO on 2020/10/3.
//
#include "LinkedList.h"
#include "Stack.h"
#ifndef UNTITLED2_TREENODE_H
#define UNTITLED2_TREENODE_H

#endif //UNTITLED2_TREENODE_H
typedef struct Node* Tree;
struct Node{
    char label;
    Tree leftchild, middlechild, rightchild;
};

Tree makeNode0(char x);
Tree makeNode1(char x, Tree t);
Tree makeNode2(char x, Tree t1, Tree t2);
Tree makeNode3(char x, Tree t1, Tree t2, Tree t3);

Tree search_add(Tree root, char x, Tree child1, Tree child2, Tree child3);
void add(Tree subroot, Tree t1, Tree t2, Tree t3);
void printTree(Tree t);
void printTree_space(Tree t, int space);
void printRegExp(Stack expression);
Stack toPostfix(Stack myinput);
bool isOperator(char symbol);
int precedence(char symbol);
void printPreorder(Tree tree);
void printSingleReg(char s);
bool Terminal(char symbol);
Stack expression(Stack input, Tree tree, int number);
void myexpression(Tree tree);