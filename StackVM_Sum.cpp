#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include "StackVM.hpp"

int main()
{
    printf("This StackVM will implement the following C language code\n"
           "int sum = 0;\n"
           "for(int i=1; i<11; i++) {\n"
           "    sum += i;\n"
           "}\n"
           "print(\"%%d \"), sum\n");
    StackVM VM_Sum("0 1 11 lt 12 if adda push 1 adda 2 jmp pop print st ");
    VM_Sum.Run();
    return 0;
}
