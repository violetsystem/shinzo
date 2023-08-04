#ifndef MISC_LOCK_H
#define MISC_LOCK_H

#include <types/types.h>

typedef struct{
    // TODO
    uint8_t locker;
}lock_t;

void atomic_acquire(lock_t* lock);
void atomic_try_lock(lock_t* lock);
void atomic_release(lock_t* lock);

#endif
