//
//  pro_output.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_output.hpp"
#include "pro_header.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

void output()
{
    ofstream fout("../output/result.txt") ;
    if(!fout)
    {
        cout<<"输出文件打开失败"<<endl;
        return;
    }
    
    //输出寄存器的值（16进制）
    for(int i=0;i<32;i++)
        fout << hex << register_[i] << " ";
    fout<<endl;
    
    //输出内存的值(格式：小端输出、字节单位、64个字节后换行）
    for(int i=0;i<1048576;i++)
    {
        unsigned int temp_memory = memory[i];
        int a[4];
        a[0]=temp_memory%256;
        a[1]=(temp_memory/256)%256;
        a[2]=(temp_memory/256/256)%256;
        a[3]=temp_memory/256/256/256;
        fout<<setw(2)<<setfill('0')<<hex<<a[0]<<" ";
        fout<<setw(2)<<setfill('0')<<hex<<a[1]<<" ";
        fout<<setw(2)<<setfill('0')<<hex<<a[2]<<" ";
        fout<<setw(2)<<setfill('0')<<hex<<a[3]<<" ";
        if((i+1)%16==0)fout<<endl;
    }
    fout.close();
}
