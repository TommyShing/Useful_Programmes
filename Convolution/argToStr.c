#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    //argv -> str
    int len = 0;
    for (int i = 0, counter = 0; i < argc; i++)
    {
        while (argv[i][counter] != '\0')
        {
            counter++;
        }
        len += counter;
        counter = 0;
    }
    char *param = malloc((len + 1) * sizeof(char));
    if (param == NULL)
    {
        printf("No enough space");
        return 1;
    }
    param[len] = '\0';
    
    len = 0;
    for (int i = 0, counter = 0; i < argc; i++)
    {
        while (argv[i][counter] != '\0')
        {
            param[len++] = argv[i][counter];
            counter++;
        }
        counter = 0;
    }
    printf("%s\n", param);
    free(param);
    return 0;
}
