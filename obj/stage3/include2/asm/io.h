/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994, 1995 Waldorf GmbH
 * Copyright (C) 1994 - 2000 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2000 FSMLabs, Inc.
 */
#ifndef _ASM_IO_H
#define _ASM_IO_H

#include <linux/config.h>
#if 0
#include <linux/pagemap.h>
#endif
#include <asm/addrspace.h>
#include <asm/byteorder.h>
#ifdef CONFIG_ADDR_MAP
#include <addr_map.h>
#endif
#ifdef CONFIG_OCTEON
# include <asm/arch/cvmx.h>
# include <asm/arch/cvmx-access.h>
#if CONFIG_OCTEON_PCI_HOST
# include <asm/arch/octeon_pci.h>
#endif
#endif
/*
 * Slowdown I/O port space accesses for antique hardware.
 */
#undef CONF_SLOWDOWN_IO

#define __iomem
/*
 * Sane hardware offers swapping of I/O space accesses in hardware; less
 * sane hardware forces software to fiddle with this ...
 */
#if defined(CONFIG_SWAP_IO_SPACE) && defined(__MIPSEB__)

#define __ioswab8(x) (x)
#define __ioswab16(x) swab16(x)
#define __ioswab32(x) swab32(x)
#ifdef CONFIG_64BIT
#define __ioswab64(x) swab64(x)
#endif

#else

#define __ioswab8(x) (x)
#define __ioswab16(x) (x)
#define __ioswab32(x) (x)
#ifdef CONFIG_64BIT
#define __ioswab64(x) (x)
#endif

#endif

/*
 * This file contains the definitions for the MIPS counterpart of the
 * x86 in/out instructions. This heap of macros and C results in much
 * better code than the approach of doing it in plain C.  The macros
 * result in code that is to fast for certain hardware.  On the other
 * side the performance of the string functions should be improved for
 * sake of certain devices like EIDE disks that do highspeed polled I/O.
 *
 *   Ralf
 *
 * This file contains the definitions for the x86 IO instructions
 * inb/inw/inl/outb/outw/outl and the "string versions" of the same
 * (insb/insw/insl/outsb/outsw/outsl). You can also use "pausing"
 * versions of the single-IO instructions (inb_p/inw_p/..).
 *
 * This file is not meant to be obfuscating: it's just complicated
 * to (a) handle it all in a way that makes gcc able to optimize it
 * as well as possible and (b) trying to avoid writing the same thing
 * over and over again with slight variations and possibly making a
 * mistake somewhere.
 */

/*
 * On MIPS I/O ports are memory mapped, so we access them using normal
 * load/store instructions. mips_io_port_base is the virtual address to
 * which all ports are being mapped.  For sake of efficiency some code
 * assumes that this is an address that can be loaded with a single lui
 * instruction, so the lower 16 bits must be zero.  Should be true on
 * on any sane architecture; generic code does not use this assumption.
 */
extern const unsigned long mips_io_port_base;

/*
 * Gcc will generate code to load the value of mips_io_port_base after each
 * function call which may be fairly wasteful in some cases.  So we don't
 * play quite by the book.  We tell gcc mips_io_port_base is a long variable
 * which solves the code generation issue.  Now we need to violate the
 * aliasing rules a little to make initialization possible and finally we
 * will need the barrier() to fight side effects of the aliasing chat.
 * This trickery will eventually collapse under gcc's optimizer.  Oh well.
 */
static inline void set_io_port_base(unsigned long base)
{
	* (unsigned long *) &mips_io_port_base = base;
}

/*
 * Thanks to James van Artsdalen for a better timing-fix than
 * the two short jumps: using outb's to a nonexistent port seems
 * to guarantee better timings even on fast machines.
 *
 * On the other hand, I'd like to be sure of a non-existent port:
 * I feel a bit unsafe about using 0x80 (should be safe, though)
 *
 *		Linus
 *
 */

#define __SLOW_DOWN_IO \
	__asm__ __volatile__( \
		"sb\t$0,0x80(%0)" \
		: : "r" (mips_io_port_base));

