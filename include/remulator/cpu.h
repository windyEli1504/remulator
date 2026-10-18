#pragma once
#include<stdint.h>

typedef struct {
    uint32_t x[31], pc, instr;
} rv32i_proc;

void cpu_init(rv32i_proc *cptr);
void fetch(rv32i_proc *cptr);
void dispatch(rv32i_proc *cptr);
