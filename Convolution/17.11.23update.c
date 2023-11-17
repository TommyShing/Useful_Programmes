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

int calc(char** ptr, int i, int* data)//space remain: w - len, cdt is the ending signal
{
    int state = 0, tmp = 0, buf = 0, next = 0;
    switch (**ptr)
    {
        case '-':
            state = 2;
            *ptr++;
            break;
        case '[':
        case '{':
            return 1;
    }
    int sum = 0, pro = 1, dpr = 1, ter = 1;
    /*
    sum: +, -
    pro: *, /
    ter: ^
    
    the first digit 0(sum) or 1(pro or ter)
    the second digit 0(+) or 1(-)
    the third digit 0(*) or 1(/)
    the fourth digit 0(pro) or 1(ter)
    e.g. 0011: sum with -, pro with *; 1001: sum with +, pro with *, ter
    */
    while (1)
    {/*
        while (*ptr == ' ')
        {
            ptr++;
        } benefits*/
        switch (**ptr)
        {
            case '('
                *ptr++;
                buf = calc(ptr, i, data);
                break;
            case 'i':
                buf = i;
                break;
            case 't':
                buf = data[0];
                break;
            case 'h':
                buf = data[1];
                break;
            case 'w':
                buf = data[2];
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                do
                {
                    buf*=10;
                    buf += **ptr - '0';
                    *ptr++;
                } while ('0' <= **ptr && '9' >= **ptr);
                **ptr--;
                break;
            default:
                return//
        }
        *ptr++;
        switch (*ptr)
        {
            case '+'://normal
            case '-':
            case '['://coefficient
            case '{':
            case ','://in core
            case ']':
            case ')'://in bracket
                next = 0;
                break;
            case '*':
            case '/':
                next = 1;
                break;
            case '^'
                next = 9;
                break;
            default:
                return//
        }
        tmp = state | next;
        switch (tmp & 8)
        {
            case 0:
                switch (tmp & 5)
                {
                    case 0:
                        switch (tmp)
                        {
                            case 0:
                                sum += buf;
                                break;
                            default://case 2:
                                sum -= buf;
                                break;
                        }
                        break;
                    case 1:
                        pro *= buf;
                        break;
                    default://case 5:
                        dpr *= buf;
                        break;
                }
                break;
            default://case 8:
                switch (state & 8)
                {
                    case 0:
                        ter = buf;
                        break;
                    default:
                        ter = myPow(ter, buf);
                        break;
                }
                break;
        }
        //from ^ to *, /
        if (next & ((state & (next + 8)) >> 3))
        {
            switch (state & 4)
            {
                case 0:
                    pro *= ter;
                    break;
                default://case 4:
                    dpr *=ter;
                    break;
            }
            ter = 1;
        }
        //from ^, *, / to +, -
        else if (1 & (next + 1) & state)
        {
            switch (state & 6)
            {
                case 0:
                    sum += pro * ter / dpr;
                    break;
                case 2:
                    sum -= pro * ter / dpr;
                    break;
                case 4:
                    sum += pro / ter / dpr;
                    break;
                case 6:
                    sum -= pro / ter / dpr;
                    break;
            }
            pro = 1, dpr = 1, ter = 1;
        }
        //exit
        switch (**ptr)
        {
            case '[':
            case '{':
            case ',':
            case ']':
            case ')':
                return sum;
            case '+':
            case '-':
                switch(*(*ptr + 1))
                {
                    case '[':
                    case '{':
                        return sum;
                }
                break;
        }
        switch (**ptr)
        {
            case '+':
                state = 0;
                break;
            case '-':
                state = 2;
                break;
            case '*':
                state &= 3;
                break;
            case '/':
                state = (state & 3) | 4;
                break;
            case '^':
                state |= 8;
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
