#ifndef MISC_ASSERT_H
#define MISC_ASSERT_H

#include <types/types.h>

#define assert(exp) if(!(exp)) kernel_panic("Assertion failed: " #exp ", file " __FILE__);

#endif
