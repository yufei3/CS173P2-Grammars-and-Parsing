cmake_minimum_required(VERSION 3.17)
project(Project2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Project2
        LinkedList.c
        LinkedList.h
        main.c
        ParseTree.c
        ParseTree.h
        Stack.c
        Stack.h
        Table.c
        Table.h
        TreeNode.c
        TreeNode.h)
