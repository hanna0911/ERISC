//
//  pro_register.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_register.hpp"
#include "pro_header.hpp"
#include <cstring>

char a[3][20];

//分割instruction[line]中的rd,rs1,rs2至a[0],a[1],a[2]; 仅适用于命令为3字符的命令进行分割
void divide_char(int line){
    for(int i=0;i<3;i++)
        for(int j=0;j<10;j++)
            a[i][j]='\0';
    int length = (int)(strlen(instruction[line]));
    int xnum=0;//记录当前是哪一个字符串
    int k=0;//记录字符串的下标
    for(int i=4;i<length;i++)
    {
        if(instruction[line][i]==',')
        {
            k=0;
            xnum++;
            continue;
        }
        else{
            a[xnum][k]=instruction[line][i];
            k++;
        }
    }
}

//ins_mov含义：处理的第line行的instruction，对应命令为mov [rd],[rs/imm]，  表示将寄存器[rs]或立即数[imm]的值赋值给寄存器[rd]。
void ins_mov(int line){
    //将instruction[line]一整行中代表着rd与rs的字符串分割出来；a for rd, b for rs
    char a[20]="",b[20]="";
    int id = 0;//负责记录‘，’的位置
    for(int i = 4; instruction[line][i] != '\0'; ++i)
        if(instruction[line][i] == ','){
            id = i; break; //寻找id的位置
        }
    for(int i = 4; i < id; ++i)
        a[i-4] = instruction[line][i];//记录rd
    for(int i = id + 1; instruction[line][i] != '\0'; ++i)
        b[i-(id+1)] = instruction[line][i];//记录rs
    
    //先判断第二个字符串是数字还是寄存器，再分别按照规则，改变寄存器的值，并记录寄存器的读写状态以绘制可视化图像； 其中recg_type(b)返回值1代表数字；0代表寄存器
    if(recg_type(b)){
        register_[recg_regs(a)]=recg_num(b);
        register_w[recg_regs(a)] = true;
    }
    else{
        register_[recg_regs(a)]=register_[recg_regs(b)];
        register_w[recg_regs(a)] = true;
        register_r[recg_regs(b)] = true;
    }
}


//ins_add含义：处理的第line行的instruction，对应命令为add [rd],[rs1],[rs2/imm]，  表示将寄存器[rs1]的值和寄存器[rs2]或立即数[imm]的值相加，结果赋值给寄存器[rd]
void ins_add(int line)
{
    divide_char(line);
    
    //先判断第三个字符串是数字还是寄存器，再分别按照规则，改变寄存器的值，并记录寄存器的读写状态以绘制可视化图像； 其中recg_type()返回值1代表数字；0代表寄存器
    if(recg_type(a[2]))
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]+recg_num(a[2]);
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        
    }
    else
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]+register_[recg_regs(a[2])];
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        register_r[recg_regs(a[2])]=true;
    }
}


//ins_sub含义：处理的第line行的instruction，对应命令为sub [rd],[rs1],[rs2/imm]，  表示将寄存器[rs1]的值和寄存器[rs2]或立即数[imm]的值相减， 结果赋值给寄存器[rd]。
void ins_sub(int line)
{
    divide_char(line);
    
    //先判断第三个字符串是数字还是寄存器，再分别按照规则，改变寄存器的值，并记录寄存器的读写状态以绘制可视化图像； 其中recg_type()返回值1代表数字；0代表寄存器
    if(recg_type(a[2]))
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]-recg_num(a[2]);
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        
    }
    else
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]-register_[recg_regs(a[2])];
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        register_r[recg_regs(a[2])]=true;
    }
}

//ins_mul含义：处理的第line行的instruction，对应命令为mul [rd],[rs1],[rs2/imm]，  表示将寄存器[rs1]的值和寄存器[rs2]或立即数[imm]的值相乘， 结果赋值给寄存器[rd]。
void ins_mul(int line)
{
    divide_char(line);
    
    //先判断第三个字符串是数字还是寄存器，再分别按照规则，改变寄存器的值，并记录寄存器的读写状态以绘制可视化图像； 其中recg_type()返回值1代表数字；0代表寄存器
    if(recg_type(a[2]))
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]*recg_num(a[2]);
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        
    }
    else
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]*register_[recg_regs(a[2])];
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        register_r[recg_regs(a[2])]=true;
    }
}

