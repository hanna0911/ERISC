//
//  pro_recognize.hpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright © 2020 Hanna Wang. All rights reserved.
//

#ifndef pro_recognize_hpp
#define pro_recognize_hpp

#include <stdio.h>

#include <string>
using namespace std;

string recg_instruct(int);
void recg_line(int);
bool recg_type(char a[]);
int recg_regs();
int power(int, int);
int recg_num(char a[]);

#endif /* pro_recognize_hpp */
