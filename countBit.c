#include <stdio.h>

int count(char * str);

int main(int argc, char * argv[])
{
    if (argc > 1)
    {
        printf("%i", count(argv[1]));
    }
}

int count(char * str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}