//
//  pro_control.hpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright © 2020 Hanna Wang. All rights reserved.
//

#ifndef pro_control_hpp
#define pro_control_hpp

#include <stdio.h>

void divide_char_regs(int line);
void divide_char_RIDs(int line);
int find_line_RIDs(int line);

void ins_jal(int);
void ins_beq(int);
void ins_bne(int);
void ins_blt(int);
void ins_bge(int);
void ins_call(int);

#endif /* pro_control_hpp */