#ifdef CONF_SLOWDOWN_IO
#ifdef REALLY_SLOW_IO
#define SLOW_DOWN_IO { __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; __SLOW_DOWN_IO; }
#else
#define SLOW_DOWN_IO __SLOW_DOWN_IO
#endif
#else
#define SLOW_DOWN_IO
#endif

/*
 * Change virtual addresses to physical addresses and vv.
 * These are trivial on the 1:1 Linux/MIPS mapping
 */
static inline phys_addr_t virt_to_phys(volatile void * address)
{
    /* Juniper, fix loader usb vitual address problem */
    if ((uint32_t)address >= 0x80000000 &&
            (uint32_t)address < 0xa0000000) {
        void *addr = (void *)address;
        return cvmx_ptr_to_phys(addr);
    }
	
#ifdef CONFIG_ADDR_MAP
	return addrmap_virt_to_phys((void *)address);
#else
#ifdef CONFIG_OCTEON
	void *addr = (void *)address;
	return cvmx_ptr_to_phys(addr);
#else
	return CPHYSADDR(address);
#endif
#endif
}

static inline void * phys_to_virt(phys_addr_t address)
{
#ifdef CONFIG_ADDR_MAP
	return (void *)addrmap_phys_to_virt(address);
#else
	return (void *)CKSEG0ADDR(address);
#endif
}

#if 0
/*
 * IO bus memory addresses are also 1:1 with the physical address
 */
extern inline unsigned long virt_to_bus(volatile void * address)
{
#ifndef CONFIG_64BIT
	return CPHYSADDR(address);
#else
	return XPHYSADDR(address);
#endif
}
#endif

extern inline void * bus_to_virt(unsigned long address)
{
#if !defined(CONFIG_64BIT)
	return (void *)KSEG0ADDR(address);
#elif defined(CONFIG_OCTEON)
	return (void *)((address & 0x1fffffff) | 0x80000000);
#else
	return (void *)CKSEG0ADDR(address);
#endif
}

/*
 * isa_slot_offset is the address where E(ISA) busaddress 0 is mapped
 * for the processor.
 */
extern unsigned long isa_slot_offset;

extern void * __ioremap(unsigned long offset, unsigned long size, unsigned long flags);

#if 0
extern inline void *ioremap(unsigned long offset, unsigned long size)
{
	return __ioremap(offset, size, _CACHE_UNCACHED);
}

extern inline void *ioremap_nocache(unsigned long offset, unsigned long size)
{
	return __ioremap(offset, size, _CACHE_UNCACHED);
}

extern void iounmap(void *addr);
#endif

#ifndef CONFIG_OCTEON
/*
 * XXX We need system specific versions of these to handle EISA address bits
 * 24-31 on SNI.
 * XXX more SNI hacks.
 */
#define readb(addr) (*(volatile unsigned char *)(addr))
#define readw(addr) __ioswab16((*(volatile unsigned short *)(addr)))
#define readl(addr) __ioswab32((*(volatile unsigned int *)(addr)))
#ifdef CONFIG_64BIT
#define readq(addr) __ioswab64((*(volatile unsigned long long *)(addr)))
#endif
#else
static inline unsigned char readb(volatile void *addr)
{
#ifdef CONFIG_PCI
	unsigned long vaddr = (unsigned long)addr;
	if ((vaddr >= OCTEON_PCI_SLOT0_BAR_ADDR) &&
	    (vaddr <= (OCTEON_PCI_SLOT0_BAR_ADDR + OCTEON_PCI_TOTAL_BAR_SIZE - 1)))
		return octeon_pci_mem1_readb(vaddr);
#endif
	__asm__ __volatile__ ( "syncw" );
	return (*(volatile unsigned char *)(addr));
}

