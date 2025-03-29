#include "riscv_csr_encoding.h"
#include "ipic.h"
#include "uart.h"

#define XCAUSE_XINHV        0x40000000
#define XCAUSE_XPP          0x30000000
#define XCAUSE_XPIE         0x08000000
#define XCAUSE_XPIL         0x00ff0000

#define CHECK_XLEN li a0, 1; slli a0, a0, 31; bltz a0, 1f; RVTEST_PASS; 1:

#define RVTEST_PASS                                                     \
        fence;                                                          \
        li TESTNUM, 1;                                                  \
        li a7, 0x10000;                                                 \
        li a0, 0;                                                       \
        ecall

#define TESTNUM gp

#define RVTEST_FAIL                                                     \
        fence;                                                          \
1:      beqz TESTNUM, 1b;                                               \
        sll TESTNUM, TESTNUM, 1;                                        \
        or TESTNUM, TESTNUM, 1;                                         \
        li a7, 0x10000;                                                 \
        addi a0, TESTNUM, 0;                                            \
        ecall

#define TEST_PASSFAIL \
        bne x0, TESTNUM, pass; \
fail: \
        RVTEST_FAIL; \
pass: \
        RVTEST_PASS \

#define STRING_MEM(name, str) .align 4; name: .string str; .word 0;

#define UART_DEBUG_MSG(message_addr)    \
    li t4, SC1F_UART0_PORT;             \
    la t0, message_addr;                \
1:                                      \
    li t5, SC1F_UART_ST_TRDY;           \
    lw t1, SC1F_UART_STATUS(t4);        \
    and t1, t1, t5;                     \
    beqz t1, 1b;                        \
                                        \
    lbu t5, 0(t0);                      \
    beqz t5, 1f;                        \
    sb t5, SC1F_UART_TXD(t4);           \
    addi t0, t0, 1;                     \
    j 1b;                               \
1:

#define RVTEST_CODE_BEGIN                                               \
.section .text.init;                                                    \
.align  4;                                                              \
.weak mtvec_handler;                                                    \
.globl _start;                                                          \
_start:                                                                 \
    li x1, 0;                                                           \
    li x2, 0;                                                           \
    li x3, 0;                                                           \
    li x4, 0;                                                           \
    li x5, 0;                                                           \
    li x6, 0;                                                           \
    li x7, 0;                                                           \
    li x8, 0;                                                           \
    li x9, 0;                                                           \
    li x10, 0;                                                          \
    li x11, 0;                                                          \
    li x12, 0;                                                          \
    li x13, 0;                                                          \
    li x14, 0;                                                          \
    li x15, 0;                                                          \
    li x16, 0;                                                          \
    li x17, 0;                                                          \
    li x18, 0;                                                          \
    li x19, 0;                                                          \
    li x20, 0;                                                          \
    li x21, 0;                                                          \
    li x22, 0;                                                          \
    li x23, 0;                                                          \
    li x24, 0;                                                          \
    li x25, 0;                                                          \
    li x26, 0;                                                          \
    li x27, 0;                                                          \
    li x28, 0;                                                          \
    li x29, 0;                                                          \
    li x30, 0;                                                          \
    li x31, 0;                                                          \
                                                                        \
    j reset_vector;                                                     \
.align 4;                                                               \
trap_vector:                                                            \
    csrr s0, IPIC_IPR;                                                  \
                                                                        \
    li t5, 0x10000;                                                     \
    bne a7, t5, 1f;                                                     \
                                                                        \
    csrr t5, mcause;                                                    \
                                                                        \
    li t6, ~(XCAUSE_XINHV | XCAUSE_XPP | XCAUSE_XPIE | XCAUSE_XPIL);    \
    and t5, t5, t6;                                                     \
    li t6, CAUSE_USER_ECALL;                                            \
    beq t5, t6, exit_prepare;                                           \
    li t6, CAUSE_SUPERVISOR_ECALL;                                      \
    beq t5, t6, exit_prepare;                                           \
    li t6, CAUSE_MACHINE_ECALL;                                         \
    beq t5, t6, exit_prepare;                                           \
1:                                                                      \
                                                                        \
