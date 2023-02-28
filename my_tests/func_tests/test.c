#include <stdio.h>
#include <string.h>

struct my_struct {
        int b;
        char c[10];
        char d[25];
};

int foo(int a, struct my_struct str) {
	printf("Orig: %s\n", str.c);
	strcpy(str.c, "hello");
        return a + str.b;
}


int main() {
        struct my_struct s;
        s.b = 10; 
	strcpy(s.c, "yes!");
        int res = foo(15,s); 
	printf("After: %s\n", s.c);
        printf("%d\n", res);
}