static inline unsigned short readw(volatile void *addr)
{
#ifdef CONFIG_PCI
	unsigned long vaddr = (unsigned long)addr;
	if ((vaddr >= OCTEON_PCI_SLOT0_BAR_ADDR) &&
	    (vaddr <= (OCTEON_PCI_SLOT0_BAR_ADDR + OCTEON_PCI_TOTAL_BAR_SIZE - 1)))
		return octeon_pci_mem1_readw(vaddr);
#endif
	__asm__ __volatile__ ( "syncw" );
	return (*(volatile unsigned short *)(addr));
}

static inline unsigned int readl(volatile void *addr)
{
#ifdef CONFIG_PCI
	unsigned long vaddr = (unsigned long)addr;
	if ((vaddr >= OCTEON_PCI_SLOT0_BAR_ADDR) &&
	    (vaddr <= (OCTEON_PCI_SLOT0_BAR_ADDR + OCTEON_PCI_TOTAL_BAR_SIZE - 1)))
		return octeon_pci_mem1_readl(vaddr);
#endif
	__asm__ __volatile__ ( "syncw" );
	return (*(volatile unsigned int *)(addr));
}
#endif

#define __raw_readb readb
#define __raw_readw readw
#define __raw_readl readl
#ifdef CONFIG_64BIT
#define __raw_readq readq
#endif

#ifndef CONFIG_OCTEON
#define writeb(b,addr) (*(volatile unsigned char *)(addr)) = (b)
#define writew(b,addr) (*(volatile unsigned short *)(addr)) = (__ioswab16(b))
#define writel(b,addr) (*(volatile unsigned int *)(addr)) = (__ioswab32(b))
#ifdef CONFIG_64BIT
#define writeq(b,addr) (*(volatile unsigned long long *)(addr)) = (__ioswab64(b))
#endif
#else
static inline void writeb(u8 value, volatile void *addr)
{
#ifdef CONFIG_PCI
	u32 vaddr = (u32)addr;
	if ((vaddr >= OCTEON_PCI_SLOT0_BAR_ADDR) &&
	    (vaddr <= (OCTEON_PCI_SLOT0_BAR_ADDR + OCTEON_PCI_TOTAL_BAR_SIZE - 1)))
		    octeon_pci_mem1_writeb(value, vaddr);
	else
#endif
		(*(volatile unsigned char *)(addr)) = (value);
}

static inline void writew(u16 value, volatile void *addr)
{
#ifdef CONFIG_PCI
	u32 vaddr = (u32)addr;
	if ((vaddr >= OCTEON_PCI_SLOT0_BAR_ADDR) &&
	    (vaddr <= (OCTEON_PCI_SLOT0_BAR_ADDR + OCTEON_PCI_TOTAL_BAR_SIZE - 1)))
		    octeon_pci_mem1_writew(value, vaddr);
	else
#endif
		(*(volatile unsigned short *)(addr)) = (__ioswab16(value));
}

static inline void writel(u32 value, volatile void *addr)
{
#ifdef CONFIG_PCI
	u32 vaddr = (u32)addr;
	if ((vaddr >= OCTEON_PCI_SLOT0_BAR_ADDR) &&
	    (vaddr <= (OCTEON_PCI_SLOT0_BAR_ADDR + OCTEON_PCI_TOTAL_BAR_SIZE - 1)))
		    octeon_pci_mem1_writel(value, vaddr);
	else
#endif
		(*(volatile unsigned int *)(addr)) = (__ioswab32(value));
}

#endif

#define __raw_writeb writeb
#define __raw_writew writew
#define __raw_writel writel
#ifdef CONFIG_64BIT
#define __raw_writeq writeq
#endif

#define memset_io(a,b,c)	memset((void *)(a),(b),(c))
#define memcpy_fromio(a,b,c)	memcpy((a),(void *)(b),(c))
#define memcpy_toio(a,b,c)	memcpy((void *)(a),(b),(c))

/* END SNI HACKS ... */

/*
 * ISA space is 'always mapped' on currently supported MIPS systems, no need
 * to explicitly ioremap() it. The fact that the ISA IO space is mapped
 * to PAGE_OFFSET is pure coincidence - it does not mean ISA values
 * are physical addresses. The following constant pointer can be
 * used as the IO-area pointer (it can be iounmapped as well, so the
 * analogy with PCI is quite large):
 */
