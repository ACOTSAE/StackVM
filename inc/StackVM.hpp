#define _CRT_SECURE_NO_WARNINGS
#define N 36

#ifndef _STACKVM_HPP_
    #define _STACKVM_HPP_

    #include <stdio.h>
    #include <stdlib.h>
    #include <cstdint>
    #include <stack>
    #include <vector>
    #include <string>

// 双栈结构虚拟机，等价于图灵机。如果只使用一个栈，那么这个虚拟机等价为下推自动机
//
//
class StackVM
{
public:
    StackVM(){};

    StackVM(const StackVM &VM)
    {
        this->VM_Cseq = new std::vector<std::string>;
        this->VM_Cseq->assign(VM.VM_Cseq->begin(), VM.VM_Cseq->end());
        this->VM_stackA = new std::stack<int>;
        this->VM_stackB = new std::stack<int>;
        this->VM_stackC = this->VM_stackB;
    };

    StackVM(std::string Command_Seq)
    {
        this->VM_Cseq = new std::vector<std::string>;
        this->VM_stackA = new std::stack<int>;
        this->VM_stackB = new std::stack<int>;
        this->VM_stackC = this->VM_stackB;

        uint32_t start = 0, end = 1;
        const uint32_t size = Command_Seq.size();
        while(start < size && end < size) {
            if(Command_Seq[start] == ' ') { ++start; }
            else {
                end = start;
                ++end;
                while(end <= size) {
                    if(Command_Seq[end] == ' ') {
                        this->VM_Cseq->emplace_back(Command_Seq.substr(start, end - start));
                        start = end;
                        ++end;
                        break;
                    }
                    ++end;
                }
            }
        }
    };

    StackVM(std::vector<std::string> Command_Seq)
    {
        this->VM_Cseq = new std::vector<std::string>(Command_Seq);
        this->VM_stackA = new std::stack<int>;
        this->VM_stackB = new std::stack<int>;
        this->VM_stackC = this->VM_stackB;
    };

    // 接受字符串作为指令序列初始化
    inline int VMInit(std::string Command_Seq)
    {
        this->VM_Cseq = new std::vector<std::string>;
        this->VM_stackA = new std::stack<int>;
        this->VM_stackB = new std::stack<int>;
        this->VM_stackC = this->VM_stackB;
        uint32_t start = 0, end = 1;
        const uint32_t size = Command_Seq.size();
        while(start < size && end < size) {
            if(Command_Seq[start] == ' ') { ++start; }
            else {
                end = start;
                ++end;
                while(end < size) {
                    if(Command_Seq[end] == ' ') {
                        this->VM_Cseq->emplace_back(Command_Seq.substr(start, end - start));
                        start = end;
                        ++end;
                        break;
                    }
                    ++end;
                }
            }
        }
    };

    // 接受指令序列初始化
    inline int VMInit(std::vector<std::string> Command_Seq)
    {
        this->VM_Cseq = new std::vector<std::string>(Command_Seq);
        this->VM_stackA = new std::stack<int>;
        this->VM_stackB = new std::stack<int>;
        this->VM_stackC = this->VM_stackB;
        return 0;
    };

    // 软重置，不清除指令序列，无需再次初始化
    inline int SoftReset()
    {
        this->PC = 0;
        this->VM_Cache = 0;
        this->VM_Top_Cache = 0;
        delete this->VM_stackA;
        delete this->VM_stackB;
        this->VM_stackA = new std::stack<int>;
        this->VM_stackB = new std::stack<int>;
        this->VM_stackC = this->VM_stackB;
        return 0;
    };

    // 硬重置，清除指令序列，清除数据栈，归零寄存器，需要再次初始化
    inline int HardReset()
    {
        this->VM_stackC = nullptr;
        delete this->VM_Cseq;
        delete this->VM_stackA;
        delete this->VM_stackB;
        this->PC = 0;
        this->VM_Cache = 0;
        this->VM_Top_Cache = 0;
        return 0;
    };

