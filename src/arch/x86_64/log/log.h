#ifndef ARCH_X86_64_LOG_H
#define ARCH_X86_64_LOG_H

#include <arch/x86_64/asm.h>
#include <arch/x86_64/boot/boot.h>

void arch_log_init(void);
void arch_log_put_char(char c);
void arch_log_print(const char* str);

#endif