trap_skip_ecall:                                                        \
    la t5, mtvec_handler;                                               \
    beqz t5, 1f;                                                        \
    jr t5;                                                              \
    /* was it an interrupt or an exception? */                          \
1:  csrr t5, mcause;                                                    \
    bgez t5, handle_exception;                                          \
                                                                        \
    j other_exception;                                                  \
                                                                        \
handle_exception:                                                       \
    /* we don't know how to handle whatever the exception was */        \
other_exception:                                                        \
    /* some unhandlable exception occurred, send non-zero code */       \
1:  li t1, 0x10000000;                                                  \
    or TESTNUM, TESTNUM, t1;                                            \
exit_prepare:                                                           \
    li t0, 1;                                                           \
    bne TESTNUM, t0, transmit_fail;                                     \
    UART_DEBUG_MSG(exit_pass)                                           \
    li t0, 0;                                                           \
    j test_exit;                                                        \
transmit_fail:                                                          \
    UART_DEBUG_MSG(exit_fail)                                           \
    mv t0, gp;                                                          \
    j test_exit;                                                        \
test_exit:                                                              \
    j .;                                                                \
                                                                        \
.align 4;                                                               \
reset_vector:                                                           \
                                                                        \
    li gp, 0;                                                           \
    la t0, trap_vector;                                                 \
    csrw mtvec, t0;                                                     \
    CHECK_XLEN                                                          \
                                                                        \
ipic_init:                                                              \
                                                                        \
    li s0, MIP_MEIP;                                                    \
    csrw mie, s0;                                                       \
    csrsi mstatus, MSTATUS_MIE;                                         \
                                                                        \
    csrw IPIC_IDX, 0;                                                   \
                                                                        \
    csrwi IPIC_ICSR, (IPIC_IRQ_ENABLE | IPIC_IRQ_LEVEL);                \
    csrr t0, IPIC_ICSR;                                                 \
                                                                        \
uart_init:                                                              \
                                                                        \
    /* Init UART to recieve code */                                     \
    li s0, SC1F_UART0_PORT;                                             \
                                                                        \
    /* Enable access to divisor */                                      \
    li t0, SC1F_UART_LCR_DIVL;                                          \
    sw t0, SC1F_UART_CONTROL(s0);                                       \
                                                                        \
    /* Setup clock divisor */                                           \
    li s1, UART_115200_CLK_DIVISOR;                                     \
                                                                        \
    sw s1, SC1F_UART_DIV_LO(s0);                                        \
    sw zero, SC1F_UART_DIV_HI(s0);                                      \
                                                                        \
    /* Setup line control register */                                   \
    li t0, SC1F_UART_LCR_CL8;                                           \
    sw t0, SC1F_UART_CONTROL(s0);                                       \
                                                                        \
    /* Enable FIFO */                                                   \
    li t0, SC1F_UART_FCR_RT_1 | SC1F_UART_FCR_EN | SC1F_UART_FCR_R_RST | SC1F_UART_FCR_T_RST;\
    sw t0, SC1F_UART_FCR(s0);                                           \
                                                                        \
    li t0, 0x1;                                                         \
    sw t0, SC1F_UART_IER(s0);                                           \
                                                                        \
    li a0, MSTATUS_MPIE;                                                \
    csrs mstatus, a0;                                                   \
    li sp, 3;                                                           \
                                                                        \
    la t0, 1f;                                                          \
    csrw mepc, t0;                                                      \
    mret;                                                               \
1:                                                                      \
    .align 4;                                                           \
    j 1f;                                                               \
    .section ".text"; .align 4; 1:                                      \


#define RVTEST_CODE_END .align 4; unimp

#define EXTRA_DATA

#define RVTEST_DATA_BEGIN                                               \
    .align 4; .section ".data";                                         \
    EXTRA_DATA                                                          \
    STRING_MEM(exit_pass, "Test is finished. Exit code: PASS\n")        \
    STRING_MEM(exit_fail, "Test is finished. Exit code: FAIL\n")        \
    .align 4; .global begin_signature; begin_signature:

#define RVTEST_DATA_END .align 4; .global end_signature; end_signature:

