##############################################################################
#
# Asm UART test
#
# @author Kirill Zhernov

##############################################################################

#include "../../common_macro/riscv_csr_encoding.h"
#include "../../common_macro/ipic.h"
#include "../../common_macro/uart.h"
#include "../../common_macro/riscv_test.h"

#define ADD_TEST(testnum, val_1, val_2, result) \
test_ ##testnum:                                \
    li TESTNUM, testnum;                        \
    li t0, val_1;                               \
    li t1, val_2;                               \
    add s0, t0, t1;                             \
    li s1, result;                              \
    bne s0, s1, fail;

#define ADDI_TEST(testnum, val_1, val_2, result)    \
test_ ##testnum:                                    \
    li TESTNUM, testnum;                            \
    li t0, val_1;                                   \
    addi s0, t0, val_2;                             \
    li s1, result;                                  \
    bne s0, s1, fail;

RVTEST_CODE_BEGIN

ADD_TEST(2, 1, 2, 3)
ADD_TEST(3, 0x123456, -0x123456, 0)
ADD_TEST(4, -0x123456, 0x123456, 0)
ADD_TEST(5, -0x123456, -0x123456, (-0x123456 - 0x123456))
ADD_TEST(6, 0xdeadbeef, 0xbeefdead, (0xdeadbeef + 0xbeefdead))
ADD_TEST(7, 0, -1, -1)
ADD_TEST(9, 0x7fffffff, 1, 0x80000000)

ADDI_TEST(10, 1, 2, 3)
ADDI_TEST(11, 0x7fffffff, 1, 0x80000000)
ADDI_TEST(12, (1 << 12) - 1, 1, 0x1000)
ADDI_TEST(13, 0, -1, -1)
ADDI_TEST(14, 0xdeadbeef, 0xff, 0xdeadbfee)
ADDI_TEST(15, -0x123456, -0x123, -0x123579)
ADDI_TEST(16, -0x123, 0x123, 0)

TEST_PASSFAIL

RVTEST_CODE_END

RVTEST_DATA_BEGIN

RVTEST_DATA_END
