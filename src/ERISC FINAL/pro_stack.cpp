//
//  pro_stack.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_stack.hpp"
#include "pro_header.hpp"
#include <cstring>

void stack_push(int x){
    pointer--; //栈指针移位
    stack_[pointer]=x; //栈空间赋值
    stack_c = true; //记录栈的变动情况
}

void ins_push(int line){
    //识别寄存器rs
    char a[10]="";
    for(int i=5;instruction[line][i]!='\0';++i)
        a[i-5]=instruction[line][i];
    //将寄存器的值压入栈
    stack_push(register_[recg_regs(a)]);
    //记录寄存器读写情况
    register_r[recg_regs(a)] = true;
}

int stack_pop(){
    int x = stack_[pointer];
    stack_[pointer] = 0; //栈复原
    ++pointer; //指针复原
    stack_c = true; //记录栈读写情况
    return x; //返回栈原存储值
}

void ins_pop(int line){
    //识别指令中寄存器rd
    char a[10]="";
    for(int i=4;instruction[line][i]!='\0';++i)
        a[i-4]=instruction[line][i];
    //将栈的值存入寄存器
    register_[recg_regs(a)] = stack_pop();
    //记录寄存器读写情况
    register_w[recg_regs(a)] = true;

}
