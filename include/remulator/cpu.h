#pragma once
#include<stdint.h>

typedef struct {
    uint32_t x[31];
    uint32_t pc;
} rv32i_proc;