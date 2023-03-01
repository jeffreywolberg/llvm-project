#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hello.h"

#define typename(x) _Generic((x),                                                 \
            _Bool: "_Bool",                  unsigned char: "unsigned char",          \
             char: "char",                     signed char: "signed char",            \
        short int: "short int",         unsigned short int: "unsigned short int",     \
              int: "int",                     unsigned int: "unsigned int",           \
         long int: "long int",           unsigned long int: "unsigned long int",      \
    long long int: "long long int", unsigned long long int: "unsigned long long int", \
            float: "float",                         double: "double",                 \
      long double: "long double",                   char *: "pointer to char",        \
  unsigned char *: "pointer to uchar", \
           void *: "pointer to void",                int *: "pointer to int",         \
           struct my_struct *: "pointer to my_struct", \
          default: "other")

double func(int a, double b) {
	return a + b * a;
}

static inline double foo(int a, double b, student *s, union Data *data) {
	return a + b * a;
}

int bar(int c) {
	return 3 * c;
}

int *foo2(int a, struct my_struct *s, char *b, double (*func)(int, double)) {
        printf("Orig: %s\n", s->c);
        strcpy(s->c, "hello");
	int *res = malloc(sizeof(int));
	*res = a + s->b;
        return res;
}

int main() {
        student stud;
        union Data data;
	double result = foo(bar(2), 5, &stud, &data);
	printf("output: %f\n", result);
        
        short c = 120;
        struct my_struct s;
        unsigned char d[2];
        // unsigned char *e = d;
	printf("%s, %s, %s\n", typename(&s), typename(&c), typename(d));

        s.b = 10;
        strcpy(s.c, "yes!");
        int* res = foo2(15,&s, "no!", &func);
        printf("After: %s\n", s.c);
        printf("%d\n", *res);
	return 0;
}

