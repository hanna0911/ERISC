//
//  pro_initialize.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_initialize.hpp"
#include "pro_header.hpp"
#include <iostream>
#include <cstring>

using namespace std;

//将所有变量置初值
void initialize()
{
    for(int i=0;i<32;i++)
    {   register_[i]=0;
        register_w[i]=false;
        register_r[i]=false;
    }
    for(int i=0;i<16;i++)
        memory_c[i]=false;
    for(int i=0;i<1048576;i++)
    {
        memory[i]=0;
        stack_[i]=0;
        
    }
    stack_c=false;
    pointer=1048576 + 1;
    current_line=0;
    sumRIDs=0;
    total_line=0;
    cnt_draw = 0;
}

//将绘图所需全局变量记初值
void initialize_draw()
{
    for(int i=0;i<32;i++)
    {
        register_w[i]=false;
        register_r[i]=false;
    }
    for(int i=0;i<16;i++)
        memory_c[i]=false;
    stack_c=false;
}

//查找行标识
void find_RIDs()
{
    for(int i=0;i<total_line;i++)
    {
        int length=(int)strlen(instruction[i]);
        if(instruction[i][length-1]==':')
        {
            RIDs[sumRIDs].row=i;
            strcpy(RIDs[sumRIDs].inst,instruction[i]);
            RIDs[sumRIDs].inst[length-1]='\0';
            sumRIDs++;
        }
    }
    /*
    for(int i = 0; i < sumRIDs; i++)
        cout << "%" << RIDs[i].inst << " " << RIDs[i].row << endl;*/
}
