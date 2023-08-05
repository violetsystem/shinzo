#ifndef ARCH_X86_64_VMM_H
#define ARCH_X86_64_VMM_H

typedef void* vmm_space_t;
extern void* hhdm_address;
extern vmm_space_t kernel_space;

#include <pmm/pmm.h>
#include <libk/assert.h>
#include <types/types.h>
#include <memory/memory.h>
#include <arch/x86_64/asm.h>

#endif
