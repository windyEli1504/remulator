#include<stdint.h>
#include<remulator/cpu.h>
#include<remulator/bus.h>

rv32i_proc cpu;

uint32_t instruction;

void fetch() {
    instruction = fetch32(cpu.pc);
}

void r_type() {
    uint8_t rd = (instruction >>= 7) & 0x1F;
    uint8_t func3 = (instruction >>= 5) & 0x7;
    uint8_t rs1 = (instruction >>= 3) & 0x1F;
    uint8_t rs2 = (instruction >>= 5) & 0x1F;
    uint8_t func7 = instruction >> 5; 

    if(func7 == 0x20) {
        if(func3 == 0x0) {
            cpu.x[rd] = cpu.x[rs1]-cpu.x[rs2];
        } else if(func3 == 0x5) {
            cpu.x[rd] = cpu.x[rs1] >> cpu.x[rs2];
            if(cpu.x[rs1] >> 31 == 1) {
                uint32_t upper_ones = 0xFFFFFFFF & (1 << (32-cpu.x[rs2]));
                cpu.x[rd] += upper_ones;
            }
        } else {
            // Error
        }
    } else {
        switch(func3) {
            case 0x0:
                cpu.x[rd] = cpu.x[rs1]+cpu.x[rs2];
                break;
            case 0x1:
                cpu.x[rd] = cpu.x[rs1] << cpu.x[rs2];
                break;
            case 0x2:
                cpu.x[rd] = (int32_t)cpu.x[rs1] < (int32_t)cpu.x[rs2];
                break;
            case 0x3:
                cpu.x[rd] = cpu.x[rs1] < cpu.x[rs2];
                break;
            case 0x4:
                cpu.x[rd] = cpu.x[rs1] ^ cpu.x[rs2];
                break;
            case 0x5:
                cpu.x[rd] = cpu.x[rs1] >> cpu.x[rs2];
                break;
            case 0x6:
                cpu.x[rd] = cpu.x[rs1] | cpu.x[rs2];
                break;
            case 0x7:
                cpu.x[rd] = cpu.x[rs1] & cpu.x[rs2];
                break;
            default:
                // Error
                break;
        }
    }
}

void dispatch() {
    uint8_t opcode = instruction & 0x7F;
    switch(opcode) {
        case 0x33:
            r_type();
            break;
        
    }
}
