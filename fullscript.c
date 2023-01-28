#include <stdio.h>
#include <stdlib.h>
//I think I should have written a .sh script

int bin_to_dec(void);
int countBit(void);
int dec_to_bin(void);
int str_to_ascii(void);

int main(void)
{
    int result;
    int input;

    char * list[] = {"exit", "bin_to_dec-int", "countBit", "dec_to_bin-int", "str_to_ascii"};
    int len = 5;

    while(1)
    {
        printf("\nTommy's Scripts\n\n");

        for (int i = 0; i < len; i++)
        {
            printf("%i. %s\n", i, list[i]);
        }
        printf("\nInput: ");

        scanf("%i", &input);
        getc(stdin);
        if (input)
        {
            switch (input)
            {
                case 1:
                    bin_to_dec();
                    break;
                case 2:
                    countBit();
                    break;
                case 3:
                    dec_to_bin();
                    break;
                case 4:
                    str_to_ascii();
                    break;
            }
        }
        else
        {
            printf("Exiting...\n");
            return 0;
        }
    }
}

int bin_to_dec(void)
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

int countBit(void)//Distinct from the original one
{
    printf("In: ");
    char input = getc(stdin);
    printf("Out: ");

    int count = 0;
    while (input != '\n')
    {
        count++;
        input = getc(stdin);
    }
    printf("%i\n", count);

    return 0;
}

int dec_to_bin(void)
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

char * char_to_ascii(char input, int op);

int str_to_ascii(void)
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
