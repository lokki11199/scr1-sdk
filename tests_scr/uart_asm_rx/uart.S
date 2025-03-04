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
    UART_DEBUG_MSG(transmit)
    j .

RVTEST_CODE_END

RVTEST_PASS
RVTEST_FAIL

RVTEST_DATA_BEGIN

STRING_MEM(transmit, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~!\n")

RVTEST_DATA_END
