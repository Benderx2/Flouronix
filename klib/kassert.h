#ifndef __KASSERT_H
#define __KASSERT_H
#include <kernel/console/console.h>
#include <arch/x86/x86.h>
#define kassert(exp) \
do { \
        if (!(exp)) { \
                Console.WriteLine("Assertion " #exp " failed at %s, line %d", __FILE__, __LINE__); \
                CPU_x86.halt(); \
        } \
} while (0)
#endif

