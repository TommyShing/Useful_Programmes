#include <stdio.h>
//指向指向指针的指针的指针
void pointer1(int num);
void pointer0(int num);

int main (void)
{
    int num = 0;
    printf("*数: ");
    scanf("%i", &num);
    getc(stdin);
    if (num == 0)
    {
        num = 33;
    }

    pointer0(num);
    printf("\n");
    pointer1(num);
    printf("\n");

    return 0;
}

void pointer0(int num)
{
    if (num == 1)
    {
        printf("指针");
    }
    else
    {
        printf("指向");
        pointer0(num - 1);
        printf("的指针");
    }
}

void pointer1(int num)
{
    num--;
    for (int i = 0; i < num; i++)
    {
        printf("指向");
    }
    printf("指针");
    for (int i = 0; i < num; i++)
    {
        printf("的指针");
    }
}