    // 将栈顶数据弹出到虚拟机外
    inline int Out()
    {
        this->VM_Top_Cache = this->VM_stackC->top();
        this->VM_stackC->pop();
        return this->VM_Top_Cache;
    }

    // 将虚拟机外数据压入当前数据栈
    inline int In(int &top)
    {
        this->VM_Top_Cache = top;
        this->VM_stackC->push(this->VM_Top_Cache);
        return 0;
    }

    inline int Run()
    {
        const uint32_t size = this->VM_Cseq->size();
        uint32_t num = 1;
        while((this->PC & 0x7FFFFFFF) < size) {
            if(this->VM_Cseq->at((PC & 0x7FFFFFFF)) == "st") break;
            if(isdigit(this->VM_Cseq->at((PC & 0x7FFFFFFF)).c_str()[0])) {
                int n = atoi(this->VM_Cseq->at((PC & 0x7FFFFFFF)).c_str());
                this->VM_stackC->push(n);
            }
            else {
                for(; num < N; ++num) {
                    if(this->VM_Cseq->at((PC & 0x7FFFFFFF)) == (const char *)ISA[num]) {
                        (this->*Com[num])();
                        num = 1;
                        break;
                    }
                }
            }
            num = 1;
            ++(this->PC);
        }
        return 0;
    };

    inline int RunByStep()
    {
        const uint32_t size = this->VM_Cseq->size();
        uint32_t num = 1;
        if((this->PC & 0x7FFFFFFF) < size) {
            if(this->VM_Cseq->at(PC) == "st") return 1;
            if(isdigit(this->VM_Cseq->at(PC).c_str()[0])) {
                int n = atoi(this->VM_Cseq->at(PC).c_str());
                this->VM_stackC->push(n);
            }
            else {
                for(; num < N; ++num) {
                    if(this->VM_Cseq->at(PC) == (const char *)ISA[num]) {
                        (this->*Com[num])();
                        num = 1;
                        break;
                    }
                }
            }
            num = 1;
            ++(this->PC);
            return 0;
        }
        return 0;
    };

    inline int PrintCSeq() const
    {
        for(auto Cseq = this->VM_Cseq->begin(); Cseq != this->VM_Cseq->end(); ++Cseq) { printf("%s ", Cseq->c_str()); }
        putchar('\n');
        return 0;
    };

    inline int PrintRegister() const
    {
        printf("Current Command is [%s]\n"
               "Register PC = %d\n"
               "Register VM_Cache = %d\n"
               "Register VM_Top_Cache = %d\n",
               this->VM_Cseq->at(PC).c_str(), this->PC & 0x7FFFFFFF, this->VM_Cache, this->VM_Top_Cache);
        printf("Current DataStack is VM_Stack%c\n", (PC & 0x80000000 ? 'A' : 'B'));
        return 0;
    }

    inline int PrintDataStack()
    {
        std::stack<int> *tempStack = new std::stack<int>(*this->VM_stackA);
        puts("VM_stackA:");
        while(!tempStack->empty()) {
            printf("%d ", tempStack->top());
            tempStack->pop();
        }
        putchar('\n');
        delete tempStack;
        puts("VM_stackB:");
        tempStack = new std::stack<int>(*this->VM_stackB);
        while(!tempStack->empty()) {
            printf("%d ", tempStack->top());
            tempStack->pop();
        }
        putchar('\n');
        delete tempStack;
        return 0;
    }

    inline int PrintISA() const
    {
        for(int n = 0; n < N; ++n) printf("%s ", (const char *)this->ISA[n]);
        return 0;
    }

private:
    // ~StackVM();
    std::vector<std::string> *VM_Cseq = nullptr; // VM指令序列
    std::stack<int> *VM_stackA = nullptr;        // VM数据栈A
    std::stack<int> *VM_stackB = nullptr;        // VM数据栈B
    std::stack<int> *VM_stackC = nullptr;        // VM当前数据栈
    uint32_t PC = 0;                             // 程序计数寄存器，最高位为栈判断位
    uint32_t VM_Cache = 0;                       // VM通用缓存
    uint32_t VM_Top_Cache = 0;                   // VM栈顶缓存，也是返回值寄存器

