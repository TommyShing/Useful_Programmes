#include <stdio.h>

int main(void)
{
    int result;
    printf("Type 0 to exit\n");
    do
    {
        result = func();
    }
    while (result == 0);
    printf("Exiting...\n");
    return 0;
}
