#include<stdlib.h>
#include<stdint.h>
#include<remulator/mem.h>

uint8_t * memory[MAX_PAGE_NUM] = {};

uint32_t page_handler(uint32_t addr) {
    uint32_t page_id = addr >> PAGE_SIZE_LOG;
    if(memory[page_id] == NULL) memory[page_id] = (uint8_t*)malloc(1 << PAGE_SIZE_LOG);
    return page_id;
}

void reclaim_page(uint32_t page_id) {
    if(memory[page_id] != NULL) free(memory[page_id]);
    memory[page_id] = NULL;
}

void mem_cleanup() {
    for(int i = 0; i < MAX_PAGE_NUM; i++) reclaim_page(i);
}

uint8_t mem_read8(uint32_t addr) {
    uint32_t curr_page = page_handler(addr);
    uint32_t page_offset = addr & 0xFFF;
    return *(memory[curr_page]+page_offset);
}

uint16_t mem_read16(uint32_t addr) {
    uint16_t res = mem_read8(addr) + (mem_read8(addr+1) << 8);
    return res;
}

uint32_t mem_read32(uint32_t addr) {
    uint32_t res = mem_read16(addr) + (mem_read16(addr+2) << 16);
    return res;
}

void mem_write8(uint32_t addr, uint8_t val) {
    uint32_t curr_page = page_handler(addr);
    uint32_t page_offset = addr & 0xFFF;
    *(memory[curr_page]+page_offset) = val;
}

void mem_write16(uint32_t addr, uint16_t val) {
    mem_write8(addr, (uint8_t)val);
    mem_write8(addr+1, (uint8_t)(val >> 8));
}

void mem_write32(uint32_t addr, uint32_t val) {
    mem_write16(addr, (uint16_t)val);
    mem_write16(addr+2, (uint16_t)(val >> 16));
}
