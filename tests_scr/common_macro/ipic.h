#ifndef IPIC_H
#define IPIC_H

// IPIC memory map
#define PLF_IPIC_MBASE (0xbf0)
#define IPIC_CISV  (PLF_IPIC_MBASE + 0)
#define IPIC_CICSR (PLF_IPIC_MBASE + 1)
#define IPIC_IPR   (PLF_IPIC_MBASE + 2)
#define IPIC_ISVR  (PLF_IPIC_MBASE + 3)
#define IPIC_EOI   (PLF_IPIC_MBASE + 4)
#define IPIC_SOI   (PLF_IPIC_MBASE + 5)
#define IPIC_IDX   (PLF_IPIC_MBASE + 6)
#define IPIC_ICSR  (PLF_IPIC_MBASE + 7)
#define IPIC_IER   (PLF_IPIC_MBASE + 8)
#define IPIC_IMAP  (PLF_IPIC_MBASE + 9)

// Status
#define IPIC_IRQ_PENDING       (1 << 0)
#define IPIC_IRQ_ENABLE        (1 << 1)
#define IPIC_IRQ_LEVEL         (0 << 2)
#define IPIC_IRQ_EDGE          (1 << 2)
#define IPIC_IRQ_INV           (1 << 3)
#define IPIC_IRQ_MODE_MASK     (3 << 2)
#define IPIC_IRQ_CLEAR_PENDING IPIC_IRQ_PENDING

// define IPIC_IRQ_IN_SERVICE (1 << 4) // RO
#define IPIC_IRQ_PRIV_MASK  (3 << 8)
#define IPIC_IRQ_PRIV_MMODE (3 << 8)
#define IPIC_IRQ_PRIV_SMODE (1 << 8)
#define IPIC_IRQ_LN_OFFS    (12)

#endif