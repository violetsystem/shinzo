#ifndef ARCH_X86_64_LOAD_H
#define ARCH_X86_64_LOAD_H

#include <arch/x86_64/boot/limine/limine.h>

typedef struct{
    int smp;
    int vmm;
    int pmm;
    int simd;
    int idt;
    int gdt;
    int apic;
    int arch_log;
}load_info_t;

#endif
