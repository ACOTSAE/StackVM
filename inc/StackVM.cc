#include "StackVM.hpp"

int StackVM::VM_Le()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_Top_Cache = (this->VM_Cache >= this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Lt()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_Top_Cache = (this->VM_Cache > this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Ge()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_Top_Cache = (this->VM_Cache <= this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Gt()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_Top_Cache = (this->VM_Cache < this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Eq()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_Top_Cache = (this->VM_Cache == this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Ne()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_Top_Cache = (this->VM_Cache != this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Add()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_stackC->push(this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Cache);
    this->VM_Top_Cache += this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Sub()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_stackC->push(this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Cache);
    this->VM_Top_Cache -= this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
    return 0;
}

int StackVM::VM_Mul()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_stackC->push(this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Cache);
    this->VM_Top_Cache *= this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
    return 0;
}

int StackVM::VM_Div()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_stackC->push(this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Cache);
    this->VM_Top_Cache /= this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
    return 0;
}

int StackVM::VM_Mod()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_stackC->push(this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Cache);
    this->VM_Top_Cache %= this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
    return 0;
}

int StackVM::VM_Left()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = (this->VM_Top_Cache >> (const uint32_t)(32 - this->VM_Cache) |
                          (this->VM_Top_Cache << (const uint32_t)(this->VM_Cache)));
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Right()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = (this->VM_Top_Cache << (const uint32_t)(32 - this->VM_Cache) |
                          (this->VM_Top_Cache >> (const uint32_t)(this->VM_Cache)));
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Pop()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    return 0;
}

int StackVM::VM_Push()
{
    this->VM_stackC->push(this->VM_Cache);
    return 0;
}

int StackVM::VM_PopT()
{
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    return 0;
}

int StackVM::VM_PushT()
{
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Jmp()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->PC = this->VM_Cache;
    --(this->PC);
    return 0;
}

int StackVM::VM_If()
{
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    if(this->VM_Cache == 0) {
        this->PC = this->VM_Top_Cache;
        --(this->PC);
    }
    return 0;
}

int StackVM::VM_MovA()
{
    if(this->VM_stackC == this->VM_stackA) {
        this->VM_stackC->pop();
        this->VM_Cache = 0; // 缓存一致性
        return 0;
    }
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    while(this->VM_Cache--) {
        this->VM_Top_Cache = this->VM_stackC->top();
        this->VM_stackC->pop();
        this->VM_stackA->push(this->VM_Top_Cache);
    }
    return 0;
}

int StackVM::VM_MovB()
{
    if((void *)(this->VM_stackC) == (void *)(this->VM_stackB)) {
        this->VM_stackC->pop();
        this->VM_Cache = 0;
        return 0;
    }
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    while(this->VM_Cache--) {
        this->VM_Top_Cache = this->VM_stackC->top();
        this->VM_stackC->pop();
        this->VM_stackB->push(this->VM_Top_Cache);
    }
    return 0;
}

int StackVM::VM_Reve()
{
    if(this->PC & 0x80000000) {
        // 2B
        while(!(this->VM_stackC->empty())) {
            this->VM_Top_Cache = this->VM_stackC->top();
            this->VM_stackC->pop();
            this->VM_stackB->push(this->VM_Top_Cache);
        }
    }
    else {
        // 2A
        while(!(this->VM_stackC->empty())) {
            this->VM_Top_Cache = this->VM_stackC->top();
            this->VM_stackC->pop();
            this->VM_stackA->push(this->VM_Top_Cache);
        }
    }
    return 0;
}

int StackVM::VM_Swap()
{
    std::swap(this->VM_stackB, this->VM_stackA);
    return 0;
}

int StackVM::VM_Add_Assign()
{
    //[6,3]
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache += this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Sub_Assign()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache -= this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Mul_Assign()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache *= this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Div_Assign()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache /= this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Mod_Assign()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache %= this->VM_Cache;
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_And()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = (this->VM_Cache & VM_stackC->top());
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Or()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = (this->VM_Cache | VM_stackC->top());
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Not()
{
    this->VM_Cache = this->VM_stackC->top();
    this->VM_Top_Cache = ~(this->VM_Cache); // 缓存一致性
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Xor()
{

    this->VM_Cache = this->VM_stackC->top();
    this->VM_stackC->pop();
    this->VM_Top_Cache = (this->VM_Cache ^ VM_stackC->top());
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}

int StackVM::VM_Print()
{
    printf("%d ", this->VM_stackC->top());
    return 0;
}

int StackVM::VM_Scan()
{
    scanf("%d", &this->VM_Top_Cache);
    this->VM_stackC->push(this->VM_Top_Cache);
    return 0;
}
