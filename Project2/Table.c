//
// Created by Rainy ZHAO on 2020/10/3.
//
#include "TreeNode.h"
#include "Table.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#define FAILED NULL

struct Table{
    int ** table;
    LinkedList stack;
};

/*
 * Grammar:
 * (1)<E> -> <C><ET>
 * (2)<ET> -> |<E>
 * (3)<ET> -> eps
 * (4)<C> -> <S><CT>
 * (5)<CT> -> .<C>
 * (6)<CT> -> eps
 * (7)<S> -> <A><ST>
 * (8)<ST> -> *<ST>
 * (9)<ST> -> eps
 * (10)<A> -> (<E>)
 * (11)<A> -> <X>
 * (12)<X> -> a
 * (13)<X> -> b
 * ...
 * (37)<X> -> z
 */

Table new_table(){
    LinkedList stack=new_LinkedList();
    LinkedList_add_at_front(stack, (void *)'E');

    Table this=(Table)malloc(sizeof(struct Table));
    //row 0: E; row 1: ET (M); row 2: C; row 3: CT (N)
    //row 4: S; row 5: ST (P); row 6: A; row 7: X
    //epsilon: $
    int** table=(int**)malloc(sizeof(int*)*8); //each syntactic category has a row
    for (int i=0; i<8; i++){
        table[i]=(int*)malloc(sizeof(int)*128); //each terminal has a column
    }
    for (int i=0; i<8; i++){
        for (int j=0; j<128; j++){
            table[i][j]=-1; //default value
        }
    }
    for (int j=0; j<128; j++){
        table[1][j]=3;
        table[3][j]=6;
        table[5][j]=9;
    }
    for (int j=97; j<=122; j++){ //a->97, b->98, ..., z->122
       table[0][j]=1;
       table[2][j]=4;
       table[4][j]=7;
       table[6][j]=11;
       table[7][j]=j-85;
   }
   table[0][(int)'(']=1;
   table[1][(int)'|']=2;
   table[1][(int)'$']=3;
   table[2][(int)'(']=4;
   table[3][(int)'.']=5;
   table[3][(int)'$']=6;
   table[4][(int)'(']=7;
   table[5][(int)'*']=8;
   table[5][(int)'$']=9;
   table[6][(int)'(']=10;

    this->table=table;
    this->stack=stack;
    return this;
}


Tree Tableparser(Table t, char *input){
    Tree mytree=makeNode0('E');
    int lookahead=0;
    while(!LinkedList_isEmpty(t->stack)){
        char stackItem=(char)LinkedList_pop(t->stack);
//        printf("%c\n", stackItem);

        //if the stack top is a terminal or eps
        if (isTerminal(stackItem)){
            if (stackItem=='$'){ //if the pop item is eps
                //just pop the eps out
            }
            else { //if the pop item is a, b, ..., or z
                if (input[lookahead]==stackItem){ //match
                    lookahead++;
                }
                //not match
                else return FAILED;
            }
        }

        //if the stack top is a syntactic category
        else {
            int production=t->table[SyntacticC(t, stackItem)][(int)input[lookahead]];
//            printf("%c\n", stackItem);
//            printf("%d\n", production);
//            printf("%c\n", (char)input[lookahead]);
            if (production==-1){
                return FAILED;
            }
            else {
                switch(production){
                    case 1:
                        search_add(mytree, 'E', makeNode0('C'), NULL, makeNode0('M'));
                        LinkedList_add_at_front(t->stack, (void *)'M');
                        LinkedList_add_at_front(t->stack, (void *)'C');
                        break;
                    case 2:
                        search_add(mytree, 'M', makeNode0('|'), NULL, makeNode0('E'));
                        LinkedList_add_at_front(t->stack, (void *)'E');
                        LinkedList_add_at_front(t->stack, (void *)'|');
                        break;
                    case 3:
                        search_add(mytree, 'M', makeNode0('$'), NULL, NULL);
                        LinkedList_add_at_front(t->stack, (void *)'$');
                        break;
                    case 4:
                        search_add(mytree, 'C', makeNode0('S'), NULL, makeNode0('N'));
                        LinkedList_add_at_front(t->stack,(void *)'N');
                        LinkedList_add_at_front(t->stack,(void *)'S');
                        break;
                    case 5:
                        search_add(mytree, 'N', makeNode0('.'), NULL, makeNode0('C'));
                        LinkedList_add_at_front(t->stack, (void *)'C');
                        LinkedList_add_at_front(t->stack, (void *)'.');
                        break;
                    case 6:
                        search_add(mytree, 'N', makeNode0('$'), NULL, NULL);
                        LinkedList_add_at_front(t->stack, (void *)'$');
                        break;
                    case 7:
                        search_add(mytree, 'S', makeNode0('A'), NULL, makeNode0('P'));
                        LinkedList_add_at_front(t->stack, (void *)'P');
                        LinkedList_add_at_front(t->stack, (void *)'A');
                        break;
                    case 8:
                        search_add(mytree, 'P', makeNode0('*'), NULL, makeNode0('P'));
                        LinkedList_add_at_front(t->stack, (void *)'P');
                        LinkedList_add_at_front(t->stack, (void *)'*');
                        break;
                    case 9:
                        search_add(mytree, 'P', makeNode0('$'), NULL, NULL);
                        LinkedList_add_at_front(t->stack, (void *)'$');
                        break;
                    case 10:
                        search_add(mytree, 'A', makeNode0('('), makeNode0('E'), makeNode0(')'));
                        LinkedList_add_at_front(t->stack, (void *)')');
                        LinkedList_add_at_front(t->stack, (void *)'E');
                        LinkedList_add_at_front(t->stack, (void *)'(');
                        break;
                    case 11:
                        search_add(mytree, 'A', makeNode0('X'), NULL, NULL);
                        LinkedList_add_at_front(t->stack, (void *)'X');
                        break;
                    case 12 ... 37:
                        search_add(mytree, 'X', makeNode0((char)(production+85)), NULL, NULL);

                        LinkedList_add_at_front(t->stack, (void *)(long)(production+85));
                        break;
                    default:
                        break;

                }

            }

        }
    }

    if (lookahead<strlen(input)){
        return NULL;
    }
    return mytree;
}

bool isTerminal(char stackItem) {
    char c = stackItem;
    if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h' ||
        c == 'i' || c == 'j' || c == 'k' || c == 'l' || c == 'm' || c == 'n' || c == 'o' || c == 'p' || c == 'q' ||
        c == 'r' || c == 's' || c == 't' || c == 'u' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z' ||
        c == '*' || c == '.' || c == '|' || c == '(' || c == ')' || c == '$') {
//        if (((int)c>=33 && (int)c<=64)&& (int)c<=126){
        return true;
    } else return false;

}


int SyntacticC(Table t, char synC){
    if (synC=='E'){
        return 0;
    }
    else if (synC=='M'){ //ET
        return 1;
    }
    else if (synC=='C'){
        return 2;
    }
    else if (synC=='N'){ //CT
        return 3;
    }
    else if (synC=='S'){
        return 4;
    }
    else if (synC=='P'){ //ST
        return 5;
    }
    else if (synC=='A'){
        return 6;
    }
    else if (synC=='X'){
        return 7;
    }
    else return -1;
}

