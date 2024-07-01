#include <iostream>
#include "StackVM.hpp"

int main()
{
    puts("This example will calculate Fibonacci numbers up to one thousand and print them out");
    // 这个示例将计算一千以内的斐波拉数
    // StackVM test("1 print 1 print add 3 jmp st");
    // StackVM test("1 print 1 print add 1000 lt 12 if 3 jmp st "); // 不进行垃圾回收
    StackVM test("1 print 1 print add reve swi pop reve swi 1000 lt 17 if 3 jmp st "); // 垃圾回收
    test.Run();
    test.~StackVM();
    return 0;
}
