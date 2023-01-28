#include <stdio.h>

int main(void)
{
    int num = 0;
    printf("In: ");
    scanf("%i", &num);
    getc(stdin);

    printf("Out: ");
    char ret[36];
    ret[35] = '\0';
    for (int i = 1; i < 36; i++)
    {
        if(i % 9)
        {
            ret[35 - i] = (num & 1) + 48;
            num >>= 1;
        }
        else
        {
            ret[35 - i] = ' ';
        }
    }
    printf("%s\n", ret);
  
    return 0;
}