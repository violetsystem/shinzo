#include <arch/x86_64/boot/boot.h>

load_info_t load_info;

void boot(void){
    arch_log_init();
    arch_log_print("boot : finish");
    
    while(1){
        __asm__("hlt");
    }
}
