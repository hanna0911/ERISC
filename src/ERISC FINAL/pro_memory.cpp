//
//  pro_memory.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_memory.hpp"
#include "pro_header.hpp"
#include <cstring>

//memory中两个函数的特点：代表地址的寄存器在后

//ins_load含义：处理的第line行的instruction，对应命令为内存数据加载:load [rd],[rs]； 将内存中地址为寄存器[rs]中值的 32 位数据加载到寄存器 [rd]中。
void ins_load(int line){
    //将instruction[line]一整行中代表着rd与rs的字符串分割出来
    char rd[10] = "",rs[10] = "";
    int id = 0;//负责记录‘，’的位置
    for(int i = 5; instruction[line][i] != '\0'; ++i)
        if(instruction[line][i] == ','){
            id = i; break; //寻找id的位置
        }
    for(int i = 5; i < id; ++i)
        rd[i-5] = instruction[line][i];//记录rd
    for(int i = id + 1; instruction[line][i] != '\0'; ++i)
        rs[i-(id+1)] = instruction[line][i];//记录rs
    
    //将内存中地址为寄存器[rs]中值的32位数据加载到寄存器[rd]中
    int tmp = register_[recg_regs(rs)] / 4; //默认rs为4的倍数，否则向下取整；tmp代表rs中地址所对应的，memory中int类型地址的下标值
    register_[recg_regs(rd)] = memory[tmp];
    
    //记录寄存器、内存的读写状态，便于绘制可视化图像
    register_r[recg_regs(rs)] = true;
    register_r[recg_regs(rd)] = true;
    memory_c[tmp / power(2, 16)] = true;
}



//ins_store含义：处理的第line行的instruction，对应命令为内存数据加载:store [rs],[rd]； 表示将寄存器[rs]的值存入内存地址为寄存器[rd]中值的存储空间中。
void ins_store(int line){
    //将instruction[line]一整行中代表着rs与rd的字符串分割出来
    char rd[10] = "",rs[10] = "";
    int id = 0;//负责记录‘，’的位置
    for(int i = 6; instruction[line][i] != '\0'; ++i)
        if(instruction[line][i] == ','){
            id = i; break; //寻找id的位置
        }
    for(int i = 6; i < id; ++i)
        rs[i-6] = instruction[line][i];//记录rd
    for(int i = id + 1; instruction[line][i] != '\0'; ++i)
        rd[i-(id+1)] = instruction[line][i];//记录rs
    
    //将寄存器[rs]的值存入内存地址为寄存器[rd]中值的存储空间中。
    int tmp = register_[recg_regs(rd)] / 4; //默认rd为4的倍数，否则向下取整；tmp代表rd中地址所对应的，memory中int类型地址的下标值
    memory[tmp] = register_[recg_regs(rs)];
    
    //记录寄存器、内存的读写状态，便于绘制可视化图像
    register_r[recg_regs(rs)] = true;
    register_r[recg_regs(rd)] = true;
    memory_c[tmp / power(2, 16)] = true;
}
