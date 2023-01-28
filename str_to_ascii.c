#include <stdio.h>
#include <stdlib.h>

char * char_to_ascii(char input, int op);

int main(void)
{
    int option = 1;
    printf("2 for hex, 1 for bin, 0 for dec: ");
    scanf("%i", &option);
    getc(stdin);

    printf("In: ");
    char input = getc(stdin);
    printf("Out: ");
    while (input != '\n')
    {
        char * str = char_to_ascii(input, option);
        if (str == NULL)
        {
            return 1;
        }
        printf("%s ", str);
        free(str);
        input = getc(stdin);
    }
    //getc in the end, so there is no need to getc again to skip the '\n'
    printf("\n");
    
    return 0;
}

char * char_to_ascii(char input, int op)
{
    int dec = (int) input;
    char * out = NULL;
    if (op)
    {
        if (op == 1)
        {
            out = malloc(sizeof(char) * 9);
            if (out == NULL)
            {
                return NULL;
            }
            out[8] = '\0';
            for (int i = 7; i >= 0; i--)
            {
                out[i] = (dec & 1) + 48;//00110000: 32+16
                dec >>= 1;
            }
        }
        else
        {
            out = malloc(sizeof(char) * 3);
            if (out == NULL)
            {
                return NULL;
            }
            out[2] = '\0';
            out[1] = (dec & 15) + 48;
            if (out[1] > 57)//ABCDEF
            {
                out[1] += 7;
            }
            dec >>= 4;
            out[0] = (dec & 15) + 48;
            if (out[0] > 57)
            {
                out[0] += 7;
            }
        }
    }
    else
    {
        out = malloc(sizeof(char) * 4);//dec < 128, 128 = 1 << 7
        if (out == NULL)
        {
            return NULL;
        }
        out[3] = '\0';
        out[2] = (dec % 10) + 48;
        dec /= 10;
        out[1] = (dec % 10) + 48;
        dec /= 10;
        out[0] = (dec % 10) + 48;
    }
    return out;
}