#include <stdio.h>
#include <string.h>

struct my_struct {
        int b;
        char c[10];
        char d[25];
};

int foo(int a, struct my_struct *s, char *b, short *c, double d) {
        printf("Orig: %s\n", s->c);
        strcpy(s->c, "hello");
        return a + s->b;
}


int main() {
	short c = 325;
        struct my_struct s;
        s.b = 10; 
        strcpy(s.c, "yes!");
        int res = foo(15,&s, "no!", &c, 20.5); 
        printf("After: %s\n", s.c);
        printf("%d\n", res);
}
