#include<stdlib.h>
#include<stdint.h>
#include<remulator/mem.h>
#define MAX_PAGE_NUM 786432
#define PAGE_SIZE_LOG 12

uint8_t * memory[MAX_PAGE_NUM] = {};

uint32_t page_handler(uint32_t addr) {
    uint32_t page_id = addr >> PAGE_SIZE_LOG;
    if(memory[page_id] == NULL) memory[page_id] = (uint8_t*)malloc(1 << PAGE_SIZE_LOG);
    return page_id;
}

void mem_cleanup() {
    for(int i = 0; i < MAX_PAGE_NUM; i++) {
        if(memory[i] != NULL) {
            free(memory[i]);
            memory[i] = NULL;
        }
    }
}

uint8_t fetch8(uint32_t addr) {
    uint32_t curr_page = page_handler(addr);
    uint32_t page_offset = addr & 0xFFF;
    return *(memory[curr_page]+page_offset);
}

uint16_t fetch16(uint32_t addr) {
    uint16_t res = fetch8(addr) + (fetch8(addr+1) << 8);
    return res;
}

uint32_t fetch32(uint32_t addr) {
    uint32_t res = fetch16(addr) + (fetch16(addr+2) << 16);
    return res;
}

void write8(uint32_t addr, uint8_t val) {
    uint32_t curr_page = page_handler(addr);
    uint32_t page_offset = addr & 0xFFF;
    *(memory[curr_page]+page_offset) = val;
}

void write16(uint32_t addr, uint16_t val) {
    write8(addr, (uint8_t)val);
    write8(addr+1, (uint8_t)(val >> 8));
}

void write32(uint32_t addr, uint32_t val) {
    write16(addr, (uint16_t)val);
    write16(addr+2, (uint16_t)(val >> 16));
}