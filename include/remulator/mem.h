#pragma once
#include<stdint.h>
#define MAX_PAGE_NUM 0xC0000
#define PAGE_SIZE_LOG 0xC

void mem_cleanup();

uint8_t mem_read8(uint32_t addr);
uint16_t mem_read16(uint32_t addr);
uint32_t mem_read32(uint32_t addr);

void mem_write8(uint32_t addr, uint8_t val);
void mem_write16(uint32_t addr, uint16_t val);
void mem_write32(uint32_t addr, uint32_t val);