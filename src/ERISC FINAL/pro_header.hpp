//
//  pro_header.hpp
//  ERISC 20201128
//
//  Created by Hanna Wang on 28/11/2020.
//  Copyright © 2020 Hanna Wang. All rights reserved.
//

#ifndef pro_header_hpp
#define pro_header_hpp

#include <stdio.h>
#include <string>

using namespace std;

//pro_memory
void ins_load(int);
void ins_store(int);

//pro_stack
void ins_push(int);
void stack_push(int);
void ins_pop(int);
int stack_pop();

//pro_register
void divide_char(int);
void ins_mov(int);
void ins_add(int);
void ins_sub(int);
void ins_mul(int);
void ins_div(int);
void ins_rem(int);
void ins_and(int);
void ins_or(int);

//pro_control
void divide_char_regs(int);
void divide_char_RIDs(int);
int find_line_RIDs(int);
void ins_jal(int);
void ins_beq(int);
void ins_bne(int);
void ins_blt(int);
void ins_bge(int);
void ins_call(int);

//pro_draw
void ini_colortype();
void ins_draw();
void init_BM_Header();
void init_BM_Info();
void setcolor();
void setname(char* a);

//pro_recognize
string recg_instruct(int);
void recg_line(int);
bool recg_type(char a[]);
int recg_regs(char a[]);
int power(int, int);
int recg_num(char a[]);

//pro_initialize
void initialize();
void initialize_draw();
void find_RIDs();

//pro_input
bool input();

//pro_output
void output();

//global variable
extern int register_[32];
extern bool register_r[32];
extern bool register_w[32];
extern bool memory_c[16];
extern int memory[1048576];
extern bool stack_c;
extern int stack_[1048576 + 1];
extern int pointer;
extern char instruction[200][50];
extern int current_line;
extern int sumRIDs;
extern int total_line;
extern int cnt_draw;

/*typedef*/ struct rids
{
    int row;
    char inst[50];
};
extern rids RIDs[200];


#endif /* pro_header_hpp */
