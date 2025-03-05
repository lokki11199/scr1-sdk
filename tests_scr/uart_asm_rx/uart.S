##############################################################################
#
# Asm UART test
#
# @author Kirill Zhernov

##############################################################################

#include "../common_macro/riscv_csr_encoding.h"
#include "../common_macro/ipic.h"
#include "../common_macro/uart.h"
#include "../common_macro/riscv_test.h"

RVTEST_CODE_BEGIN

test_2:

    li TESTNUM, 2

    wfi

test_3:

    li TESTNUM, 3

    // Compare recieved and reference strings
    la a0, compare_string
    la a1, save_str

    #####
1:
    lbu t0, 0(a0)
    lbu t1, 0(a0)

    bne t0, t1, fail

    // Update counters
    addi a0, a0, 1
    addi a1, a1, 1

    addi t2, a0, 1
    lbu t3, 0(t2)

    bnez t3, 1b     // Break if next byte is zero (end of string)
    #####

    j pass

.align 4;
mtvec_handler:

    csrr s1, mcause
    // Mask the mcause
    li t0, (1 << (__riscv_xlen - 1)) | 0xFFF
    and s1, s1, t0
    // Compare cause with external interrupt
    li t0, (1 << (__riscv_xlen - 1)) | IRQ_M_EXT
    bne s1, t0, fail

check_status:

    li s0, SC1F_UART0_PORT

    la a1, save_str

    li s3, 0
    li s9, 0
    li s8, 4

    la a0, compare_string

    lw s1, SC1F_UART_STATUS(s0)
    andi s1, s1, SC1F_UART_ST_RRDY
    li t0, SC1F_UART_ST_RRDY
    beq t0, s1, read_uart_rx

read_uart_rx:

    // Read symbol
    lbu s2, SC1F_UART_RXD(s0)

    slli t0, s9, 3  // t0 = s9 * 8 - Byte shift
    sll t2, s2, t0  // t2 = read_byte(s2) << t0
    or s3, s3, t2
    addi s9, s9, 1

    addi a0, a0, 1
    lbu t0, 0(a0)   // Break if next byte is 0
    beqz t0, complete_rx

    ### Store only whole all word
    bne s9, s8, 1f
    sw s3, 0(a1)

    addi a1, a1, 4

    mv s3, zero
    mv s9, zero
1:
    ###

    // Wait for FIFO to fill
status_read:
    lw s1, SC1F_UART_STATUS(s0)
    andi s1, s1, SC1F_UART_ST_RRDY
    li t0, SC1F_UART_ST_RRDY
    bne t0, s1, status_read
    // Continue to recieve data
    beq t0, s1, read_uart_rx

complete_rx:

    sw s3, 0(a1)    // Can contain data if not whole word was recieved and stored

    la t0, test_3
    csrw mepc, t0
    mret

TEST_PASSFAIL

RVTEST_CODE_END

RVTEST_DATA_BEGIN

STRING_MEM(compare_string, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!")
.align 4; save_str: .space 0x200

RVTEST_DATA_END
