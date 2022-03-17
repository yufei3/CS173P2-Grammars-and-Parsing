//
// Created by Rainy ZHAO on 2020/10/3.
//

#include <stdlib.h>
#include "LinkedList.h"
#include "TreeNode.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Stack.h"
#define FAILED NULL


Tree makeNode0(char x){
    Tree root;
    root = (Tree) malloc(sizeof(struct Node));
    root->label=x;
    root->leftchild=NULL;
    root->middlechild=NULL;
    root->rightchild=NULL;
    return root;
}

Tree makeNode1(char x, Tree t){
    Tree root;
    root=makeNode0(x);
    root->leftchild=t;
    return root;
}

Tree makeNode2(char x, Tree t1, Tree t2){
    Tree root;
    root=makeNode0(x);
    root->leftchild=t1;
    root->rightchild=t2;
    return root;
}

Tree makeNode3(char x, Tree t1, Tree t2, Tree t3){
    Tree root;
    root=makeNode0(x);
    root->leftchild=t1;
    root->middlechild=t2;
    root->rightchild=t3;
    return root;
}

Tree search_add(Tree root, char x, Tree child1, Tree child2, Tree child3){
    if (root==NULL){
        return FAILED;
    }
    else if (root->label==x && (root->leftchild==NULL) && root->rightchild==NULL
    && root->middlechild==NULL){
        add(root, child1, child2, child3);
        return root;
    }
    else {
        Tree result;
        result=search_add(root->leftchild, x, child1, child2, child3);
        if (result==FAILED){
            result=search_add(root->middlechild, x, child1, child2, child3);
            if (result==FAILED){
                result=search_add(root->rightchild, x, child1, child2, child3);
                if (result==FAILED){
                    return FAILED;
                }
            }
        }
        return result;
    }
}

void add(Tree subroot, Tree t1, Tree t2, Tree t3){
    subroot->leftchild=t1;
    subroot->middlechild=t2;
    subroot->rightchild=t3;
}

void printTree(Tree t){
    printTree_space(t, 0);
}

void printTree_space(Tree t, int space){
    //printf("%d\n", space);
    if (t==NULL){
        return;
    }
    for (int i=0; i<space; i++){
        printf(" ");
    }
    switch(t->label){
        case 'E':
            printf("E\n");
            break;
        case 'M':
            printf("ET\n");
            break;
        case 'C':
            printf("C\n");
            break;
        case 'N':
            printf("CT\n");
            break;
        case 'S':
            printf("S\n");
            break;
        case 'P':
            printf("ST\n");
            break;
        case 'A':
            printf("A\n");
            break;
        case 'X':
            printf("X\n");
            break;
        case '$':
            printf("eps\n");
            break;
        default:
            printf("%c\n", t->label);
    }
    if (t->leftchild!=NULL){
        printTree_space(t->leftchild, space+4);
    }
    if (t->middlechild!=NULL){
        printTree_space(t->middlechild, space+4);
    }
    if (t->rightchild!=NULL){
        printTree_space(t->rightchild, space+4);
    }
}


void printRegExp(Stack expression){
    Tree expTree=NULL;
    //Stack expression stores the left characters
    //Stack operands stores the numbers(operands)
    Stack operands=new_Stack();
    while(!Stack_isEmpty(expression)){
        char c=Stack_removeBottom(expression);
        if (isOperator(c)){
            if (c=='*'){
                char variable='0';
                if (!Stack_isEmpty(operands)){
                    variable=Stack_pop(operands);
                }
                else{
                    printf("Failed.");
                    return;
                }
                expTree=makeNode1(c, makeNode0(variable));
            }

            else {
                if (expTree==NULL){
                    char variable1='0';
                    char variable2='0';
                    if (!Stack_isEmpty(operands)){
                        variable1=Stack_pop(operands);
                    }
                    else{
                        printf("Failed.");
                        return;
                    }
                    if (!Stack_isEmpty(operands)){
                        variable2=Stack_pop(operands);
                    }
                    else{
                        printf("Failed.");
                        return;
                    }
                    expTree=makeNode2(c, makeNode0(variable2), makeNode0(variable1));
                }
                else{
                    char variable='0';
                    if (!Stack_isEmpty(operands)){
                        variable=Stack_pop(operands);
                    }
                    expTree=makeNode2(c, makeNode0(variable), expTree);
                }
            }
        }

        else {
            Stack_add(operands, c);
        }
    }
    printPreorder(expTree);
}

void myexpression(Tree tree){
    int number=0;
    Stack input=new_Stack();
    Stack result=expression(input, tree, number);
    Stack expression=toPostfix(result);
    printRegExp(expression);
}

Stack expression(Stack input, Tree tree, int number){
    if (tree==NULL){
        return NULL;
    }
    else if (Terminal(tree->label)){
        number++;
        Stack_add(input, tree->label);
    }
    else{
        expression(input, tree->leftchild, number);
        expression(input, tree->middlechild, number);
        expression(input, tree->rightchild, number);
    }
    return input;
}

Stack toPostfix(Stack myinput){
    Stack expression=new_Stack();
    Stack stack=new_Stack();
    while(!Stack_isEmpty(myinput)){
        char c=Stack_removeBottom(myinput);
        if (isOperator(c)){
            if (Stack_isEmpty(stack) || precedence(Stack_peek(stack)) < precedence(c)){
                Stack_add(stack, c);
            }
            else{
                bool add=false;
                char top=Stack_peek(stack);
                while(precedence(top) >= precedence(c)){
                    Stack_add(expression, Stack_pop(stack));
                    if (Stack_isEmpty(stack)){
                        Stack_add(stack, c);
                        add=true;
                        break;
                    }
                    top=Stack_peek(stack);
                }
                if (!add){
                    Stack_add(stack, c);
                }
            }
        }
        else {
            Stack_add(expression, c);
        }
    }
    while(!Stack_isEmpty(stack)){
        Stack_add(expression, Stack_pop(stack));
    }

    return expression;
}

bool isOperator(char symbol){
    if (symbol=='*' || symbol=='|' || symbol=='.'){
        return true;
    }
    else return false;
}
int precedence(char symbol){

    if (symbol=='*'){
        return 3;
    }
    else if (symbol=='.'){
        return 2;
    }
    else if (symbol=='|'){
        return 1;
    }
    else return -1;
}
bool Terminal(char symbol){
    char c = symbol;
    if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' ||
        c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' ||
        c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z' ||
        c == '*' || c == '.' || c == '|' || c == '(' || c == ')') {
        return true;
    } else return false;
}

void printPreorder(Tree tree){
    if (tree==NULL){
        return;
    }
    printf("(");
    int mylabel=(int)tree->label;
    switch (mylabel) {
        case 124: //'|'
            printf("UNION ");
            break;
        case 46: //'.'
            printf("CONCAT ");
            break;
        case 42: //'*'
            printf("CLOSURE ");
            break;
        case 97 ... 122:
            printf("ATOMIC %c", tree->label);
            break;
        case 40: //'('
            printf("(");
            break;
        case 41: //')
            printf(")");
        default:
            break;
    }
    printPreorder(tree->leftchild);
    printPreorder(tree->rightchild);
    printf(")");
}
void printSingleReg(char s){
    if (isOperator(s)){
        switch (s) {
            case '|':
                printf("UNION");
                break;
            case '.':
                printf("CONCAT");
                break;
            case '*':
                printf("CLOSURE");
                break;
        }
    }
    else{
        printf("(ATOMIC %c)", s);
    }
}



