//
//  pro_input.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_input.hpp"
#include "pro_header.hpp"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

bool input()
{
    
    char name[100] = "";
    cout << "请输入文件名（包含后缀名）" << endl;
    cin >> name;
    char prename[100] = "../input/";
    strcat(prename, name);
	ifstream fin(prename);
    if(!fin)
    {
        cout<<"输入文件打开失败"<<endl;return false;
    }
    string temp="";
    //将读入的文件，依据换行符分割成不同指令
    while(getline(fin,temp))
    {
        
        char TargetFile[strlen(temp.c_str())];
        strcpy(TargetFile,temp.c_str());
        strcpy(instruction[total_line],TargetFile);
        total_line++;
        
    }
    fin.close();
    return true;
}
