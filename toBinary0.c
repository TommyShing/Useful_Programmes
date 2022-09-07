#include <stdio.h>
#include <stdlib.h>

typedef char * string;
int printNum_0(char *str);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Please add an integer\n");
        return 1;
    }
    printf("Binary: ");
    //Multiple Nums
    for (int i = 1; i < argc; i++)
    {
        int retVal = printNum_0(argv[i]);
        if (retVal == 1)
        {
            printf("\nNo Enough Memory!\n");
            return 1;
        }
        else if (retVal == 2)
        {
            printf("\nPlease Input a Valid Number!\n");
        }
    }
    return 0;
}

int strLen(char *str)
{
    long long i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

void strPush(char *str, char *addStr, long long index)
{
    for (int i = 0, length = strLen(addStr); i < length; i++)
    {
        str[index] = addStr[i];
        index++;
    }
}

int printNum_0(char *str)
{
    char *list[] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    int listRange = 4;
    long long length = strLen(str);
    //Create An BCD Array
    char *bcd = malloc(sizeof(char) * length * listRange);
    if (bcd == NULL)
    {
        return 1;
    }
    //Push the Numbers
    for (long long i = 0; i < length; i++)
    {
        char current = str[i];
        if (current > 47 && current < 59)
        {
            strPush(bcd, list[(long long)current - 48], i * listRange);
        }
        else
        {
            return 2;
        }
    }
    bcd[length * listRange] = '\0';
    //BCD -> BIN
    length = strLen(bcd);
    if (length > 5)
    {
        int carry = 0;
        char *num;
        for (long long i = length - 5; i >= 0;i--)
        {
            for (long long j = i; j >= 0; j-=4)//Iterate Over the Number
            {
                if (bcd[j] == '1')
                {
                    //origin - 011||origin + 1101
                    for (int k = 3; k >= 0; k--)//Iterate Over 4 digits
                    {
                        num = &bcd[j + k];//Or bcd + j + k
                        *num = (char)((int)*num + carry);
                        if (k == 2)
                        {
                            switch (*num)
                            {
                                case '0':
                                    carry = 0;
                                    *num = '0';
                                    break;
                                case '1':
                                    carry = 0;
                                    *num = '1';
                                    break;
                                case '2':
                                    carry = 1;
                                    *num = '0';
                                    break;
                            }
                        }
                        else
                        {
                            switch (*num)
                            {
                                case '0':
                                    carry = 0;
                                    *num = '1';
                                    break;
                                case '1':
                                    carry = 1;
                                    *num = '0';
                                    break;
                                case '2':
                                    carry = 1;
                                    *num = '1';
                                    break;
                            }
                        }
                    }
                    carry = 0;
                }
            }
        }
    }
    //Get Rid of the 0s in the Front
    char *ret = bcd;
    while (*ret == '0')
    {
        ret++;
    }
    printf("%s\n", ret);
    free(bcd);
    return 0;
}