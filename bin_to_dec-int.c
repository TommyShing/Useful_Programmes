#include <stdio.h>
int main(void)
{
    printf("In: ");
    char input = getc(stdin);
    printf("Out: ");
  
    int ret = 0;
    while (input != '\n')
    {
        if (input == '1')
        {
            ret <<= 1;
            ret++;
        }
        else if (input == '0')
        {
            ret <<= 1;
        }
        input = getc(stdin);
    }
    printf("%i\n", ret);

    return 0;
}