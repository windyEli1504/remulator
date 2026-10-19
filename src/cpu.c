#include<stdint.h>
#include<remulator/cpu.h>
#include<remulator/bus.h>

void cpu_init(rv32i_proc *cptr) {
    cptr->pc = 0x0; // replace this with starting address upon boot later
    cptr->x[0] = 0x0;
}

void fetch(rv32i_proc *cptr) {
    cptr->instr = fetch32(cptr->pc);
}

void r_type(rv32i_proc *cptr) {
    uint8_t rd = (cptr->instr >> 7) & 0x1F;
    uint8_t func3 = (cptr->instr >> 12) & 0x7;
    uint8_t rs1 = (cptr->instr >> 15) & 0x1F;
    uint8_t rs2 = (cptr->instr >> 20) & 0x1F;
    uint8_t func7 = cptr->instr >> 25;

    if(func7 == 0x20) {
        if(func3 == 0x0) cptr->x[rd] = cptr->x[rs1]-cptr->x[rs2];
        else if(func3 == 0x5) cptr->x[rd] = (int32_t)cptr->x[rs1] >> (cptr->x[rs2] & 0x1F);
    } else {
        switch(func3) {
            case 0x0: cptr->x[rd] = cptr->x[rs1]+cptr->x[rs2]; break;
            case 0x1: cptr->x[rd] = cptr->x[rs1] << (cptr->x[rs2] & 0x1F); break;
            case 0x2: cptr->x[rd] = (int32_t)cptr->x[rs1] < (int32_t)cptr->x[rs2]; break;
            case 0x3: cptr->x[rd] = cptr->x[rs1] < cptr->x[rs2]; break;
            case 0x4: cptr->x[rd] = cptr->x[rs1] ^ cptr->x[rs2]; break;
            case 0x5: cptr->x[rd] = cptr->x[rs1] >> (cptr->x[rs2] & 0x1F); break;
            case 0x6: cptr->x[rd] = cptr->x[rs1] | cptr->x[rs2]; break;
            case 0x7: cptr->x[rd] = cptr->x[rs1] & cptr->x[rs2]; break;
            default: break;
        }
    }
}

void i_type(rv32i_proc *cptr) {
    uint8_t rd = (cptr->instr >> 7) & 0x1F;
    uint8_t func3 = (cptr->instr >> 12) & 0x7;
    uint8_t rs1 = (cptr->instr >> 15) & 0x1F;
    uint16_t imm = cptr->instr >> 20;
    switch(func3) {
        case 0x0: cptr->x[rd] = cptr->x[rs1]+imm; break;
        
    }
}

void s_type(rv32i_proc *cptr) {
    uint32_t imm = (cptr->instr >> 7 & 0x1F)+(((int32_t)cptr->instr >> 25) << 5);
    uint8_t funct3 = cptr->instr >> 12 & 0x7;
    uint8_t rs1 = cptr->instr >> 15 & 0x1F;
    uint8_t rs2 = cptr->instr >> 20 & 0x1F;
    switch(funct3) {
        case 0x0: write8(cptr->x[rs1]+imm, cptr->x[rs2]); break;
        case 0x1: write16(cptr->x[rs1]+imm, cptr->x[rs2]); break;
        case 0x2: write32(cptr->x[rs1]+imm, cptr->x[rs2]); break;
        default: break;
    }
}

void j_type(rv32i_proc *cptr);

void dispatch(rv32i_proc *cptr) {
    uint8_t opcode = cptr->instr & 0x7F;
    switch(opcode) {
        case 0x33: r_type(cptr); break;
        case 0x3: i_type(cptr); break;
        case 0x23: s_type(cptr); break;
        case 0x6F: j_type(cptr); break;
        default: break;
    }
}