    // 切换数据栈
    inline int VM_Switch()
    {
        this->PC ^= 0x80000000;
        if(this->PC & 0x80000000) { this->VM_stackC = this->VM_stackA; }
        else {
            this->VM_stackC = this->VM_stackB;
        }
        return 0;
    };

    // 对于"le", "lt", "ge", "gt", "eq", "ne"，指令弹出操作数，将结果压栈，"0"为假，非零为真

    int VM_Le();
    int VM_Lt();
    int VM_Ge();
    int VM_Gt();
    int VM_Eq();
    int VM_Ne();

    // 算数运算，不弹出操作数，结果入栈

    int VM_Add();
    int VM_Sub();
    int VM_Mul();
    int VM_Div();
    int VM_Mod();

    // 算数运算，不弹出操作数，修改栈顶

    int VM_Add_Assign();
    int VM_Sub_Assign();
    int VM_Mul_Assign();
    int VM_Div_Assign();
    int VM_Mod_Assign();

    // 位运算，弹出操作数，结果入栈

    int VM_And();
    int VM_Or();
    int VM_Not();
    int VM_Xor();
    // 循环左移次栈顶数据，左移多少位由栈顶决定，弹出操作数，结果入栈
    int VM_Left();
    // 循环右移次栈顶数据，右移多少位由栈顶决定，弹出操作数，结果入栈
    int VM_Right();
    // 无条件转移，弹出操作数
    int VM_Jmp();
    // 若栈次顶数据为真，执行之后语句，否则跳到栈顶指定位置
    // 弹出操作数
    int VM_If();

    // 数据访问

    // 将栈顶数据弹出到通用缓存
    int VM_Pop();
    // 将通用缓存压栈
    int VM_Push();
    // 将栈顶数据弹出到栈顶缓存
    int VM_PopT();
    // 将栈顶缓存压栈
    int VM_PushT();

    int VM_MovA();
    int VM_MovB();
    int VM_Swap();
    int VM_Reve();
    // 输出栈顶数据以及一个空格，printf("%d",栈顶数据)
    int VM_Print();
    // 接受一个int型数据压入数据栈
    int VM_Scan();

    // 指令集
    // st是个内建指令，不使用函数实现
    constexpr volatile static const char *ISA[] = {
        "st",  "swi",  "le",   "lt",   "ge",   "gt",    "eq",   "ne",   "add",  "sub",  "mul",   "div",
        "mod", "adda", "suba", "mula", "diva", "moda",  "and",  "or",   "not",  "xor",  "left",  "right",
        "jmp", "if",   "pop",  "push", "popt", "pusht", "mova", "movb", "swap", "reve", "print", "scan"};
    constexpr static int (StackVM::*Com[])() = {
        nullptr,        &VM_Switch,     &VM_Le,    &VM_Lt,   &VM_Ge,   &VM_Gt,         &VM_Eq,         &VM_Ne,
        &VM_Add,        &VM_Sub,        &VM_Mul,   &VM_Div,  &VM_Mod,  &VM_Add_Assign, &VM_Sub_Assign, &VM_Mul_Assign,
        &VM_Div_Assign, &VM_Mod_Assign, &VM_And,   &VM_Or,   &VM_Not,  &VM_Xor,        &VM_Left,       &VM_Right,
        &VM_Jmp,        &VM_If,         &VM_Pop,   &VM_Push, &VM_PopT, &VM_PushT,      &VM_MovA,       &VM_MovB,
        &VM_Swap,       &VM_Reve,       &VM_Print, &VM_Scan};
};

#endif
