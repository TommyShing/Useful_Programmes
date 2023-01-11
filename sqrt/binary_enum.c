#include <stdio.h>

int main(void)
{
    //init
    int input;//sqrt(input)=N=an+...+a0
    printf("Input: ");
    scanf("%i", &input);
    int pm = 1;//Pm=an+...+am(n>=m)
    int n = 0;
    //O(n)
    for (int i = 1; i <= input; i <<= 2)
    {
        pm <<= 1;
        n++;
    }
    pm >>= 1;//Pn
    //int m = n - 1;
    //O(n)
    for (int m = n - 1; m >= 0; m--)
    {
        int am = (1 << m);
        int tmp = pm + am;
        int ttmp = tmp * tmp;
        if (ttmp < input)
        {
            pm = tmp;
        }
        else if (ttmp == input)
        {
            printf("%i\n", tmp);//9(2,1),36(3,2),144(4,3),576(4,3,2)
            return 0;//
        }
    }
    printf("%i\n", pm);
    return 0;
}
