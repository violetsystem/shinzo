#ifndef ARCH_X86_64_BOOT_H
#define ARCH_X86_64_BOOT_H

#include <arch/x86_64/load.h>

#define BOOT_STACK_SIZE 0x10000

extern load_info_t load_info;

void boot(void);

#endif
