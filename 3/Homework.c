#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print(int n)
{
    printf("%\n");
    for (int base = 2; base <= 16; base+=14) {
        char nums[100];
        int i = 0;
        int number = n;
        while (number != 0) {
            int temp = 0;
            temp = number % base;
            nums[i] = (temp < 10) ? temp + 48 : temp + 55;
            i++;
            number /= base;
        }
        for (int j = i - 1; j >= 0; j--)
            printf("%c", nums[j]);
        printf("%\n");
    }

}


int main(void)
{
    int a;
    scanf("%d", &a);
    int b = a;
    int mask, mask2;
    int cnt = 0;
    while (b != 0) {
        b=b>>1;
        cnt++;
    }
    print(a);
    for (int i = 0; i < cnt/2; i++) {
        mask = 1<<i;
        mask = mask & a;
        mask2 = 1 << cnt-1-i;
        mask2 = mask2 & a;
        if ((mask > 0) != (mask2 > 0)) {
            a = a ^ ((1 << i) | (1 << cnt - 1 - i));
        }
    }
    print(a);

    return 0;
}