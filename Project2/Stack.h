//
// Created by Rainy ZHAO on 2020/10/9.
//

#ifndef UNTITLED2_STACK_H
#define UNTITLED2_STACK_H

#endif //UNTITLED2_STACK_H

typedef struct Stack* Stack;
Stack new_Stack();
bool Stack_isEmpty(const Stack this);
void Stack_add(Stack this, char value);
char Stack_pop(Stack this);
char Stack_removeBottom(Stack this);
char Stack_peek(Stack this);
char Stack_lookBottom(Stack this);
void Stack_TopPrint(Stack this);
void Stack_BottomPrint(Stack this);

