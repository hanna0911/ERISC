//
//  main.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include <iostream>
#include "pro_header.hpp"
#include <cstring>

using namespace std;

int register_[32]; //用于实时依次记录寄存器x0~x31内的值，初始值均为0
bool register_r[32]; //用于依次记录寄存器x0~x31被读取（read）的情况，初始值为false，每次执行draw指令后赋值为false，在相应的寄存器被读取时赋值为true
bool register_w[32]; //用于依次记录寄存器x0~x31被赋值（write）的情况，初始值为false，每次执行draw指令后赋值为false，在相应的寄存器被读取时赋值为true
bool memory_c[16];
    //用于依次记录内存每连续的256kB被赋值或读取（change）的情况，初始值为false，每次执行draw指令后赋值为false，在相应的内存区间被读取或赋值时赋值为true
int memory[1048576]; //（1048576=1024×1024）用于依次记录内存中每连续的4个字节按小端访问原则储存的32位整数的值
bool stack_c; //用于记录栈的使用情况，初始值为false，每次执行draw指令后赋值为false，在栈空间被使用时赋值为true
int stack_[1048576+1]; //（1048576=1024×1024）用于依次记录栈空间中每连续的4个字节储存的32位整数的值
int pointer; //用于记录当前栈顶指向的地址，初始值为4M
char instruction[200][50]; //用于以行为单位读取输入的ERISC指令，char[i]指向输入的ERISC指令第i行（从第0行开始计）整行的指令字符串
int current_line; //用于记录程序执行的当前行的行数，初值为0
int sumRIDs; //用于记录含有行标识的指令的总行数
int total_line; //用于记录输入的ERISC指令的总行数
int cnt_draw; //用于记录draw指令执行的总次数
rids RIDs[200]; //用于记录所有含行标识指令的行号和具体指令内容；rids定义见header


int main(int argc, const char * argv[]) {
    //将所有初始化
    initialize();
    //读取cin文件，并判断读入文件是否成功
    if(input() == false)
        return 0;
    //寻找并记录所有行标识
    find_RIDs();
    while(1)
    {
        //运行到end行，输出，结束程序
        if(strcmp("end", instruction[current_line]) == 0)
        {
            output();
            break;
        }
        //运行当前current_line行的命令，换行指令在recg_line中实现
        recg_line(current_line);
    }
    
    return 0;
}
