#include <stdio.h>
#include <string.h>

double foo(int a, double b) {
	return a + b * a;
}

int bar(int c) {
	return 3 * c;
}

struct my_struct {
        int b;
        char c[10];
        char d[25];
};

int foo2(int a, struct my_struct *s, char *b, short *c, double d) {
        printf("Orig: %s\n", s->c);
        strcpy(s->c, "hello");
        return a + s->b;
}

int main() {
	double result = foo(bar(2), 5);
	printf("output: %f\n", result);
        
        short c = 325;
        struct my_struct s;
        s.b = 10;
        strcpy(s.c, "yes!");
        int res = foo2(15,&s, "no!", &c, 20.5);
        printf("After: %s\n", s.c);
        printf("%d\n", res);
	return 0;
}

