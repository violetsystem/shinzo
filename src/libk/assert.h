#ifndef ASSERT_H
#define ASSERT_H

#include <types/types.h>

#define assert(exp) if(!(exp)) kernel_panic("Assertion failed: " #exp ", file " __FILE__);

#endif