#define __ISA_IO_base ((char *)(PAGE_OFFSET))

#define isa_readb(a) readb(a)
#define isa_readw(a) readw(a)
#define isa_readl(a) readl(a)
#define isa_writeb(b,a) writeb(b,a)
#define isa_writew(w,a) writew(w,a)
#define isa_writel(l,a) writel(l,a)

#define isa_memset_io(a,b,c)     memset_io((a),(b),(c))
#define isa_memcpy_fromio(a,b,c) memcpy_fromio((a),(b),(c))
#define isa_memcpy_toio(a,b,c)   memcpy_toio((a),(b),(c))

/*
 * We don't have csum_partial_copy_fromio() yet, so we cheat here and
 * just copy it. The net code will then do the checksum later.
 */
#define eth_io_copy_and_sum(skb,src,len,unused) memcpy_fromio((skb)->data,(src),(len))
#define isa_eth_io_copy_and_sum(a,b,c,d) eth_copy_and_sum((a),(b),(c),(d))

static inline int check_signature(unsigned long io_addr,
				  const unsigned char *signature, int length)
{
	int retval = 0;
	do {
		if (readb((u32 *)io_addr) != *signature)
			goto out;
		io_addr++;
		signature++;
		length--;
	} while (length);
	retval = 1;
out:
	return retval;
}
#define isa_check_signature(io, s, l) check_signature(i,s,l)

/*
 * Talk about misusing macros..
 */

#define __OUT1(s) \
static inline void __out##s(unsigned int value, unsigned int port) {

#define __OUT2(m) \
__asm__ __volatile__ ("s" #m "\t%0,%1(%2)"

#define __OUT(m,s,w) \
__OUT1(s) __OUT2(m) : : "r" (__ioswab##w(value)), "i" (0), "r" (mips_io_port_base+port)); } \
__OUT1(s##c) __OUT2(m) : : "r" (__ioswab##w(value)), "ir" (port), "r" (mips_io_port_base)); } \
__OUT1(s##_p) __OUT2(m) : : "r" (__ioswab##w(value)), "i" (0), "r" (mips_io_port_base+port)); \
	SLOW_DOWN_IO; } \
__OUT1(s##c_p) __OUT2(m) : : "r" (__ioswab##w(value)), "ir" (port), "r" (mips_io_port_base)); \
	SLOW_DOWN_IO; }

#define __IN1(t,s) \
static inline t __in##s(unsigned int port) { t _v;

/*
 * Required nops will be inserted by the assembler
 */
#define __IN2(m) \
__asm__ __volatile__ ("l" #m "\t%0,%1(%2)"

#define __IN(t,m,s,w) \
__IN1(t,s) __IN2(m) : "=r" (_v) : "i" (0), "r" (mips_io_port_base+port)); return __ioswab##w(_v); } \
__IN1(t,s##c) __IN2(m) : "=r" (_v) : "ir" (port), "r" (mips_io_port_base)); return __ioswab##w(_v); } \
__IN1(t,s##_p) __IN2(m) : "=r" (_v) : "i" (0), "r" (mips_io_port_base+port)); SLOW_DOWN_IO; return __ioswab##w(_v); } \
__IN1(t,s##c_p) __IN2(m) : "=r" (_v) : "ir" (port), "r" (mips_io_port_base)); SLOW_DOWN_IO; return __ioswab##w(_v); }

#define __INS1(s) \
static inline void __ins##s(unsigned int port, void * addr, unsigned long count) {

#define __INS2(m) \
if (count) \
__asm__ __volatile__ ( \
	".set\tnoreorder\n\t" \
	".set\tnoat\n" \
	"1:\tl" #m "\t$1,%4(%5)\n\t" \
	"subu\t%1,1\n\t" \
	"s" #m "\t$1,(%0)\n\t" \
	"bne\t$0,%1,1b\n\t" \
	"addiu\t%0,%6\n\t" \
	".set\tat\n\t" \
	".set\treorder"

#define __INS(m,s,i) \
__INS1(s) __INS2(m) \
	: "=r" (addr), "=r" (count) \
	: "0" (addr), "1" (count), "i" (0), \
	  "r" (mips_io_port_base+port), "I" (i) \
	: "$1");} \
__INS1(s##c) __INS2(m) \
	: "=r" (addr), "=r" (count) \
	: "0" (addr), "1" (count), "ir" (port), \
	  "r" (mips_io_port_base), "I" (i) \
	: "$1");}

#define __OUTS1(s) \
static inline void __outs##s(unsigned int port, const void * addr, unsigned long count) {

#define __OUTS2(m) \
if (count) \
__asm__ __volatile__ ( \
	".set\tnoreorder\n\t" \
	".set\tnoat\n" \
	"1:\tl" #m "\t$1,(%0)\n\t" \
	"subu\t%1,1\n\t" \
	"s" #m "\t$1,%4(%5)\n\t" \
	"bne\t$0,%1,1b\n\t" \
	"addiu\t%0,%6\n\t" \
	".set\tat\n\t" \
	".set\treorder"

#define __OUTS(m,s,i) \
__OUTS1(s) __OUTS2(m) \
	: "=r" (addr), "=r" (count) \
	: "0" (addr), "1" (count), "i" (0), "r" (mips_io_port_base+port), "I" (i) \
	: "$1");} \
__OUTS1(s##c) __OUTS2(m) \
	: "=r" (addr), "=r" (count) \
	: "0" (addr), "1" (count), "ir" (port), "r" (mips_io_port_base), "I" (i) \
	: "$1");}

__IN(unsigned char,b,b,8)
__IN(unsigned short,h,w,16)
__IN(unsigned int,w,l,32)

__OUT(b,b,8)
__OUT(h,w,16)
__OUT(w,l,32)

__INS(b,b,1)
__INS(h,w,2)
__INS(w,l,4)

__OUTS(b,b,1)
__OUTS(h,w,2)
__OUTS(w,l,4)


/*
 * Note that due to the way __builtin_constant_p() works, you
 *  - can't use it inside an inline function (it will never be true)
 *  - you don't have to worry about side effects within the __builtin..
 */
#define outb(val,port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outbc((val),(port)) : \
	__outb((val),(port)))

#define inb(port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__inbc(port) : \
	__inb(port))

