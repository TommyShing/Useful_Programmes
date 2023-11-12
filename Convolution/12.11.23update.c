#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//upcoming: sqrt
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
    
    int data[3];//t, h, w
    
    
    return 0;
}


int myPow(int x, int n);

int calc(char* ptr, int i, int *data, int sp, char *cdt, int cdtlen)//space remain: w - len, cdt is the ending signal
{
    int sum = 0, pro = 0, ter = 0;
    /*
    sum: +, -
    pro: *, /
    ter: ^
    */
    int buf = 0;
    int state = 0;
    /*
    the first digit 0(sum) or 1(pro or ter)
    the second digit 0(+) or 1(-)
    the third digit 0(*) or 1(/)
    the fourth digit 0(pro) or 1(ter)
    e.g. 0011: sum with -, pro with *; 1001: sum with +, pro with *, ter
    */
    while (1)
    {
        while (*ptr == ' ')
        {
            ptr++;
        }
        switch (*ptr)
        {
            case '('
                buf = calc_bracket();
                break;
            case 't':
                buf = data[0];
            case 'h':
                buf = data[1];
            case 'w':
                buf = data[2];
        }
        
        switch (*ptr)
        {
            case '+':
                switch (state)
                {
                    case 0:
                        sum += buf;
                        break;
                    case 1:
                        sum -= buf;
                        break;
                    case 2:
                        sum += buf * pro;
                        break;
                    case 4:
                        sum += myPow(ter, buf);
                        break;
                }
                buf = 0;
                state = 0;
            case '-':
                switch (state)
                {
                    case 0:
                        sum -= buf;
                        break;
                    case 1:
                        sum -= buf * pro;
                        break;
                    case 2:
                        sum += myPow(ter, buf);
                        break;
                }
                buf = 0;
                state = 0;
            case ' ':
                ptr++;
                break;
        }
    }
}


int myPow(int x, int n)
{
    switch (n)
    {
        case 0:
            return 1;
    }
    int result = 1;
    while (n)
    {
        switch (n & 1)
        {
            case 1:
                result *= x;
                break;
        }
        x = x * x;
        n >>= 1;
    }
    return result;
}


