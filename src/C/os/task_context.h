#ifndef TASK_CONTEXT_H
#define TASK_CONTEXT_H

#include "config.h"

inline __attribute__((always_inline)) void move_sp(uint16_t addr)
{
        asm("out __SP_H__, %0" : : "r" ((uint8_t)(((addr & 0xFF00) >> 8))));
        asm("out __SP_L__, %0" : : "r" ((uint8_t)(addr & 0x00FF)));
}

inline __attribute__((always_inline)) uint16_t get_sp(void)
{
        uint16_t addr_h, addr_l;
        asm("in %0, __SP_H__" : "=&r" (addr_h));
        addr_h <<= 8;
        asm("in %0, __SP_L__" : "=&r" (addr_l));
        return addr_h | addr_l;
}

static inline __attribute__((always_inline)) void save_buffer(void)
{
        asm("sts %0, r0" : : "m" (buffer.regs[0]));
        asm("sts %0, r1" : : "m" (buffer.regs[1]));
        asm("sts %0, r2" : : "m" (buffer.regs[2]));
        asm("sts %0, r3" : : "m" (buffer.regs[3]));
        asm("sts %0, r4" : : "m" (buffer.regs[4]));
        asm("sts %0, r5" : : "m" (buffer.regs[5]));
        asm("sts %0, r6" : : "m" (buffer.regs[6]));
        asm("sts %0, r7" : : "m" (buffer.regs[7]));
        asm("sts %0, r8" : : "m" (buffer.regs[8]));
        asm("sts %0, r9" : : "m" (buffer.regs[9]));
        asm("sts %0, r10" : : "m" (buffer.regs[10]));
        asm("sts %0, r11" : : "m" (buffer.regs[11]));
        asm("sts %0, r12" : : "m" (buffer.regs[12]));
        asm("sts %0, r13" : : "m" (buffer.regs[13]));
        asm("sts %0, r14" : : "m" (buffer.regs[14]));
        asm("sts %0, r15" : : "m" (buffer.regs[15]));
        asm("sts %0, r16" : : "m" (buffer.regs[16]));
        asm("sts %0, r17" : : "m" (buffer.regs[17]));
        asm("sts %0, r18" : : "m" (buffer.regs[18]));
        asm("sts %0, r19" : : "m" (buffer.regs[19]));
        asm("sts %0, r20" : : "m" (buffer.regs[20]));
        asm("sts %0, r21" : : "m" (buffer.regs[21]));
        asm("sts %0, r22" : : "m" (buffer.regs[22]));
        asm("sts %0, r23" : : "m" (buffer.regs[23]));
        asm("sts %0, r24" : : "m" (buffer.regs[24]));
        asm("sts %0, r25" : : "m" (buffer.regs[25]));
        asm("sts %0, r26" : : "m" (buffer.regs[26]));
        asm("sts %0, r27" : : "m" (buffer.regs[27]));
        asm("sts %0, r28" : : "m" (buffer.regs[28]));
        asm("sts %0, r29" : : "m" (buffer.regs[29]));
        asm("sts %0, r30" : : "m" (buffer.regs[30]));
        asm("sts %0, r31" : : "m" (buffer.regs[31]));

        asm("in r0, __SREG__");
        asm("sts %0, r0" : : "m" (buffer.sreg));

        asm("pop r0");
        asm("sts %0, r0" : : "m" (pc_buffer.pc_h));
        asm("pop r0");
        asm("sts %0, r0" : : "m" (pc_buffer.pc_l));

        buffer.pc = (TPTR) ((((uint16_t) pc_buffer.pc_h) << 8) | pc_buffer.pc_l);
}

static inline __attribute__((always_inline)) void load_buffer(void)
{
        pc_buffer.pc_l = (uint8_t)((uint16_t)(buffer.pc) & 0xff);
        pc_buffer.pc_h = (uint8_t)(((uint16_t)(buffer.pc) & 0xff00) >> 8);

        asm("lds r0, %0" : : "m" (pc_buffer.pc_l));
        asm("push r0");
        asm("lds r0, %0" : : "m" (pc_buffer.pc_h));
        asm("push r0");

        asm("lds r0, %0" : : "m" (buffer.sreg));
        asm("out __SREG__, r0");
        
        asm("lds r0, %0" : : "m" (buffer.regs[0]));
        asm("lds r1, %0" : : "m" (buffer.regs[1]));
        asm("lds r2, %0" : : "m" (buffer.regs[2]));
        asm("lds r3, %0" : : "m" (buffer.regs[3]));
        asm("lds r4, %0" : : "m" (buffer.regs[4]));
        asm("lds r5, %0" : : "m" (buffer.regs[5]));
        asm("lds r6, %0" : : "m" (buffer.regs[6]));
        asm("lds r7, %0" : : "m" (buffer.regs[7]));
        asm("lds r8, %0" : : "m" (buffer.regs[8]));
        asm("lds r9, %0" : : "m" (buffer.regs[9]));
        asm("lds r10, %0" : : "m" (buffer.regs[10]));
        asm("lds r11, %0" : : "m" (buffer.regs[11]));
        asm("lds r12, %0" : : "m" (buffer.regs[12]));
        asm("lds r13, %0" : : "m" (buffer.regs[13]));
        asm("lds r14, %0" : : "m" (buffer.regs[14]));
        asm("lds r15, %0" : : "m" (buffer.regs[15]));
        asm("lds r16, %0" : : "m" (buffer.regs[16]));
        asm("lds r17, %0" : : "m" (buffer.regs[17]));
        asm("lds r18, %0" : : "m" (buffer.regs[18]));
        asm("lds r19, %0" : : "m" (buffer.regs[19]));
        asm("lds r20, %0" : : "m" (buffer.regs[20]));
        asm("lds r21, %0" : : "m" (buffer.regs[21]));
        asm("lds r22, %0" : : "m" (buffer.regs[22]));
        asm("lds r23, %0" : : "m" (buffer.regs[23]));
        asm("lds r24, %0" : : "m" (buffer.regs[24]));
        asm("lds r25, %0" : : "m" (buffer.regs[25]));
        asm("lds r26, %0" : : "m" (buffer.regs[26]));
        asm("lds r27, %0" : : "m" (buffer.regs[27]));
        asm("lds r28, %0" : : "m" (buffer.regs[28]));
        asm("lds r29, %0" : : "m" (buffer.regs[29]));
        asm("lds r30, %0" : : "m" (buffer.regs[30]));
        asm("lds r31, %0" : : "m" (buffer.regs[31]));
}

#endif