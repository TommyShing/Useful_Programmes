#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int calc(char** ptr, int i, int* data);
int set_arith(int *core, int index, int *data, int co, char **str, int isAdd);
//upcoming: sqrt
int main(int argc, char *argv[])
{
    //argv -> str
    int len = 0;
    for (int i = 1, counter = 0; i < argc; i++)
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
    for (int i = 1, counter = 0; i < argc; i++)
    {
        while (argv[i][counter] != '\0')
        {
            param[len++] = argv[i][counter];
            counter++;
        }
        counter = 0;
    }
    //printf("%s\n", param);
    char *home = --param;

    int data[] = {0, 0, 0, 0};//t, h, w, i?
    printf("h & w: ");
    for (int i = 1; i < 3; i++)
    {
        scanf("%i", &data[i]);
    }
    //get process
    int size = sizeof(int) * data[2];
    int *set = malloc(size);

    //
    printf("Init set: ");
    for (int i = 0; i < data[2]; i++)
    {
        scanf("%i", &set[i]);
    }
    //
    for (int t = 0; t < data[1]; t++)
    {
        data[0] = t;
        int *core = calloc(size, sizeof(int));
        int *tmp = calloc(size, sizeof(int));
        set_arith(core, 0, data, 1, &param, 0);
        //conv
        for (int i = 0; i < data[2]; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                tmp[i] += set[j] * core[i - j];
            }
            printf("%i ", tmp[i]);
        }
        //printf("\n%i", (set == NULL));
        free(set);
        set = tmp;
        free(core);
        printf("\n");
        param = home;
    }
    free(set);
    free(home + 1);

    return 0;
}


int myPow(int x, int n);

int calc(char** ptr, int i, int* data)
{
    int state = 0, tmp = 0, buf = 0, next = 0;
    switch (**ptr)
    {
        case '-':
            state = 2;
            (*ptr)++;
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
        } benefit from argv*/
        switch (**ptr)
        {
            case '(':
                (*ptr)++;
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
                    (*ptr)++;
                } while ('0' <= **ptr && '9' >= **ptr);
                (*ptr)--;
                break;
            default:
                return 0;//
        }
        (*ptr)++;
        switch (**ptr)
        {
            case '+'://normal
            case '-':
            case '['://coefficient
            case '{':
            case ','://in core
            case ']':
            case ')'://in bracket
            case '}':
                next = 0;
                break;
            case '*':
            case '/':
                next = 1;
                break;
            case '^':
                next = 9;
                break;
            default:
                return 0;//
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
            case '}':
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
                state = (state & 2) | 1;
                break;
            case '/':
                state = (state & 2) | 5;
                break;
            case '^':
                state |= 9;
                break;
        }
        (*ptr)++;
        buf = 0;
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

int set_link(int *core, int index, int *data, int co, char **str)
{
    char *tmp = *str;
    for (int i = 0; i < co; i++)
    {
        *str = tmp;
        while (**str != ']')
        {
            (*str)++;
            core[index++] += calc(str, i, data);

            if (index == data[2])//data[w]
            {
                return index;
            }
        }
    }

    //co is 0
    while (**str != ']')
    {
        (*str)++;
    }
    return index;
}

int set_add(int *core, int index, int *data, int co, char **str)
{
    while (**str != ']')
    {
        data[3] = 0;//data[buf]
        char *tmp = ++*str;
        int val = calc(str, 0, data);
        switch (data[3])
        {
            case 0:
                core[index++] += co * val;
                break;
            default://case 1:
                switch (co)
                {
                    case 0:
                        index++;
                        break;
                    default:
                        core[index] += val;
                        for (int i = 1; i < co; i++)
                        {
                            *str = tmp;
                            core[index] += calc(str, i, data);
                        }
                        index++;
                        break;
                }
                break;
        }
        if (index == data[2])//data[w]
        {
            return index;
        }
    }
    return index;
}

int set_arith(int *core, int index, int *data, int co, char **str, int isAdd)
{
    int home = index, max = 0;
    char *tmp = ++*str;//{ -> val
    for (int i = 0; i < co; i++)
    {
        *str = tmp;

        while (**str != '}' && **str != '\0')
        {
            switch (**str)
            {
                case '+':
                    if (index > max)
                    {
                        max = index;
                    }
                    index = home;
                    (*str)++;
                    break;
            }
            int val = calc(str, i, data);
            switch (**str)
            {
                case '+':
                    (*str)++;
                    switch (**str)
                    {
                        case '[':
                            index = set_add(core, index, data, val, str);
                            break;
                        case '{':
                            index = set_arith(core, index, data, val, str, 1);
                            break;
                    }
                    break;
                case '[':
                    index = set_link(core, index, data, val, str);
                    break;
                case '{':
                    index = set_arith(core, index, data, val, str, 0);
                    break;
            }

            if (index == data[2])//data[w]
            {
                //shift tab
                    unsigned int sign = 2;
                    while (sign)
                    {
                        switch (*((*str)++))
                        {
                            case '[':
                            case '{':
                                sign++;
                                break;
                            case ']':
                            case '}':
                                sign--;
                                switch (sign)
                                {
                                    case 1:
                                        switch (**str)
                                        {
                                            case '+':
                                            case '}':
                                            case '\0':
                                                sign = 0;
                                                i = co;
                                                break;
                                        }
                                        break;
                                }
                                break;
                        }
                    }
            }
            else
            {
                (*str)++;
            }
        }
        switch (isAdd)
        {
            case 1:
                if (index > max)
                {
                    max = index;
                }
                index = home;
                break;
        }
    }
    switch (isAdd)
    {
        case 1:
            return max;
        default:
            return index;
    }
}
