/*
 * Yufei Zhao
 * CSC173 Project2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ParseTree.h"
#include "Table.h"
#include "Stack.h"
#define Size 1
#include "LinkedList.h"
//#include "TreeNode.h"

int main() {


    bool notStop=true;
    while(notStop){
        int current_size=Size;
        char *str=malloc(current_size); //let's keep str pointing to beginning of string...
        char *next_read=str; //and next_read pointing to where next character should go
        printf("\nOnly enter strings with lower letters and do not type space within your input)");
        printf("\nNow enter your input (Enter # to quit): ");
        fgets(next_read, current_size, stdin);
        while (str[strlen(str)-1] != '\n'){ //if we got the whole string, the last char will be '\n'
            //printf("\nsize: %d, string: %s", strlen(str), str); //test the string that is already read
            current_size=strlen(str)+Size;
            str=realloc(str,current_size);
            next_read=str+strlen(str);
            fgets(next_read, Size+1, stdin);
        }
        str[strlen(str)-1]='\0';
        char* str1=str;

        if (strcmp(str, "#")!=0){
            printf("Part 1 & 3--Recursive Descent Parser:\n");
            Tree result1=ParseTree(str);
            if (result1==NULL){
                printf("Failed. Input invalid.\n");
            }
            else
                printTree(result1);

            /*Part 2 & 3*/
//            printf("\nPart 2 & 3--Table Driven Parser:\n");
            Table mytable=new_table();
            Tableparser(mytable, str1);

/*            Tree result2=Tableparser(mytable, str1);
            if (result2==NULL){
                printf("Failed. Input invalid.\n");
            }
            else
                printTree(result2);
*/

            /*Regular Expression*/
            printf("\nRegular Expression:\n");
            if (result1==NULL){
                printf("Failed. Input invalid.\n");
            }
            else if (strlen(str)==1){
                printSingleReg(str[0]);
                printf("\n");
            }
            else{
                myexpression(result1);
                printf("\n");
            }
        }
        else {
            notStop=false;
            printf("You exit\n");
        }

    }



}
