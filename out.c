#include<stdio.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    char str1[] = "wocaonima ";
    char str2[20];
    strcpy(str2,str1);
    str1[2] = '2';
    str1[3] = '3';
    printf("%s %s\n",str1,str2);
    return 0;
}
