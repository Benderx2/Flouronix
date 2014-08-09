#ifndef _K_STRING_H
#define _K_STRING_H
#define NULL 0
#include <klib/kbool.h>
typedef unsigned int size_t;
void* memcpy(void* s1, void* s2, size_t n);
void* memmove(void* s1, void* s2, size_t n);
char* strcpy(char* s1, char* s2);
char* strncpy(char* s1, char* s2, size_t n);
void* memset(void *s, int c, size_t n);
void reverse(char s[]);
void itoa (char *buf, int base, int d);
double atof(char* num);
char* ftoa(char *s, double n);
int strcmp (const char * s1, const char * s2);
int strncmp(const char* s1, const char* s2, size_t n);
#endif

