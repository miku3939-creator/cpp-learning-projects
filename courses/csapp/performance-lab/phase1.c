/*#include "student_memset.h"*/
#include <stdio.h>
#define WORD_SIZE sizeof(unsigned long)
extern void byte_write(unsigned char *addr, unsigned char val);
extern void word_write(unsigned long *addr, unsigned long val);

/* Basic implementation of memset */
void *basic_memset(void *s, int c, size_t n)
{
    size_t cnt = 0;
    unsigned char *schar = s;
    while (cnt < n)
    {
        *schar++ = (unsigned char)c;
        cnt++;
    }
    return s;
}

void advanced_memset(void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;
    unsigned char ch = (unsigned char)c;

    uintptr_t addr = (uintptr_t)p;
    size_t size = sizeof(unsigned long);
    size_t over = addr % size;
    size_t i = 0;
    if (over != 0)
    {
        size_t shor = size - over;
        if (n < shor)
        {
            for (i = 0; i < n; i++)
            {
                byte_write(p, ch);
                p++;
            }
            return;
        }
        for (i = 0; i < shor; i++)
        {
            byte_write(p, ch);
            p++;
        }
        n -= shor;
    }

    size_t n1 = n / size;
    size_t n2 = n % size;

    if (n1 != 0)
    {
        unsigned long val = 0;
        for (i = 0; i < size; i++)
        {
            val = (val << 8) | ch;
        }
        unsigned long *q = (unsigned long *)p;

        for (i = 0; i < n1; i++)
        {
            word_write(q, val);
            q++;
        }
        p = (unsigned char *)q;
    }

    if (n2 != 0)
    {
        for (i = 0; i < n2; i++)
        {
            byte_write(p, ch);
            p++;
        }
    }
}
