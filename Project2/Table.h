//
// Created by Rainy ZHAO on 2020/10/4.
//

#ifndef UNTITLED2_TABLE_H
#define UNTITLED2_TABLE_H

#endif //UNTITLED2_TABLE_H
#include <stdbool.h>

typedef  struct Table *Table;
Table new_table();
Tree Tableparser(Table t, char *input);
bool isTerminal(char input);
int SyntacticC(Table t, char synC);
