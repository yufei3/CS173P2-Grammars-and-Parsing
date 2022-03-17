//
// Created by Rainy ZHAO on 2020/10/9.
//

#include <stdio.h>
#include  <stdlib.h>
#include <stdbool.h>
#include "Stack.h"

typedef  struct Node* Node;
struct Node{
    char data;
    Node next;
    Node prev;
};

struct Stack{
    Node top;
    Node bottom;
    int size;
};

Stack new_Stack(){
    Stack this=(Stack)malloc(sizeof(struct Stack));
    this->top=NULL;
    this->bottom=NULL;
    this->size=0;
    return this;
}

Node new_Node(char data){
    Node this=(Node)malloc(sizeof(struct Node));
    this->data=data;
    this->next=this->prev=NULL;
    return this;
}
bool Stack_isEmpty(const Stack this){
    return this->top==NULL;
}

void Stack_add(Stack this, char value){
    Node node=new_Node(value);

    if (this->top!=NULL){
        this->top->prev=node;
        node->next=this->top;
    }
    this->top=node;
    if(this->bottom==NULL){
        this->bottom=node;
    }
    this->size++;
}

char Stack_pop(Stack this){
    if (!Stack_isEmpty(this)){
        this->size--;
        Node result=this->top;
        Node newTop=this->top->next;
        this->top=newTop;
        if (newTop!=NULL){
            newTop->prev=NULL;
        }
        return result->data;
    }
    else return '$';
}

char Stack_removeBottom(Stack this){
    if (!Stack_isEmpty(this)){
        this->size--;
        Node result=this->bottom;
        if (this->bottom->prev==NULL){
            this->bottom=this->top=NULL;
        }
        else {
            Node newBottom=this->bottom->prev;
            this->bottom=newBottom;
            if (newBottom!=NULL){
                newBottom->next=NULL;
            }
        }
        return result->data;
    }
    else return '$';
}

char Stack_peek(Stack this){
    if (!Stack_isEmpty(this)){
        return this->top->data;
    }
    else return '$';
}

char Stack_lookBottom(Stack this){
    if (!Stack_isEmpty(this)){
        return this->bottom->data;
    }
    else return '$';
}

void Stack_TopPrint(Stack this){
    Node n=this->top;
    if (Stack_isEmpty(this)){
        printf("Empty.\n");
        return;
    }
    while(n!=NULL){
        printf("%c", n->data);
        n=n->next;
    }
}

void Stack_BottomPrint(Stack this) {
    Node n = this->bottom;
    if (Stack_isEmpty(this)) {
        printf("Empty.\n");
        return;
    }
    while (n != NULL) {
        printf("%c", n->data);
        n = n->prev;
    }
}

