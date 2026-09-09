#include<remulator/mem.h>
#include<remulator/bus.h>
#include<stdint.h>

const uint32_t MMIO_BASE_ADDR = MAX_PAGE_NUM * (1U << PAGE_SIZE_LOG);
const uint32_t MAX_ADDR = ((uint64_t)1U << 32) - 1;

uint8_t fetch8(uint32_t addr) {
    if(addr > MAX_ADDR) {
        // Exception handler
    } else if(addr >= MMIO_BASE_ADDR) {
        //Compare addr against mmio define ranges to determine io to specific devices.
    }
    return mem_read8(addr);
}

uint16_t fetch16(uint32_t addr) {
    if(addr+1 > MAX_ADDR || addr+1 >= MMIO_BASE_ADDR) {
        // Exception Handler
    } else if(addr >= MMIO_BASE_ADDR) {
        // MMIO mapping
    }
    return mem_read16(addr);
}

uint32_t fetch32(uint32_t addr) {
    if(addr+3 > MAX_ADDR || addr+3 >= MMIO_BASE_ADDR) {
        
    } else if(addr >= MMIO_BASE_ADDR) {

    }
    return mem_read32(addr);
}

void write8(uint32_t addr, uint8_t val) {
    if(addr > MAX_ADDR) {

    } else if(addr >= MMIO_BASE_ADDR) {

    }
    mem_write8(addr, val);
}

void write16(uint32_t addr, uint16_t val) {
    if(addr+1 > MAX_ADDR || addr+1 >= MMIO_BASE_ADDR) {

    } else if(addr >= MMIO_BASE_ADDR) {

    }
    mem_write16(addr, val);
}

void write32(uint32_t addr, uint32_t val) {
    if(addr+3 > MAX_ADDR || addr+3 >= MMIO_BASE_ADDR) {

    } else if(addr >= MMIO_BASE_ADDR) {

    }
    mem_write32(addr, val);
}

