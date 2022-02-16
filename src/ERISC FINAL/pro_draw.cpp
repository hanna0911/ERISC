//
//  pro_draw.cpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright  2020 Hanna Wang. All rights reserved.
//

#include "pro_draw.hpp"
#include "pro_header.hpp"


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;


#pragma pack(2)

//bmp位图结构性格式要求
struct BM_Header
{
    unsigned char  bfType[2];
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
};

struct BM_Info
{
    unsigned int biSize;
    signed int biWidth;
    signed int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    signed int biXPelsPerMeter;
    signed int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
};

struct RGB_Pixel
{
    unsigned char B;
    unsigned char G;
    unsigned char R;
};

struct BM_Header BH;
struct BM_Info BI;
struct RGB_Pixel RGB;
int Width = 1000;
int Height = 300;
int BitDepth = 24;
short colortype[300][1000];
FILE* fout;

//置图片像素点颜色信息的初值
void ini_colortype(){
    for(int i = 0; i < 300; i++)
        for(int j = 0; j < 1000; j++)
            colortype[i][j] = 0;
}

//设置位图基本信息字段的数据
void init_BM_Header()
{
    BH.bfType[0] = 'B';
    BH.bfType[1] = 'M';
    BH.bfSize = Width * Height * (BitDepth / 8) + sizeof(BH) + sizeof(BI);
    BH.bfReserved1 = 0;
    BH.bfReserved2 = 0;
    BH.bfOffBits = sizeof(BH) + sizeof(BI);
}

void init_BM_Info()
{
    BI.biSize = sizeof(BI);
    BI.biWidth = Width;
    BI.biHeight = 0 - Height;
    BI.biPlanes = 1;
    BI.biBitCount = BitDepth;
    BI.biCompression = 0;
    BI.biSizeImage = Width * Height * (BitDepth / 8);
    BI.biXPelsPerMeter = 2834;
    BI.biYPelsPerMeter = 2834;
    BI.biClrUsed = 0;
    BI.biClrImportant = 0;
}

//判断每一个像素点的颜色
void setcolor(){
    //红、蓝、紫、绿、橙 = 1、2、3、4、5
    //判断每个寄存器的颜色
    for(int num = 0; num <= 31; num++){
        int row = (num / 8) + 1, column = (num % 8) + 1;
        if(register_w[num] == true && register_r[num] == false){
            for(int i = (row * 60) - 30; i <= (row * 60) + 30; i++)
                for(int j = (column * 60) - 10; j <= (column * 60) + 50; j++)
                    colortype[i][j] = 1;
        }
        else if(register_w[num] == false && register_r[num] == true){
            for(int i = (row * 60) - 30; i <= (row * 60) + 30; i++)
                for(int j = (column * 60) - 10; j <= (column * 60) + 50; j++)
                    colortype[i][j] = 2;
        }
        else if(register_w[num] == true && register_r[num] == true){
            for(int i = (row * 60) - 30; i <= (row * 60) + 30; i++)
                for(int j = (column * 60) - 10; j <= (column * 60) + 50; j++)
                    colortype[i][j] = 3;
        }
    }
    //判断内存单元的颜色
    for(int num = 0; num <= 15; num++){
        if(memory_c[num] == true){
            int row = (num / 4) + 1, column = (num % 4) + 1;
            for(int i = -30 + row * 60; i <= 30 + row * 60; i++)
                for(int j = 470 + column * 60; j <= 530 + column * 60; j++)
                    colortype[i][j] = 4;
        }
    }
    //判断栈空间的颜色
    if(stack_c == true){
        for(int i = 30; i <= 270; i++)
            for(int j = 770; j <= 950; j++)
                colortype[i][j] = 5;
    }
}

//确定生成文件的文件名
void setname(char* a){
    if(cnt_draw < 10){
        a[0] = char(cnt_draw + '0');
        a[1] = '\0';
    }
    else{
        a[0] = char((cnt_draw / 10) + '0');
        a[1] = char((cnt_draw % 10) + '0');
    }
    char prename[100] = "../output/";
    strcat(a, ".bmp");
    strcat(prename, a);
    strcpy(a, prename);
    return;
}

//
void ins_draw()
{
    if(cnt_draw >= 100 || cnt_draw <= 0){
        cout << "draw的调用次数超过规定" << endl;
        return;
    }
    setcolor();
    //设立bmp文件
    init_BM_Header();
    init_BM_Info();
    char a[10] = "";
    setname(a);
    fout = fopen(a, "wb+");
    fwrite(&BH, sizeof(BH), 1, fout);
    fwrite(&BI, sizeof(BI), 1, fout);
    for(int i = 0; i < Height; i++)
    {
        for(int j = 0; j < Width; j++)
        {
            //上色
            if(colortype[i][j] == 1){
                RGB.R = 255;
                RGB.G = 0;
                RGB.B = 0;
            }
            else if(colortype[i][j] == 2){
                RGB.R = 0;
                RGB.G = 0;
                RGB.B = 255;
            }
            else if(colortype[i][j] == 3){
                RGB.R = 255;
                RGB.G = 0;
                RGB.B = 255;
            }
            else if(colortype[i][j] == 4){
                RGB.R = 0;
                RGB.G = 255;
                RGB.B = 0;
            }
            else if(colortype[i][j] == 5){
                RGB.R = 255;
                RGB.G = 192;
                RGB.B = 0;
            }
            else{
                RGB.R = 255;
                RGB.G = 255;
                RGB.B = 255;
            }
            //制覆盖外框
            if(   ((i == 30 || i == 270) && j >= 50 && j <= 950)
               || ((i == 90 || i == 150 || i == 210) && j >= 50 && j <= 770)
               || ((((j - 50) % 60 == 0 && j <= 770) || j == 531 || j == 529 || j == 950 || j == 769 || j == 771) && i >= 30 && i <= 270)
               ){
                RGB.R = 0;
                RGB.G = 0;
                RGB.B = 0;
            }
            //输出本像素点到文件
            fwrite((void *)(&RGB), sizeof(RGB), 1, fout);
        }
    }
    fclose(fout);
    //绘制完成，置初值
    ini_colortype();
    initialize_draw();
    return;
}