//ins_div含义：处理的第line行的instruction，对应命令为div [rd],[rs1],[rs2/imm]，  表示将寄存器[rs1]的值除以寄存器[rs2]或立即数[imm]的值向 零舍入，结果赋值给寄存器[rd]。
void ins_div(int line)
{
    divide_char(line);
    
    //先判断第三个字符串是数字还是寄存器，再分别按照规则，改变寄存器的值，并记录寄存器的读写状态以绘制可视化图像； 其中recg_type()返回值1代表数字；0代表寄存器
    if(recg_type(a[2]))
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]/recg_num(a[2]);
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        
    }
    else
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]/register_[recg_regs(a[2])];
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        register_r[recg_regs(a[2])]=true;
    }
}


//ins_rem含义：处理的第line行的instruction，对应命令为rem [rd],[rs1],[rs2/imm]，  表示将寄存器[rs1]的值除以寄存器[rs2]或立即数[imm]的余数， 结果赋值给寄存器[rd]。
void ins_rem(int line)
{
    divide_char(line);
    
    //先判断第三个字符串是数字还是寄存器，再分别按照规则，改变寄存器的值，并记录寄存器的读写状态以绘制可视化图像； 其中recg_type()返回值1代表数字；0代表寄存器
    if(recg_type(a[2]))
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]%recg_num(a[2]);
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        
    }
    else
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]%register_[recg_regs(a[2])];
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        register_r[recg_regs(a[2])]=true;
    }
}

//ins_and含义：处理的第line行的instruction，对应命令为and [rd],[rs1],[rs2/imm]，  表示将寄存器[rs1]的值和寄存器[rs2]或立即数[imm]的值按位 与，结果赋值给寄存器[rd]。
void ins_and(int line)
{
    divide_char(line);
    
    //先判断第三个字符串是数字还是寄存器，再分别按照规则，改变寄存器的值，并记录寄存器的读写状态以绘制可视化图像； 其中recg_type()返回值1代表数字；0代表寄存器
    if(recg_type(a[2]))
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]&recg_num(a[2]);
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        
    }
    else
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]&register_[recg_regs(a[2])];
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        register_r[recg_regs(a[2])]=true;
    }
}


//ins_or含义：处理的第line行的instruction，对应命令为or [rd],[rs1],[rs2/imm]，  表示将寄存器[rs1]的值和寄存器[rs2]或立即数[imm]的值按位 或，结果赋值给寄存器[rd]。
void ins_or(int line)
{
    //分割instruction[line]中的rd,rs1,rs2至a[0],a[1],a[2];
    char a[3][10];
    for(int i=0;i<3;i++)
        for(int j=0;j<10;j++)
            a[i][j]='\0';
    int length=(int)strlen(instruction[line]);
    int xnum=0;
    int k=0;
    for(int i=3;i<length;i++)
    {
        if(instruction[line][i]==',')
        {
            k=0;
            xnum++;
            continue;
        }
        else{
            a[xnum][k]=instruction[line][i];
            k++;
        }
    }
    
    //先判断第三个字符串是数字还是寄存器，再分别按照规则，改变寄存器的值，并记录寄存器的读写状态以绘制可视化图像； 其中recg_type()返回值1代表数字；0代表寄存器
    if(recg_type(a[2]))
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]|recg_num(a[2]);
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        
    }
    else
    {
        register_[recg_regs(a[0])]=register_[recg_regs(a[1])]|register_[recg_regs(a[2])];
        register_w[recg_regs(a[0])]=true;
        register_r[recg_regs(a[1])]=true;
        register_r[recg_regs(a[2])]=true;
    }
}
