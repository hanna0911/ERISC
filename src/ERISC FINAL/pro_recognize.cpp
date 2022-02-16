//
//  pro_recognize.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_recognize.hpp"
#include "pro_header.hpp"
#include <string>
#include <cstring>

//将一行instruction的首段操作命令分辨出来
string recg_instruct(int line){
    string u("");
    int i = 0;
    while(true){
        if((instruction[line][i] == ' ' )||
           (instruction[line][i] == ':' )||
           (instruction[line][i] == '\0' )) break;
        u = u + instruction[line][i];
        i++;
    }
    return u;
}

//识别某一行是什么指令，并进行操作
void recg_line(int line){
    string u = recg_instruct(line);
    //内存访问指令
    if(u == "load"){
        ins_load(line);
        current_line++;
        return;
    }
    if(u == "store"){
        ins_store(line);
        current_line++;
        return;
    }
    //栈操作指令
    if(u == "push"){
        ins_push(line);
        current_line++;
        return;
    }
    if(u == "pop"){
        ins_pop(line);
        current_line++;
        return;
    }
    //寄存器计算指令
    if(u == "mov"){
        ins_mov(line);
        current_line++;
        return;
    }
    if(u == "add"){
        ins_add(line);
        current_line++;
        return;
    }
    if(u == "sub"){
        ins_sub(line);
        current_line++;
        return;
    }
    if(u == "mul"){
        ins_mul(line);
        current_line++;
        return;
    }
    if(u == "div"){
        ins_div(line);
        current_line++;
        return;
    }
    if(u == "rem"){
        ins_rem(line);
        current_line++;
        return;
    }
    if(u == "and"){
        ins_and(line);
        current_line++;
        return;
    }
    if(u == "or"){
        ins_or(line);
        current_line++;
        return;
    }
    //控制指令
    if(u == "jal"){
        ins_jal(line);
        return;
    }
    if(u == "beq"){
        ins_beq(line);
        return;
    }
    if(u == "bne"){
        ins_bne(line);
        return;
    }
    if(u == "blt"){
        ins_blt(line);
        return;
    }
    if(u == "bge"){
        ins_bge(line);
        return;
    }
    if(u == "call"){
        stack_push(line + 1);
        ins_call(line);
        return;
    }
    if(u == "ret"){
        current_line = stack_pop();
        return;
    }
    //可视化指令
    if(u == "draw"){
        cnt_draw++;
        ins_draw();
        current_line++;
        return;
    }
    //不符合以上任何一种：即本行为行标识
    current_line++;
    return;
}

//在某一段字符串可能是寄存器也可能是数字，用于识别该字符串的含义。返回true代表该字符串是数字，返回0代表该字符串是寄存器
bool recg_type(char a[]){
    if((48 <= a[0] && a[0] <= 57) || a[0] == '-') return 1; //return 1: 数字
    return 0; //return 0: 寄存器
}

//用于识别寄存器名称，返回寄存器第一名称下标的数字
int recg_regs(char a[]){
    int l = (int)strlen(a);
    int regsnum = 0;
    
    //别名
    if(a[0] == 'a')
        regsnum = int(a[1] - '0') + 10;
    if(a[0] == 'f') regsnum = 8;
    if(a[0] == 'g') regsnum = 3;
    if(a[0] == 'r') regsnum = 1;
    if(a[0] == 's'){
        if(a[1] == 'p') regsnum = 2;
        else if(a[1] == '1' && l == 2) regsnum = 9;
        else{
            if(l <= 2) regsnum = int(a[1] - '0') + 16;
            else regsnum = int(a[1] - '0') * 10 + int(a[2] - '0') + 16;
        }
    }
    if(a[0] == 't')
    {
        if(a[1] == 'p') regsnum = 4;
        else{
            if(int(a[1] - '0') <= 2) regsnum = int(a[1] - '0') + 5;
            else regsnum = int(a[1] - '0') + 25;
        }
    }
    if(a[0] == 'z') regsnum = 0;
    
    //名称
    if(a[0] == 'x'){
        if(l <= 2){
            regsnum = int(a[1] - '0');
        }
        else{
            regsnum = int(a[1] - '0') * 10 + int(a[2] - '0');
        }
    }
    return regsnum;
}

//计算n^m
int power(int n, int m){
    int product = 1;
    while(m > 0)
    {
        product *= n;
        m--;
    }
    return product;
}

int recg_num(char a[]){
    int l = (int)strlen(a);
    int num = 0;
    //判断是否为负数
    int base = 0;//判断负号是否占数值位，有负号，判断数值需要相应往后错一位
    if(a[0] == '-')
        base = 1;
    //十六进制转换为数字 e.g. 0x12f4 应该变为十进制4852
    if(a[base + 1] == 'x'){
        for(int i = base + 2; i < l; i++){
            int currentnum = int(a[i] - '0'); //如果a[i]是在0-9之间，变成0-9
            //如果a[i]是在a-f之间，变成10-16
            if(int('a' - '0') <= currentnum && currentnum <= int('f' - '0'))
                currentnum = int(a[i] - 'a') + 10;
            //如果a[i]是在A-F之间，变成10-16
            else if(int('A' - '0') <= currentnum && currentnum <= int('F' - '0'))
                currentnum = int(a[i] - 'A') + 10;
            num += currentnum * power(16, l - i - 1);
        }
    }
    //十进制转换为数字 e.g. 26
    else{
        //i是a[i]第i位
        for(int i = base + 0; i < l; i++){
            num += int(a[i] - '0') * power(10, l - i - 1);
        }
    }
    //如果是正数，直接输出数值部分；如果是负数，输出数值部分相反数
    if(base == 0)
        return num;
    else
        return -num;
}
