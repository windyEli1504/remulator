#pragma once
#include<stdint.h>

void mem_cleanup();

uint8_t fetch8(uint32_t addr);
uint16_t fetch16(uint32_t addr);
uint32_t fetch32(uint32_t addr);

void write8(uint32_t addr, uint8_t val);
void write16(uint32_t addr, uint16_t val);
void write32(uint32_t addr, uint32_t val);