struct my_struct {
        int b;
        char c[10];
        char d[25];
};

typedef struct student
{
  char name[50];
  char branch[50];
  int ID_no;
} student;

union Data {
   int i;
   float f;
   char str[20];
};

double func(int a, double b);

double foo(int a, long double b, student *s, union Data* data);

int bar(int c);

int *foo2(int a, struct my_struct *s, char *b, double (*func)(int, double));
