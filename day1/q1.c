#include<stdio.h>
void swap(char *a,char *b)
{
    char tmp=*a;
    *a=*b;
    *b=tmp;
}
int main(int arg, char *argv[])
{
    char a,b;
    a=*argv[1];
    b=*argv[2];
    printf("a= %c\nb= %c\n",a,b);
    swap(&a,&b);
    printf("\nAfter swapping...\na= %c\nb= %c",a,b);
}