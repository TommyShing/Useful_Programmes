#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
   char val[64];
   struct node *next;
}
node;

typedef struct
{
   char *digit;
   unsigned long long prop;//len & +/-
}
bigInt;

void freelist (node *list);
void printbits (char *bin, unsigned long long len);

int main(void)
{
    //linked list: value/pointer = 8
    //val: 64bytes  len:alloc = 128:1
    char in;
    printf("In: ");
    do
    {
        in = getc(stdin);
    }
    while (in == '\n');
    unsigned long long len = 0;
    unsigned long long alloc_space = 0;

    node *inlist = NULL;
    node *tmp = NULL;
    char *pointer = NULL;

    while (in != '\n')
    {
        len++;
        if (len > (alloc_space << 7))
        {
            tmp = inlist;
            inlist = malloc(sizeof(node *) + 64);
            if (inlist == NULL)
            {
                freelist(tmp);
                return 1;
            }
            inlist->next = tmp;
            pointer = inlist->val;
            alloc_space++;
        }
        if (len & 1)
        {
            *pointer = 0;
            *pointer = in & 15;//bcd
        }
        else
        {
            *pointer |= (in & 15) << 4;
            pointer++;
        }
        in = getc(stdin);
    }
    bigInt *num = malloc(sizeof(char *) + sizeof(long long));
    if (num == NULL)
    {
        freelist(inlist);
        return 2;
    }
    num->digit = malloc(sizeof(unsigned long long) * ((len >> 4) + 1) + sizeof(char) * 5);//long long 8bytes -> 16bcd digits, sizeof(char) * 5 for bcd transform redundancy
    if (num->digit == NULL)
    {
        freelist(inlist);
        free(num);
        return 2;
    }
    char convert[17];
    convert[16] = '\0';
    int index = 0;
    int boolval = len & 1;
    unsigned long long bcdblock = len >> 4;
    int indexflip[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    if (boolval == 1)
    {
        unsigned long long *digit = (unsigned long long *) num->digit;
        for (long long i = 0; i < bcdblock; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                convert[indexflip[index]] = (char) (*pointer & 15) | 48;
                if (pointer == inlist->val)
                {
                    pointer = tmp->val + 64;
                    free(inlist);
                    inlist = tmp;
                    tmp = tmp->next;
                }
                pointer--;
                convert[indexflip[index + 1]] = (char) ((*pointer >> 4) & 15) | 48;
                index += 2;
            }

            *digit = strtoull(convert, NULL, 10);
            digit++;
            index = 0;
        }
        * (unsigned long long *) convert = 0;
        * (unsigned long long *) (convert + 8) = 0;
        convert[(len & 15) - 1] = (char) (*pointer & 15) | 48;
        for (int i = ((len & 15) >> 1) - 1; i >= 0; i--)
        {
            pointer--;
            convert[(i << 1) + 1] = (char) ((*pointer >> 4) & 15) | 48;
            convert[i << 1] = (char) (*pointer & 15) | 48;
        }
        *digit = strtoull(convert, NULL, 10);
        free(inlist);
    }
    else
    {
        unsigned long long *digit = (unsigned long long *) num->digit;
        for (long long i = 0; i < bcdblock; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                pointer--;
                convert[indexflip[index]] = (char) ((*pointer >> 4) & 15) | 48;
                convert[indexflip[index + 1]] = (char) (*pointer & 15) | 48;
                index += 2;
                if (pointer == inlist->val)
                {
                    pointer = tmp->val + 64;
                    free(inlist);
                    inlist = tmp;
                    tmp = tmp->next;
                }
            }

            *digit = strtoull(convert, NULL, 10);
            digit++;
            index = 0;
        }
        for (int i = ((len & 15) >> 1) - 1; i >= 0; i--)
        {
            pointer--;
            convert[(i << 1) + 1] = (char) ((*pointer >> 4) & 15) | 48;
            convert[i << 1] = (char) (*pointer & 15) | 48;
        }
        *digit = strtoull(convert, NULL, 10);
        free(inlist);
    }
    //printbits(num->digit, sizeof(unsigned long long) * (bcdblock + 1));
    /*
    10000000000100011100001101111001001101111110000001111111111111111
    10000000000100011100001101111001001101111110000010000000000000000: 10**16 + 2**64
    1000000000010001110000110111100100110111111000001 + 16*0: 5**16 + 8**16
    01111111111011100011110010000110110010000001111110000000000000000
    */
    if (bcdblock)
    {
        //unsigned long long adder = 152587890625;
        //long long substractor = -281474976710656;
        long long adder = -281322388820031;
        long long filter = 281474976710656;
        long long *pointer0 = NULL;
        //bcdblock - 1; 64bits -> 8bits/add_pointer0
        for (int i = bcdblock - 1; i >= 0; i--)
        {
            pointer0 = (long long *) (num->digit + 2) + i;
            for (int j = i; j < bcdblock; j++)
            {
                for (int k = 0; k < 8; k++)
                {
                    for (int l = 0; l < 8; l++)
                    {
                        if (*pointer0 & (filter << l))
                        {
                            *pointer0 += adder << l;
                        }
                    }
                    pointer0 = (long long *) ((char *) pointer0 + 1);
                }
            }
        }
    }
    pointer = num->digit + (len >> 2) + 6;//10**16<2**54
    num->prop = 8 * ((len >> 2) + 6) << 1;
    while (*pointer == 0)
    {
        pointer--;
        num->prop -= 16;
    }
    for (unsigned int i = (unsigned int) *pointer; i > 0; i >>= 1)
    {
        num->prop += 2;
    }
    printbits(num->digit, (num->prop >> 4) + 1);
    printf("%lli", num->prop >> 1);
    free(num->digit);
    free(num);

}

void freelist (node *list)
{
    node *tmp = NULL;
    do
    {
        tmp = list->next;
        free(list);
        list = tmp;
    }
    while (tmp != NULL);
}

void printbits (char *bin, unsigned long long len)
{
    for (unsigned long long i = 0; i < len; i++)
    {
        printf("%i%i%i%i%i%i%i%i ", *bin & 1, (*bin >> 1) & 1, (*bin >> 2) & 1, (*bin >> 3) & 1, (*bin >> 4) & 1, (*bin >> 5) & 1, (*bin >> 6) & 1, (*bin >> 7) & 1);
        bin++;
    }
    printf("\n");
}