#define outb_p(val,port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outbc_p((val),(port)) : \
	__outb_p((val),(port)))

#define inb_p(port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__inbc_p(port) : \
	__inb_p(port))

#define outw(val,port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outwc((val),(port)) : \
	__outw((val),(port)))

#define inw(port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__inwc(port) : \
	__inw(port))

#define outw_p(val,port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outwc_p((val),(port)) : \
	__outw_p((val),(port)))

#define inw_p(port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__inwc_p(port) : \
	__inw_p(port))

#define outl(val,port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outlc((val),(port)) : \
	__outl((val),(port)))

#define inl(port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__inlc(port) : \
	__inl(port))

#define outl_p(val,port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outlc_p((val),(port)) : \
	__outl_p((val),(port)))

#define inl_p(port) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__inlc_p(port) : \
	__inl_p(port))


#define outsb(port,addr,count) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outsbc((port),(addr),(count)) : \
	__outsb ((port),(addr),(count)))

#define insb(port,addr,count) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__insbc((port),(addr),(count)) : \
	__insb((port),(addr),(count)))

#define outsw(port,addr,count) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outswc((port),(addr),(count)) : \
	__outsw ((port),(addr),(count)))

#define insw(port,addr,count) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__inswc((port),(addr),(count)) : \
	__insw((port),(addr),(count)))

#define outsl(port,addr,count) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__outslc((port),(addr),(count)) : \
	__outsl ((port),(addr),(count)))

#define insl(port,addr,count) \
((__builtin_constant_p((port)) && (port) < 32768) ? \
	__inslc((port),(addr),(count)) : \
	__insl((port),(addr),(count)))

#define IO_SPACE_LIMIT 0xffff

