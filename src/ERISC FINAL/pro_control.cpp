//
//  pro_control.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_control.hpp"
#include "pro_header.hpp"
#include <cstring>


char b[2][10]; //代表该行命令中的寄存器
char aa[50]; //代表该行命令中的行标识

//将条件跳转行中的两个寄存器进行识别
void divide_char_regs(int line){
    //初始化a
    for(int i=0;i<2;i++)
        for(int j=0;j<10;j++)
            b[i][j]='\0';
    int xnum=0;//代表寄存器是哪一个
    int k=0;//代表当前寄存器中的下标
    for(int i=4;xnum<2;i++)
    {
        if(instruction[line][i]==',')
        {
            k=0;
            xnum++;
            continue;
        }
        else{
            b[xnum][k]=instruction[line][i];
            k++;
        }
    }
}

//将条件跳转行中的行标识进行识别
void divide_char_RIDs(int line){
    int length=(int)(strlen(instruction[line])-4-2-strlen(b[0])-strlen(b[1])); //为行标识定位
    for(int i=0;i<length;i++)
        aa[i]=instruction[line][i+6+strlen(b[0])+strlen(b[1])];
    aa[length]='\0';
}

//在记录过的行标识中寻找与aa相同的，确定其行号
int find_line_RIDs(int line){
    for(int i=0;i<sumRIDs;i++)
        if(strcmp(RIDs[i].inst,aa)==0)
            return RIDs[i].row;
    return line;
}

//使程序指令接下来将从[行标识]处开始执行。
void ins_jal(int line)
{
    //判断行标识
    int length=int(strlen(instruction[line])-4);
    for(int i=0;i<length;i++)
        aa[i]=instruction[line][i+4];
    aa[length]='\0';
    //进行程序运行的“当前行”跳转
    current_line = find_line_RIDs(line) + 1;
}

//表示将寄存器[rs1]和寄存器[rs2]的值进行比较，如果二者相等，则跳转至[行标识]处的后一行，否则继续执行下一条指令。
void ins_beq(int line)
{
    divide_char_regs(line);
    if(register_[recg_regs(b[0])]==register_[recg_regs(b[1])])
    {
        divide_char_RIDs(line);
        current_line = find_line_RIDs(line) + 1;
    }
    else current_line++;
}

//表示将寄存器[rs1]和寄存器[rs2]的值进行比较，如果二者不等，则跳转至[行标识]处的后一行，否则继续执行下一条指令。
void ins_bne(int line)
{
    divide_char_regs(line);
    if(register_[recg_regs(b[0])]!=register_[recg_regs(b[1])])
    {
        divide_char_RIDs(line);
        current_line = find_line_RIDs(line) + 1;
    }
    else current_line++;
}

//表示将寄存器[rs1]和寄存器[rs2]的值进行比较，如果前者小于后者，则跳转至[行标识]处的后一行，否则继续执行下一条指令。
void ins_blt(int line)
{
    divide_char_regs(line);
    if(register_[recg_regs(b[0])]<register_[recg_regs(b[1])])
    {
        divide_char_RIDs(line);
        current_line = find_line_RIDs(line) + 1;
    }
    else current_line++;
}

//表示将寄存器[rs1]和寄存器[rs2]的值进行比较，如果前者大于等于后者，则跳转至[行标识]处的后一行，否则继续执行下一条指令。
void ins_bge(int line)
{
    divide_char_regs(line);
    if(register_[recg_regs(b[0])]>=register_[recg_regs(b[1])])
    {
        divide_char_RIDs(line);
        current_line = find_line_RIDs(line) + 1;
    }
    else current_line++;
}

void ins_call(int line)
{
    int length=(int)strlen(instruction[line])-5;
    for(int i=0;i<length;i++)
        aa[i]=instruction[line][i+5];
    aa[length]='\0';
    current_line = find_line_RIDs(line) + 1;
}