/*
 * The caches on some architectures aren't dma-coherent and have need to
 * handle this in software.  There are three types of operations that
 * can be applied to dma buffers.
 *
 *  - dma_cache_wback_inv(start, size) makes caches and coherent by
 *    writing the content of the caches back to memory, if necessary.
 *    The function also invalidates the affected part of the caches as
 *    necessary before DMA transfers from outside to memory.
 *  - dma_cache_wback(start, size) makes caches and coherent by
 *    writing the content of the caches back to memory, if necessary.
 *    The function also invalidates the affected part of the caches as
 *    necessary before DMA transfers from outside to memory.
 *  - dma_cache_inv(start, size) invalidates the affected parts of the
 *    caches.  Dirty lines of the caches may be written back or simply
 *    be discarded.  This operation is necessary before dma operations
 *    to the memory.
 */
extern void (*_dma_cache_wback_inv)(unsigned long start, unsigned long size);
extern void (*_dma_cache_wback)(unsigned long start, unsigned long size);
extern void (*_dma_cache_inv)(unsigned long start, unsigned long size);

#define dma_cache_wback_inv(start,size)	_dma_cache_wback_inv(start,size)
#define dma_cache_wback(start,size)	_dma_cache_wback(start,size)
#define dma_cache_inv(start,size)	_dma_cache_inv(start,size)

static inline void sync(void)
{
}

static inline void __syncw(void)
{
		__asm__ __volatile__(
			".set	push		\n"
			".set	noreorder	\n"
#ifndef CONFIG_OCTEON
			".set	mips2		\n"
			"syncw			\n"
#else
			".set	arch=octeon	\n"
			"syncw			\n"
# ifndef CONFIG_CAVIUM_OCTEON2	/* CN3XXX errata Core-401 */
			"syncw			\n"
# endif
#endif
			".set	pop		\n"
			: : : "memory"
		);
}

/*
 * 8, 16 and 32 bit, big and little endian I/O operations, with barrier.
 *
 */
static inline int in_8(const volatile unsigned char __iomem *addr)
{
	return *addr;
}

static inline void out_8(volatile unsigned char __iomem *addr, int val)
{
	__syncw();
	*addr = val;
	__syncw();
}

static inline int in_le16(const volatile unsigned short __iomem *addr)
{
	return le16_to_cpu(*addr);
}

static inline int in_be16(const volatile unsigned short __iomem *addr)
{
	return be16_to_cpu(*addr);
}

static inline void out_le16(volatile unsigned short __iomem *addr, int val)
{
	__syncw();
	*addr = cpu_to_le16(val);
	__syncw();
}

static inline void out_be16(volatile unsigned short __iomem *addr, int val)
{
	__syncw();
	*addr = cpu_to_be16(val);
	__syncw();
}

static inline unsigned in_le32(const volatile unsigned __iomem *addr)
{
	return le32_to_cpu(*addr);
}

static inline unsigned in_be32(const volatile unsigned __iomem *addr)
{
	return be32_to_cpu(*addr);
}

static inline void out_le32(volatile unsigned __iomem *addr, int val)
{
	__syncw();
	*addr = cpu_to_le32(val);
	__syncw();
}

static inline void out_be32(volatile unsigned __iomem *addr, int val)
{
	__syncw();
	*addr = cpu_to_be32(val);
	__syncw();
}
/*
 * Given a physical address and a length, return a virtual address
 * that can be used to access the memory range with the caching
 * properties specified by "flags".
 */
#define MAP_NOCACHE	(0)
#define MAP_WRCOMBINE	(0)
#define MAP_WRBACK	(0)
#define MAP_WRTHROUGH	(0)

static inline void *
map_physmem(phys_addr_t paddr, unsigned long len, unsigned long flags)
{
	/* NOTE: this is invalid for Octeon */
	return (void *)((u32)paddr);
}

/*
 * Take down a mapping set up by map_physmem().
 */
static inline void unmap_physmem(void *vaddr, unsigned long flags)
{

}

#endif /* _ASM_IO_H */
